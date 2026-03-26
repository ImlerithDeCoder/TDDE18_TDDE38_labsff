#include <iostream>
#include <sstream>


class Vector2D {
public:
    Vector2D(double x, double y) : x(x), y(y) {}
    Vector2D() : x(0), y(0) {}

    // copy constructer
    Vector2D(const Vector2D& other);
    // move constructer
    Vector2D(Vector2D&& other);    
    // destructor
    ~Vector2D() = default;
    // copy assignment
    Vector2D& operator=(const Vector2D& other);
    // move assignment
    Vector2D& operator=(Vector2D&& other);



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
    friend std::istream& operator>>(std::istream& is, Vector2D& vec);
    bool operator==(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;
    double length() const;

    
    // getters
    inline double get_x() const {return x;} 
    inline double get_y() const {return y;}

    // setters
    inline void set_x(const double x) {this->x = x;}
    inline void set_y(const double y) {this->y = y;}
    


private:
    double x, y;


};
Vector2D operator+(double const num, const Vector2D& other);
Vector2D& operator+=(double const num, Vector2D& other);
Vector2D operator-(double const num, const Vector2D& other);
Vector2D& operator-=(double const num, Vector2D& other);
Vector2D operator*(const double num, const Vector2D& other);
Vector2D& operator*=(const double num, Vector2D& other);

