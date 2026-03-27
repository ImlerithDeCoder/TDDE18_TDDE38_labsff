#include "vector2D.hpp"
#include <cmath>
#include <iostream>
#include <sstream>



// the big five
Vector2D& Vector2D::operator=(const Vector2D& other) {
    //copy assignment
    if (this != &other) {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

Vector2D::Vector2D(const Vector2D& other) {
    // copy constructor, this ska alltså bli likadan som other
    *this = other;
}

Vector2D::Vector2D(Vector2D&& other) {
    // move constructor, this ska alltså bli det som other är
    *this = other;
}

Vector2D& Vector2D::operator=(Vector2D&& other) {
    //move assignment    
    *this = other;
    return *this;
}

// negation
Vector2D Vector2D::operator -() const{
    return Vector2D(-this->x, -this->y);
}

// addition operators
Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(this->x + other.x, this->y + other.y);
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2D Vector2D::operator+(const double num) const {
    return Vector2D(this->x + num, this->y + num);
}

Vector2D& Vector2D::operator+=(const double num) {
    this->x += num;
    this->y += num;
    return *this;
}

Vector2D operator+(double const num, const Vector2D& other) {
    return Vector2D(num + other.get_x(), num + other.get_y());
}

Vector2D& operator+=(double const num, Vector2D& other) {
    other.set_x(other.get_x() + num);
    other.set_y(other.get_y() + num);
    return other;
}

// subtraction
Vector2D Vector2D::operator-(const Vector2D& other) const {
    return *this + -other;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
    *this += -other;
    return *this;
}

Vector2D Vector2D::operator-(const double num) const {
    return *this + -num;
}

Vector2D& Vector2D::operator-=(const double num) {
    *this += -num;
    return *this;
}

Vector2D operator-(double const num, Vector2D& other) {
    return other - num;
}
Vector2D& operator-=(double const num, Vector2D& other) {
    other -= num;
    return other;
}

// multiplication

Vector2D Vector2D::operator*(double const num) const {
    return Vector2D(this->x * num, this->y * num);
}

Vector2D& Vector2D::operator*=(double const num) {
    this->x *= num;
    this->y *= num;
    return *this;
}

// dot product
double Vector2D::operator*(const Vector2D& other) const {
    return this->x * other.x + this->y * other.y;
}

Vector2D operator*(const double num, const Vector2D& other) {
    return other * num;
}

Vector2D& operator*=(const double num, Vector2D& other) {
    other *= num;
    return other;
}

// division
Vector2D Vector2D::operator/(double const num) const {
    return *this * (1/num);
}

Vector2D& Vector2D::operator/=(double const num) {
    *this *= 1/num;
    return *this;
}

// format Vector v { 3.0 , 4.0 } --> "(3, 4)"
std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
    os << "(" << vec.get_x() << ", " << vec.get_y() << ")";
    return os;
}
// should be read as "(3, 4)", if incorrect formating, set the failbit in istream, 
// by calling the setstatus function, eg std::cin.setstate(std::ios::failbit);
std::istream& operator>>(std::istream& is, Vector2D& vec) {
    char l, koma, r;
    double x, y; 
    is >> l >> x >> koma >> y >> r;

    if (l == '(' && r == ')' && koma == ',') {
        vec.set_x(x);
        vec.set_y(y);

    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

bool Vector2D::operator==(const Vector2D& other) const{
    return this->x == other.x && this->y == other.y;
}

bool Vector2D::operator!=(const Vector2D& other) const {
    return !(*this == other);
}

double Vector2D::length() const {
    return std::sqrt(this->x * this->x + this->y * this->y);
}
