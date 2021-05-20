#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <valarray>


using namespace std;

template <class T>
class Matrix {
private:
	valarray<T> element;
	size_t rows, cols;
public:
	Matrix();
	Matrix(size_t rows, size_t cols);
	Matrix(const Matrix<T>& copy);
	~Matrix();
	
	void set_element(size_t row, size_t col, T value);
	T get_element(size_t row, size_t col) const ;
	size_t get_rows() const ;
	size_t get_cols() const ;
	
	friend ostream& operator<< (ostream& cout, const Matrix<T>& ob) {
		for (size_t i = 0; i < ob.rows; i++) {
			for (size_t j = 0; j < ob.cols; j++) {
				cout << ob.element[i * ob.cols + j] << " ";
			}
			cout << endl;
		}
		return cout;
	}
	
	friend istream& operator>> (istream& cin,  Matrix<T>& ob)  {
		ob.element.resize(ob.cols * ob.rows);
		for (size_t i = 0; i < ob.rows; i++) {
			for (size_t j = 0; j < ob.cols; j++) {
				cin >> ob.element[i * ob.cols + j];
			}
		}
		return cin;
	}

	Matrix<T> operator= (const Matrix<T>& copy);

	friend Matrix<T> operator* (const T n, const Matrix<T>& ob) {
		Matrix<T> temp(ob);
		temp.element *= n;
		return temp;
	}

	Matrix<T> operator* (const T n);
	Matrix<T> operator* (const Matrix<T>& ob);
	Matrix<T> operator+ (const Matrix<T>& ob);

	Matrix<T> transpose() const;
	Matrix<T> RowEchelonForm() const;
	Matrix<T> ReducedRowEchelonForm() const;
	T det() const;
	Matrix<T> inverse() const;
	Matrix<T> extended_by(const Matrix<T>& B) const ;
	size_t matrix_rang() const ;
	void solve_with(const Matrix<T>& B) const;
	void solve_with_0() const ;
};

template <typename T>
Matrix<T>::Matrix() {
	this->rows = 0;
	this->cols = 0;
	this->element.resize(0);
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) {
	this->rows = rows;
	this->cols = cols;
	this->element.resize(cols * rows);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& copy) {
	this->rows = copy.rows;
	this->cols = copy.cols;
	this->element = copy.element;
}

template <typename T>
Matrix<T>::~Matrix() {

}

template <typename T>
void Matrix<T>::set_element(size_t row, size_t col, T value) {
	element[col + cols * row] = value;
}

template <typename T>
T Matrix<T>::get_element(size_t row, size_t col) const {
	return element[col + cols * row];
}

template <typename T>
size_t Matrix<T>::get_rows() const {
	return rows;
}

template <typename T>
size_t Matrix<T>::get_cols() const {
	return cols;
}

template <typename T>
Matrix<T> Matrix<T>::operator= (const Matrix<T>& copy) {
	this->rows = copy.rows;
	this->cols = copy.cols;
	this->element = copy.element;
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const T n) {
	Matrix<T> temp(*this);
	temp.element *= n;
	return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& ob) {
	if (this->cols != ob.rows || this->cols == 0 || this->rows == 0 || ob.cols == 0 || ob.rows == 0 ) {
		ofstream fout("./out.txt");
		if (fout.is_open()) {
			fout << -1 << endl;
			fout << "Cannot multiply these Matrixs" << endl;
			fout.close();
		}
		else {
			cout << "Cannot open output file" << endl;
		}
		exit(0);
	}
	Matrix temp(this->rows, ob.cols);
	for (size_t i = 0; i < temp.rows; i++) {
		for (size_t j = 0; j < temp.cols; j++) {
			for (size_t k = 0; k < temp.rows; k++) {
				temp.element[i * temp.cols + j] += this->element[i * this->cols + k] * ob.element[j + k * ob.cols];
			}
		}
	}
	return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix<T>& ob) {
	if ((this->cols != ob.cols) || (this->rows != ob.rows) || this->cols == 0 || this->rows == 0 || ob.cols == 0 || ob.rows == 0) {
		ofstream fout("./out.txt");
		if (fout.is_open()) {
			fout << -1 << endl;
			fout << "Cannot summirize these Matrixs" << endl;
			fout.close();
		}
		else {
			cout << "Cannot open output file" << endl;
		}
		exit(0);
	}
	else {
		Matrix temp(this->rows, this->cols);
		temp.element = this->element + ob.element;
		return temp;
	}
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
	if (cols == 0 || rows == 0) {
		ofstream fout("./out.txt");
		if (fout.is_open()) {
			fout << -1 << endl;
			fout << "Cannot transpose this matrix" << endl;
			fout.close();
		}
		else {
			cout << "Cannot open output file" << endl;
		}
		exit(0);
	}

	Matrix<T> temp(cols, rows);
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			temp.element[i + j * rows] = element[i * cols + j];
		}
	}
	return temp;;
}

template <typename T>
Matrix<T> Matrix<T>::RowEchelonForm() const {
	if (cols == 0 || rows == 0) {
		ofstream fout("./out.txt");
		if (fout.is_open()) {
			fout << -1 << endl;
			fout << "Cannot make row echelon form of this matrix" << endl;
			fout.close();
		}
		else {
			cout << "Cannot open output file" << endl;
		}
		exit(0);
	}

	Matrix<T> temp(*this);
	size_t n = rows;
	size_t m = cols;
	size_t j = 0;
	size_t s = 0;
	size_t col = 0;
	for (size_t i = 0; i < n; i++) {
		if (col == m) {
			break;
		}
		for (s = i; s < n; s++) {
			if (temp.element[col + s * m] != 0) { 
				j = s;
				break;
			}
		}
		if (s == n) {
			col++;
			i--;
			continue;
		}
		else {
			for (size_t k = col; k < m; k++) {
				if (i == j) {
					break;
				}
				swap(temp.element[k + i * m], temp.element[k + j * m]);
			}
		}
		for (size_t j = i + 1; j < n; j++) {
			if (temp.element[col + j * m] == 0) {
				continue;
			}
			auto coefficient = temp.element[col + j * m] / temp.element[col + i * m];
			for (size_t k = col; k < m; k++) {
				temp.element[k + j * m] -= coefficient * temp.element[k + i * m];
				
			}
		}
		col++;
	}
	return temp;
}

template <typename T>
Matrix<T> Matrix<T>::ReducedRowEchelonForm() const {
	Matrix<T> temp(*this);
	temp = temp.RowEchelonForm();
	size_t n = rows;
	size_t m = cols;
	size_t col = 0;
	size_t gl = 0;
	for (size_t i = 0; i < n; i++) {
		if (col == m) {
			break;
		}
		if (temp.element[col + i * m] == 0) { 
			i--;
		}
		else {
			auto coefficient = temp.element[col + i * m];
			for (size_t j = col; j < m; j++) {
				temp.element[j + i * m] /= coefficient;
			}
			gl = col;
		}
		col++;
		}
	col = gl;
	for (size_t i = n - 1; i < (size_t) -1; i--) {
		if (col == (size_t) -1) {
			break;
		}
		if (temp.element[col + i * m] != 1) {
			if (col != gl) {
				i++;
				col--;
			}
			continue;
		}
		else {
			if (col != 0) {
				size_t j = 0;
				for (j = 0; j <= col; j++) {
					if (temp.element[j + i * m] == 1) {
						break;
					}
				}
				if (j != col) {
					i++;
					col--;
					continue;
				}
			}
			for (size_t j = i - 1; j < (size_t) -1; j--) {
				auto coefficient = temp.element[col + j * m];
				for (size_t k = col; k < m; k++) {
					temp.element[k + j * m] -= coefficient * temp.element[k + i * m];
				}
			}
			col--;
		}
	}
	return temp;
}

template <typename T>
T Matrix<T>::det() const {
	if (rows != cols || rows == 0) {
		ofstream fout("./out.txt");
		if (fout.is_open()) {
			fout << -1 << endl;
			fout << "Cannot find determinant" << endl;
			fout.close();
		}
		else {
			cout << "Cannot open output file" << endl;
		}
		exit(0);
	}
	Matrix temp(*this);
	size_t n = temp.rows;
	T det = 1;
	bool flag = false;
	size_t j = 0;
	size_t s = 0;
	for (size_t i = 0; i < n; i++) {
		for (s = i; s < n; s++) {
			if (temp.element[i + s * n] != 0) {
				j = s;
				break;
			}
		}
		if (s == n) {
			flag = true;
			break;   
		}
		else {
			for (size_t k = i; k < n; k++) {
				if (i == j) {
					det = -det;
					break;
				}
				auto t = temp.element[k + i * n];
				temp.element[k + i * n] = temp.element[k + j * n];
				temp.element[k + j * n] = t;
			}
			det = -det;
		}
		for (size_t j = i + 1; j < n; j++) {
			if (temp.element[i + j * n] == 0) {
				continue;
			}
			auto coefficient = temp.element[i + j * n] / temp.element[i + i * n];
			for (size_t k = i; k < n; k++) {
				temp.element[k + j * n] += -coefficient * temp.element[k + i * n];
			}
		}
	}
	if (flag)
		return 0;
	for (size_t i = 0; i < n; i++) {
		det *= temp.element[i + i * n];
	}
	return det;
}

template <typename T>
Matrix<T> Matrix<T>::inverse() const {
	if (rows != cols || rows == 0) {
		ofstream fout("./out.txt");
		if (fout.is_open()) {
			fout << -1 << endl;
			fout << "Cannot inverse non-square matrix." << endl;
			fout.close();
		}
		else {
			cout << "Cannot open output file" << endl;
		}
		exit(0);
	}

	size_t n = rows;
	Matrix<T> inversed(n, n);
	Matrix<T> temp(*this);
	for (size_t i = 0; i < n; i++) {
		inversed.element[i + i*n] = 1;
	}
	size_t j = 0;
	size_t s = 0;
	for (size_t i = 0; i < n; i++) {
		j = i;
		for (s = i; s < n; s++) {
			if (temp.element[i + s * n] != 0) {
				j = s;
				break;
			}
		}
		if (s == n) {
			continue;
		}
		else {
			for (size_t k = i; k < n; k++) {
				if (i == j) {
					break;
				}
				swap(temp.element[k + i * n], temp.element[k + j * n]);

				swap(inversed.element[k + i * n], inversed.element[k + j * n]);
			}
		}
		auto coefficient = temp.element[i + i * n];
		for (size_t j = 0; j < n; j++) {
			temp.element[j + i * n] /= coefficient;
			inversed.element[j + i * n] /= coefficient;
			
		}

		for (size_t j = i + 1; j < n; j++) {
			if (temp.element[i + j * n] == 0) {
				continue;
			}
			auto coefficient = temp.element[i + j * n];
			for (size_t k = 0; k < n; k++) {
				temp.element[k + j * n] -= coefficient * temp.element[k + i * n];
				inversed.element[k + j * n] -= coefficient * inversed.element[k + i * n];
			}
		}
	}
	for (size_t i = n - 2; i < (size_t) -1; i--) {
		for (size_t j = i; j < (size_t) -1; j--) {
			auto coefficient = temp.element[i + 1 + j * n];

			for (size_t k = n - 1; k <  (size_t) -1; k--) {
				temp.element[k + j * n] -= coefficient * temp.element[k + (i + 1) * n];
				inversed.element[k + j * n] -= coefficient * inversed.element[k + (i + 1) * n];
			}
		}
	}
	bool flag = false;
	for (size_t i = 0; i < n; i++) {
		if (temp.element[i+i*n] == 0) {
			flag = true;
			break;
		}
	}
	if (flag) {
		ofstream fout("./out.txt");
		if (fout.is_open()) {
			fout << -1 << endl;
			fout << "Cannot inverse matrix with det = 0" << endl;
			fout.close();
		}
		else {
			cout << "Cannot open output file" << endl;
		}
		exit(0);
	}
	return inversed;
}

template <typename T>
Matrix<T> Matrix<T>::extended_by(const Matrix<T>& B) const {
	if (cols == 0 || rows == 0 || B.cols == 0|| B.rows == 0) {
		ofstream fout("./out.txt");
		if (fout.is_open()) {
			fout << -1 << endl;
			fout.close();
		}
		else {
			cout << "Cannot open output file" << endl;
		}
		exit(0);
	}
	size_t n = rows;
	size_t m = cols + 1;
	Matrix extended(n, m);
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m - 1; j++) {
			extended.element[j + i * m] = element[j + i * (m - 1)];
		}
		extended.element[(m - 1) + i * m] = B.element[i];
	}
	return extended;
}

template <typename T>
size_t Matrix<T>::matrix_rang() const { // only for echelon matrix
	size_t rang = 0;
	Matrix temp(*this);
	size_t n = rows;
	size_t m = cols;
	size_t col = 0;
	for (size_t i = 0; i < n; i++) {
		if (col == m) {
			break;
		}
		if (temp.element[col + i * m] == 0) {
			i--;
		}
		else {
			rang++;
		}
		col++;
	}
	return rang;
}

template <typename T>
void Matrix<T>::solve_with(const Matrix<T>& B) const {
	size_t n = rows;
	size_t m = cols + 1;
	Matrix<T> temp(*this);
	Matrix C = temp.extended_by(B);
	temp = temp.RowEchelonForm();
	C = C.ReducedRowEchelonForm();
	size_t rang = temp.matrix_rang();
	size_t rang_of_extended = C.matrix_rang();
	if (rang_of_extended > rang) {
		ofstream fout("./out.txt");
		if (fout.is_open()) {
			fout << -1 << endl;
			fout.close();
		}
		else {
			cout << "Cannot open output file" << endl;
		}
		exit(0);
	}
	else {
		ofstream fout("./out.txt");
		if (!fout.is_open()) {
			cout << "Cannot open output file" << endl;
			exit(0);
		}
		size_t col = 0;
		vector<size_t> svobodnie;
		vector<size_t> glavnie;
		for (size_t i = 0; i < n; i++) {
			if (col == m - 1) {
				break;
			}
			if (C.element[col + i * m] == 1) {
				if ((col>0 && C.element[col-1 + i*m]==0) || (col==0)) {
					glavnie.push_back(col);
				}
				else {
					svobodnie.push_back(col);
				}
			}
			else {
				svobodnie.push_back(col);
				i--;
			}
			col++;
			if ((col!=m)&&((i+1)==n)) {
				i-=1;
			}
		}

		fout << m-1 << " " << svobodnie.size() << endl;
		size_t c = 0;
		col = 0;
		for (size_t i = 0; i < m-1; i++) {
			if (i == glavnie[col]) {
				if (C.element[(m-1)+c*m]==0) {
					fout << 0 << " ";
				}
				else {
					fout << C.element[(m-1) + c*m] << " ";
				}
				c++;
				col++;
			}
			else {
				fout << 0 << " ";
			}
		}
		fout << endl;
		col = 0;
		if (svobodnie.size() == 0) {
			return ;
		}
		for (size_t i = 0; i < m - 1; i++) {
			if (i == svobodnie[col]) {
				c = 0;
				for (size_t j = 0; j < m-1; j++) {
					if (j == i) {
						fout << 1 << " ";
					}
					else {
						if (j > i) {
							fout << 0 << " ";
						}
						else if (find(svobodnie.begin(), svobodnie.end(), j)!=svobodnie.end()) {
							fout << 0 << " ";
						}
						else {
							if (C.element[i+c*m]==0) {
								fout << 0 << " ";
							}
							else fout << -C.element[i + c * m] << " ";
							c++;
						}
					}
				}
				fout << endl;
				col++;

			}
			if (col == svobodnie.size()) {
				break;
			}
		}
		fout.close();
	}
}

template <typename T>
void Matrix<T>::solve_with_0() const {
	Matrix<T> temp(*this);
	size_t n = rows;
	size_t m = cols;
	temp = temp.ReducedRowEchelonForm();
	ofstream fout("./out.txt");
	if (!fout.is_open()) {
		cout << "Cannot open output file" << endl;
		exit(0);
	}
	size_t col = 0;
	vector<size_t> svobodnie;
	vector<size_t> glavnie;
	for (size_t i = 0; i < n; i++) {
		if (col == m) {
			break;
		}
		if (temp.element[col + i * m] == 1) {
			if ((col>0 && temp.element[col-1 + i*m]==0) || (col==0)) {
				glavnie.push_back(col);
			}
			else {
				svobodnie.push_back(col);
			}
		}
		else {
			svobodnie.push_back(col);
			i--;
		}
		col++;
		if ((col != m) && ((i+1) == n)) {
			i-=1;
		}
	}
	fout << svobodnie.size() << " " << m << endl;
	col = 0;
	if (svobodnie.size() == 0) {
		fout.close();
		return;
	}
	for (size_t i = 0; i < m; i++) { //po stolbcam
		if (i == svobodnie[col]) {
			size_t c = 0;
			for (size_t j = 0; j < m; j++) { //po strokam
				if (j == i) {
					fout << 1 << " ";
				}
				else {
					if (j > i) {
						fout << 0 << " ";
					}
					else if (find(svobodnie.begin(), svobodnie.end(), j)!=svobodnie.end()) {
						fout << 0 << " ";
					}
					else {
						fout << -temp.element[i + c * m] << " ";
						c++;
					}
				}
			}
			fout << endl;
			col++;
		}
		if (col == svobodnie.size()) {
			break;
		}
	}
	fout.close();
}
#endif // !
