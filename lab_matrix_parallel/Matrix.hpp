#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <fstream>

#include <cstddef>
#include <exception>

#include <vector>
#include <string>

#include <thread>
#include <mutex>
#include <future>
#include <chrono>

struct Cursor {
    size_t line{}, column{};
    std::mutex m;
};

template<class T>
class Matrix {
private:

    static size_t parallel;

    size_t lines_count_{}, columns_count_{};

    std::vector<T> data_;

public:
    Matrix() = default;
    Matrix(const Matrix<T>& obj) = default;
    Matrix(size_t lines_count, size_t columns_count);

    static void SetParallel(size_t num);
    static size_t GetParallel();

    void LoadMatrix(const char* filename);
    void LoadMatrix(std::ifstream& fin);

    void SaveMatrix(const char* filename) const;

    template<typename U>
    friend Matrix<U> operator * (const Matrix<U>& lhs, const Matrix<U>& rhs);
    
    template<typename U>
    friend void CalculateValuesSingleThread(const Matrix<U>& lhs, const Matrix<U>& rhs, Matrix<U>& result, Cursor& cursor,  std::promise<size_t>&& message, size_t id);
    
    template<typename U>
    friend U CalculateOneValueSingleThread(const Matrix<U>& lhs, const Matrix<U>& rhs, size_t lhs_line, size_t rhs_column, size_t common_index);

};

template<class T>
Matrix<T>::Matrix(size_t lines_count, size_t columns_count) : lines_count_(lines_count), columns_count_(columns_count) {
    data_.resize(lines_count_ * columns_count_);
}

template<typename T>
size_t Matrix<T>::parallel = 1;

template<typename T>
void Matrix<T>::SetParallel(size_t num) {
    Matrix<T>::parallel = num;
}

template <class T>
size_t Matrix<T>::GetParallel() {
    return Matrix<T>::parallel;
}

template<class T>
void Matrix<T>::LoadMatrix(const char* filename) {
    std::ifstream fin(filename);

    if (!fin.good()) {
	    std::cerr << "Cannot open input file" << std::endl;
	    exit(1);
    }

    fin >> lines_count_ >> columns_count_;
    data_.resize(lines_count_ * columns_count_);

    for (size_t line = 0; line < lines_count_; line++) {
        for (size_t column = 0; column < columns_count_; column++) {
            fin >> data_[line * columns_count_ + column];
        }
    }
    fin.close();
}

template<class T>
void Matrix<T>::LoadMatrix(std::ifstream& fin) {
    fin >> lines_count_ >> columns_count_;
    data_.resize(lines_count_ * columns_count_);

    for (size_t line = 0; line < lines_count_; line++) {
        for (size_t column = 0; column < columns_count_; column++) {
            fin >> data_[line * columns_count_ + column];
        }
    }
}

template<class T>
void Matrix<T>::SaveMatrix(const char* filename) const {
    std::ofstream fout(filename);
    
    if (!fout.good()) {
	std::cerr << "Cannot open output file" << std::endl;
	exit(1);
    }
    
    fout << lines_count_ << ' ' << columns_count_ << '\n';
    for (size_t line = 0; line < lines_count_; line++) {
        for (size_t column = 0; column < columns_count_; column++) {
            fout << data_[line * columns_count_ + column] << ' ';
        }
        fout << '\n';
    }

    fout.close();
}

template<typename U>
void CalculateValuesSingleThread(const Matrix<U>& lhs, const Matrix<U>& rhs, Matrix<U>& result, Cursor& cursor,  std::promise<size_t>&& message, size_t id) {
    for (size_t line = 0; line < lhs.lines_count_; line++) {
        for(size_t column = 0; column < rhs.columns_count_; column++) {
            
            cursor.m.lock();
            
            if (cursor.line == lhs.lines_count_) {
                line = cursor.line;
                cursor.m.unlock();
                break;
            }

            line = cursor.line;
            column = cursor.column;
            
            cursor.column++;
            if (cursor.column == rhs.columns_count_) {
                cursor.column = 0;
                cursor.line++;
            }

            cursor.m.unlock();

            result.data_[line * rhs.columns_count_ + column] = std::move(CalculateOneValueSingleThread(lhs, rhs, line, column, lhs.columns_count_));
       	}
    }

    message.set_value(std::move(id));
}

template<typename U>
U CalculateOneValueSingleThread(const Matrix<U>& lhs, const Matrix<U>& rhs, size_t lhs_line, size_t rhs_column, size_t common_index) {
    U result{};
    for (size_t index = 0; index < common_index; index++) {
        result += lhs.data_[lhs_line * lhs.columns_count_ + index] * rhs.data_[index * rhs.columns_count_ + rhs_column];
    }
    return result;
}

template<typename U>
Matrix<U> operator * (const Matrix<U>& lhs, const Matrix<U>& rhs) {
    if (lhs.lines_count_ * lhs.columns_count_ * rhs.lines_count_ * rhs.columns_count_ == 0) {
	return Matrix<U>(0, 0);
    }

    if (lhs.columns_count_ != rhs.lines_count_) {
        throw std::invalid_argument{"std::invalid_argument"};
    }

    Matrix<U> result(lhs.lines_count_, rhs.columns_count_);

    Cursor cursor;
    std::vector<std::future<size_t>> futures(Matrix<U>::GetParallel());

    for (size_t thread_num = 0; thread_num < Matrix<U>::GetParallel(); thread_num++) {
        std::promise<size_t> message;
        futures[thread_num] = message.get_future();
        std::thread t(CalculateValuesSingleThread<U>, lhs, rhs, std::ref(result), std::ref(cursor), std::move(message), thread_num+1);
        t.detach();
    }
    
    size_t parallels_to_do = Matrix<U>::GetParallel();
    std::vector<bool> done(parallels_to_do);
    while (parallels_to_do > 0) {
        for (size_t thread_num = 0; thread_num < Matrix<U>::GetParallel(); thread_num++) {
            if (!done[thread_num]) {
                if (futures[thread_num].wait_for(std::chrono::nanoseconds(1)) == std::future_status::ready) {
                    done[thread_num] = true;
                    parallels_to_do--;
                    std::cout << "Thread number " << futures[thread_num].get() << " is done" << '\n';
                }
            }
        }
    }
    
    return result;
}


#endif // MATRIX_HPP
