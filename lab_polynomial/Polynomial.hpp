#include <iostream>
#include <map>
#include <vector>
#include <exception>

using namespace std;

template<typename T>
class Polynomial {
public:
    using i64 = std::int64_t;
    using Container = typename std::map<i64, T>;
	using ConstIterator = typename Container::const_iterator;
private:
    Container coefficients_;
    
    inline static const T valueTypeZero{static_cast<T>(0)};
    
    Container& GetCoeffs() {
        return coefficients_;
    }
public:
///////////////////////STAFF////////////////////////////////
    const Container& GetCoeffs() const {
        return coefficients_;
    }
////////////////////////////////////////////////////////////

//////////////////////TASK № 1//////////////////////////////
    Polynomial(const vector<T>& vec) {
        i64 coef = 0;
        for (const auto& i : vec) {
            if (i != valueTypeZero) {
                coefficients_[coef] = i;
            }
            coef++;
        }
    }
    Polynomial(const T& value = {}) {
		if (value != valueTypeZero) {
			coefficients_[0] = value;
		}
    }
    template <typename ForwardIt>
    Polynomial(ForwardIt first, ForwardIt last) {
        i64 coef = 0;
        for (; first != last; first++) {
            if (*first != valueTypeZero) {
                coefficients_[coef] = *first;
            }
            coef++;
        }
    }
    Polynomial(const Polynomial<T>& copy) {
        this->coefficients_ = copy.coefficients_;
    }
////////////////////////////////////////////////////////////

//////////////////////TASK № 2//////////////////////////////
    friend bool operator == (const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        return lhs.GetCoeffs() == rhs.GetCoeffs();
    }

    friend bool operator != (const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        return lhs.GetCoeffs() != rhs.GetCoeffs();
    }
////////////////////////////////////////////////////////////

///////////////////////TASK № 3/////////////////////////////
    Polynomial<T>& operator= (const Polynomial<T>& rhs) {
        this->GetCoeffs() = rhs.GetCoeffs();
        return *this;
    }
    Polynomial<T>& operator+= (const Polynomial<T>& rhs) {
        for (const auto& i : rhs.GetCoeffs()) {
            this->GetCoeffs()[i.first] += i.second;
            if (this->GetCoeffs()[i.first] == valueTypeZero) {
                this->GetCoeffs().erase(i.first);
            }
        }
        return *this;
    }
    Polynomial<T>& operator-= (const Polynomial<T>& rhs) {
        for (const auto& i : rhs.GetCoeffs()) {
            this->GetCoeffs()[i.first] -= i.second;
            if (this->GetCoeffs()[i.first] == valueTypeZero) {
                this->GetCoeffs().erase(i.first);
            }
        }
        return *this;
    }
    Polynomial<T>& operator*= (const Polynomial<T>& rhs) {
        if ((this->Degree() == -1) || (rhs.Degree() == -1)) {
            this->GetCoeffs().clear();
            return *this;
        }
        else {
            Container tmp;
            for (const auto& i : this->GetCoeffs()) {
                for (const auto& j : rhs.GetCoeffs()) {
                    tmp[i.first + j.first] += (*this)[i.first] * rhs[j.first];
                    if (tmp[i.first + j.first] == valueTypeZero) {
                        tmp.erase(i.first + j.first);
                    }
                }
            }
            this->GetCoeffs() = move(tmp);
            return *this;
        }
    }
    friend Polynomial<T> operator+ (Polynomial<T> lhs, const Polynomial<T>& rhs) {
        return lhs += rhs;
    }
    friend Polynomial<T> operator- (Polynomial<T> lhs, const Polynomial<T>& rhs) {
        return lhs -= rhs;
    }
    friend Polynomial<T> operator* (Polynomial<T> lhs, const Polynomial<T>& rhs) {
        return lhs *= rhs;
    }
////////////////////////////////////////////////////////////

///////////////////////TASK № 4/////////////////////////////
    i64 Degree() const {
        if (coefficients_.size() == 0) {
            return -1;
        }
        else {
            return coefficients_.rbegin()->first;
        }
    }
    const T& operator[](size_t power) const {
        try {
		    return static_cast<i64>(power) > Degree() ? valueTypeZero : GetCoeffs().at(power);
        }
        catch(...) {
            return valueTypeZero;
        }
    }
////////////////////////////////////////////////////////////

///////////////////////TASK № 5/////////////////////////////
    T operator() (const T& givenValue) const {
        T result = valueTypeZero;
        
        for (auto i = this->Degree(); i >= 0; i--) {
			result *= givenValue;
            try {
                result += this->GetCoeffs().at(i);
            }
            catch(...) {
                
            }
		}

        return result;
    }
////////////////////////////////////////////////////////////

///////////////////////TASK № 6/////////////////////////////
    friend ostream& operator<< (ostream& os, const Polynomial& polynomial) {
        if (polynomial.Degree() == -1) {
            os << 0;
            return os;
        }
        bool first = true;
        for (auto i = polynomial.GetCoeffs().rbegin(); i != polynomial.GetCoeffs().rend(); i++) {
            if (first && (i->first == 0)) {
                os << i->second;
                first = false;
            }
            else if (first) {
                if (i->second == -1) {
                    os << '-';
                }
                else if (i->second != 1) {
                    os << i->second;
                }
                os << 'x';
                if (i->first != 1) {
                    os << '^' << i->first;
                }
                os << ' ';
                first = false;
            }
            else if (i->first == 0) {
                if (i->second > valueTypeZero) {
                    os << "+ " << i->second;
                }
                else {
                    os << "- " << -i->second;
                }
            }
            else {
                if (i->second > valueTypeZero) {
                    os << "+ ";
                    if (i->second != 1) {
                        os << i->second;
                    } 
                    os << 'x';
                    if (i->first != 1) {
                        os << '^' << i->first;
                    }
                    os << ' ';
                }
                else {
                    os << "- ";
                    if (i->second != -1) {
                        os << -i->second;
                    }
                    os << 'x';
                    if (i->first != 1) {
                        os << '^' << i->first;
                    }
                    os << ' ';
                }
            }
        }
        return os;
    }
////////////////////////////////////////////////////////////

///////////////////////TASK № 7/////////////////////////////
    ConstIterator begin() const {
        return GetCoeffs().cbegin();
    }
     
    ConstIterator end() const {
        return GetCoeffs().cend();
    }
////////////////////////////////////////////////////////////

///////////////////////TASK № 8/////////////////////////////
	friend Polynomial<T> operator&(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
		Polynomial<T> result;
        for (auto i = lhs.Degree(); i >= 0; --i) {
            result *= rhs;
            result += lhs[i];
        }
		return result;
	}
////////////////////////////////////////////////////////////

///////////////////////TASK № 9/////////////////////////////
friend Polynomial<T> operator/ (Polynomial<T> lhs, const Polynomial<T>& rhs) {
    Polynomial<T> ret;
    if (lhs.Degree() == -1) {
        return ret;
    }
    else if (rhs.Degree() == -1) {
        throw invalid_argument{"operator/ (): rhs = 0"};
    }
    else {
        Polynomial<T> tmp = lhs;
        i64 rhs_deg = rhs.Degree();
        while (tmp.Degree() >= rhs_deg) {

            T coef = tmp.GetCoeffs().rbegin()->second / rhs.GetCoeffs().rbegin()->second;

            Polynomial<T> tmpp;
            tmpp.GetCoeffs()[tmp.Degree() - rhs_deg] = coef;
            ret += tmpp;

            i64 delta = tmp.Degree() - rhs_deg;
            for (const auto& i : rhs) {
                tmp.GetCoeffs()[i.first + delta] -= coef * i.second;
                if (tmp.GetCoeffs()[i.first + delta] == tmp.valueTypeZero) {
                    tmp.GetCoeffs().erase(i.first + delta);
                }
            }
        }
        return ret;
    }
}
friend Polynomial<T> operator% (const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
   return lhs - (lhs / rhs) * rhs;
}
friend Polynomial<T> operator, (const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    if (lhs == lhs.valueTypeZero) {
        if (rhs.Degree() != -1) {
            return rhs / rhs[rhs.Degree()];
        }
        return rhs;
    }
    return (rhs % lhs, lhs);
}
/////////////////////////////////////////////////////////////
};