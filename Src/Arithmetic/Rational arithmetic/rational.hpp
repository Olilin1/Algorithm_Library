/*
AUTHOR: Oliver Lindgren
*/

#include<iostream>
#include<utility>

//A datatype that stores and performs operations on fractions. T must implement the +,-,*,/,<<,>> operators. 
//In addition to that, euclids algorithm needs to work for T. It must also be possible to use T with the std::abs function.
template<typename T>
struct Rational{
    T numerator, denominator;

    Rational<T> operator+(const Rational<T>& other) const;
    Rational<T> operator-(const Rational<T>& other) const;
    Rational<T> operator*(const Rational<T>& other) const;
    Rational<T> operator/(const Rational<T>& other) const;

    void normalise();
};

template<typename T>
T gcd(T a, T b);

template<typename T>
std::istream & operator>>(std::istream & is, Rational<T>& m);

template<typename T>
std::ostream & operator<<(std::ostream & os, const Rational<T> & m);

template<typename T>
Rational<T> Rational<T>::operator+(const Rational<T>& other) const{
    Rational<T> sum;
    sum.denominator = denominator * other.denominator;
    sum.numerator = numerator * other.denominator + other.numerator * denominator;

    sum.normalise();
    return sum;
}

template<typename T>
Rational<T> Rational<T>::operator-(const Rational<T>& other) const{
    Rational<T> difference;
    difference.denominator = denominator * other.denominator;
    difference.numerator = numerator * other.denominator - other.numerator * denominator;

    difference.normalise();
    return difference;
}

template<typename T>
Rational<T> Rational<T>::operator*(const Rational<T>& other) const{
    Rational<T> product;
    product.denominator = denominator * other.denominator;
    product.numerator = numerator * other.numerator;

    product.normalise();
    return product;
}

template<typename T>
Rational<T> Rational<T>::operator/(const Rational<T>& other) const{
    Rational<T> swapped;
    swapped.denominator = other.numerator;
    swapped.numerator = other.denominator;

    Rational<T> ans = *(this) * swapped;
    ans.normalise();
    return ans;
}

template<typename T>
void Rational<T>::normalise(){
    T divisor = gcd(denominator, numerator);
    denominator /= divisor;
    numerator /= divisor;

    if(denominator < 0 && numerator < 0){
        denominator = -denominator;
        numerator = -numerator;
    }
    else if(denominator < 0){
        denominator = -denominator;
        numerator = -numerator;
    }
}

template<typename T>
std::istream & operator>>(std::istream & is, Rational<T>& m){
    is >> m.numerator >> m.denominator;
    m.normalise();
    return is;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const Rational<T> & m){
    os << m.numerator << " / " << m.denominator;
    return os;
}

template<typename T>
T gcd(T a, T b){
    a = std::abs(a);
    b = std::abs(b);
    if(a > b){
        std::swap(a,b);
    }

    if (a == 0)
        return b;
    return gcd(b % a, a);
}

