#ifndef COMPLEXCLASS_H
#define COMPLEXCLASS_H

#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imaginary;
public:
    Complex();
    Complex(double r, double i = 0.0);
    Complex(const Complex& other);
    ~Complex();
    double getReal() const;
    double getImaginary() const;
    void setReal(double r);
    void setImaginary(double i);
    Complex& operator=(const Complex& other);
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);
    Complex operator-() const;
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
    double magnitude() const;
    double magnitudeSquared() const;
    Complex conjugate() const;
    double phase() const;

    friend std::istream& operator>>(std::istream& is, Complex& c);
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);

    friend Complex operator+(double lhs, const Complex& rhs);
    friend Complex operator-(double lhs, const Complex& rhs);
    friend Complex operator*(double lhs, const Complex& rhs);
    friend Complex operator/(double lhs, const Complex& rhs);
};

#endif