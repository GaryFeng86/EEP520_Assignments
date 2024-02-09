#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
public:
    Complex(double real, double imaginary) : real_(real), imaginary_(imaginary) {}

    // Getter methods
    double real() const { return real_; }
    double imaginary() const { return imaginary_; }

    // Method to calculate complex conjugate
    Complex conjugate() const { return Complex(real_, -imaginary_); }

    // Overloaded operators
    Complex operator+(const Complex& other) const {
        return Complex(real_ + other.real_, imaginary_ + other.imaginary_);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real_ * other.real_ - imaginary_ * other.imaginary_,
                       real_ * other.imaginary_ + imaginary_ * other.real_);
    }

    bool operator==(const Complex& other) const {
        return real_ == other.real_ && imaginary_ == other.imaginary_;
    }

private:
    double real_;
    double imaginary_;
};

// Overloaded operator<< to print Complex numbers
std::ostream& operator<<(std::ostream& os, const Complex& complex) {
    os << complex.real() << " + " << complex.imaginary() << "i";
    return os;
}

#endif
