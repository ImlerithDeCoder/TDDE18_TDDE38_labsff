#include <iosteam>
#include <sstream>


class Vector2D {
public:
    Vector2D(double x, double y) : x(x), y(y) {}
    Vector2D() : x(0), y(0) {}

    void negate();
    Vector2D& operator+(const Vector2D& other);
    Vector2D& operator-(const Vector2D& other);
    Vector2D& operator*(double const num);
    Vector2D& operator/(double const num);
    ostream& operatr<<();




private:
    double x, y;


};