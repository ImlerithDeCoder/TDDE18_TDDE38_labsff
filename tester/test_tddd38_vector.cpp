#include "../src/TDDD38_mathematical_vector/Vector2D.hpp"
#include <cassert>
#include <sstream>
#include <iostream>
#include <cmath>

// Testar initiering och jämförelseoperatorer
void test_initialization_and_comparison() {
    Vector2D v1{1.0, 2.0};
    Vector2D v2{1.0, 2.0};
    Vector2D v3{3.0, 4.0};

    assert(v1 == v2);
    assert(v1 != v3);
}

// Testar addition, subtraktion och negation
void test_vector_arithmetic() {
    Vector2D v1{1.0, 2.0};
    Vector2D v2{3.0, 4.0};
    
    // Addition och subtraktion
    Vector2D v3 = v1 + v2;
    assert(v3 == Vector2D(4.0, 6.0));
    
    Vector2D v4 = v2 - v1;
    assert(v4 == Vector2D(2.0, 2.0));

    // Sammansatta operatorer
    Vector2D v5{1.0, 2.0};
    v5 += v2;
    assert(v5 == Vector2D(4.0, 6.0));

    // Negering
    Vector2D v6 = -v1;
    assert(v6 == Vector2D(-1.0, -2.0));
}

// Testar multiplikation och division med konstant (skalär)
void test_scalar_arithmetic() {
    Vector2D v1{1.0, 2.0};
    
    // Multiplikation (både från höger och vänster)
    Vector2D v2 = v1 * 0.5;
    Vector2D v3 = 0.5 * v1;
    assert(v2 == Vector2D(0.5, 1.0));
    assert(v3 == Vector2D(0.5, 1.0));
    assert(v2 == v3);

    // Division (endast från höger)
    Vector2D v4 = v1 / 2.0;
    assert(v4 == Vector2D(0.5, 1.0));

    // Sammansatta operatorer
    Vector2D v5{1.0, 2.0};
    v5 *= 3.0;
    assert(v5 == Vector2D(3.0, 6.0));
    
    v5 /= 3.0;
    assert(v5 == Vector2D(1.0, 2.0));
}

// Testar skalärprodukt (dot product) och längd
void test_math_operations() {
    Vector2D v1{1.0, 2.0};
    Vector2D v2{3.0, 4.0};
    
    // Skalärprodukt (1*3 + 2*4 = 11)
    // Antar att du överlagrar operator* för två vektorer
    double dot_product = v1 * v2; 
    assert(dot_product == 11.0);

    // Längd med Pythagoras sats
    Vector2D v3{3.0, 4.0};
    assert(v3.length() == 5.0);
}

// Testar strömutmatning (operator<<)
void test_stream_output() {
    Vector2D v{3.0, 4.0};
    std::ostringstream oss;
    oss << v;
    assert(oss.str() == "(3, 4)");
}

// Testar ströminmatning (operator>>)
void test_stream_input() {
    // Test av lyckad inläsning
    Vector2D v1{0.0, 0.0};
    std::istringstream iss1("(5, 6)");
    iss1 >> v1;
    assert(v1 == Vector2D(5.0, 6.0));
    assert(!iss1.fail());

    // Test av felaktig inläsning (saknar parentes)
    Vector2D v2{1.0, 2.0};
    std::istringstream iss2("3, 4)");
    iss2 >> v2;
    assert(iss2.fail()); // Failbit ska sättas
    assert(v2 == Vector2D(1.0, 2.0)); // Objektet får inte uppdateras vid fel
}

int main() {
    test_initialization_and_comparison();
    test_vector_arithmetic();
    test_scalar_arithmetic();
    test_math_operations();
    test_stream_output();
    test_stream_input();

    std::cout << "Alla tester passerade framgångsrikt!\n";
    return 0;
}