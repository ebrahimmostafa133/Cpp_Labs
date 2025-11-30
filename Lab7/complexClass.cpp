#include "complexClass.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

Complex::Complex() : real(0.0), imaginary(0.0) {
    cout<<"Default Constructor called"<<endl;
}
Complex::Complex(double r, double i) : real(r), imaginary(i) {
    cout<<"Parameterized Constructor called"<<endl;
}
Complex::Complex(const Complex& other) : real(other.real), imaginary(other.imaginary) {
    cout<<"Copy Constructor called"<<endl;
}
Complex::~Complex() {
    cout<<"Destructor called"<<endl;
}

double Complex::getReal() const {
    return real;
}
double Complex::getImaginary() const {
    return imaginary;
}
void Complex::setReal(double r) {
    real = r;
}
void Complex::setImaginary(double i) {
    imaginary = i;
}

Complex& Complex::operator=(const Complex& other) {
    if (this != &other) {
        real = other.real;
        imaginary = other.imaginary;
    }
    return *this;
}
Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imaginary + other.imaginary);
}
Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imaginary - other.imaginary);
}
Complex Complex::operator*(const Complex& other) const {
    double new_real = (real * other.real) - (imaginary * other.imaginary);
    double new_imaginary = (real * other.imaginary) + (imaginary * other.real);
    return Complex(new_real, new_imaginary);
}
Complex Complex::operator/(const Complex& other) const {
    double denominator = other.magnitudeSquared();

    if (denominator == 0.0) {
        throw std::runtime_error("Error: Division by zero complex number.");
    }

    double new_real = (real * other.real + imaginary * other.imaginary) / denominator;
    double new_imaginary = (imaginary * other.real - real * other.imaginary) / denominator;

    return Complex(new_real, new_imaginary);
}

Complex& Complex::operator+=(const Complex& other) {
    real += other.real;
    imaginary += other.imaginary;
    return *this;
}
Complex& Complex::operator-=(const Complex& other) {
    real -= other.real;
    imaginary -= other.imaginary;
    return *this;
}
Complex& Complex::operator*=(const Complex& other) {
    *this = *this * other;
    return *this;
}
Complex& Complex::operator/=(const Complex& other) {
    *this = *this / other;
    return *this;
}
Complex Complex::operator-() const {
    return Complex(-real, -imaginary);
}
bool Complex::operator==(const Complex& other) const {
    const double EPSILON = 1e-9;
    return (std::abs(real - other.real) < EPSILON) &&
           (std::abs(imaginary - other.imaginary) < EPSILON);
}
bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

double Complex::magnitude() const {
    return std::sqrt(magnitudeSquared());
}
double Complex::magnitudeSquared() const {
    return real * real + imaginary * imaginary;
}
Complex Complex::conjugate() const {
    return Complex(real, -imaginary);
}
double Complex::phase() const {
    return std::atan2(imaginary, real);
}

std::istream& operator>>(std::istream& is, Complex& c) {
    double r, i;
    if (is >> r >> i) {
        c.real = r;
        c.imaginary = i;
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real;
    if (c.imaginary >= 0) {
        os << " + " << c.imaginary << "i)";
    } else {
        os << " - " << std::abs(c.imaginary) << "i)";
    }
    return os;
}

Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0) + rhs;
}
Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0) - rhs;
}
Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0) * rhs;
}
Complex operator/(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0) / rhs;
}