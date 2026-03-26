#include <iostream>
#include <sstream>


class Vector2D {
public:
    Vector2D(double x, double y) : x(x), y(y) {}
    Vector2D() : x(0), y(0) {}

    void negate();
    Vector2D operator-() const; //returns the negation of this vec 

    Vector2D operator+(const Vector2D& other) const;
    Vector2D& operator+=(const Vector2D& other);
    Vector2D operator+(const double num) const;
    Vector2D& operator+=(const double num);


    Vector2D operator-(const Vector2D& other) const;
    Vector2D& operator-=(const Vector2D& other);
    Vector2D operator-(const double num) const;
    Vector2D& operator-=(const double num);
    
    Vector2D operator*(double const num) const;
    Vector2D& operator*=(double const num);
    double operator*(const Vector2D& other) const;// dot product
    
    
    Vector2D operator/(double const num) const;
    Vector2D& operator/=(double const num);

    // format Vector v { 3.0 , 4.0 } --> "(3, 4)"
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);
    // should be read as "(3, 4)", if incorrect formating, set the failbit in istream, 
    // by calling the setstatus function, eg std::cin.setstate(std::ios::failbit);
    friend std::ostream& operator>>(std::istream& is, const Vector2D& vec);
    bool operator==(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;
    double length() const;





private:
    double x, y;


};
Vector2D operator+(double const num, const Vector2D& other);
Vector2D& operator+=(double const num, const Vector2D& other);
Vector2D operator-(double const num, const Vector2D& other);
Vector2D& operator-=(double const num, const Vector2D& other);
Vector2D operator*(const double num, const Vector2D& other);
Vector2D& operator*=(const double num, const Vector2D& other);

