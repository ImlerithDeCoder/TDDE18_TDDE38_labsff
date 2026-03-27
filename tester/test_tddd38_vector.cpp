#include "../src/TDDD38_mathematical_vector/vector2D.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cassert>
#include <sstream>
#include <iostream>
#include <cmath>

// Testar initiering och jämförelseoperatorer
TEST_CASE ("test_initialization_and_comparison") {
    Vector2D v1{1.0, 2.0};
    Vector2D v2{1.0, 2.0};
    Vector2D v3{3.0, 4.0};

    REQUIRE(v1 == v2);
    REQUIRE(v1 != v3);
}

// Testar addition, subtraktion och negation
TEST_CASE ("test_vector_arithmetic") {
    Vector2D v1{1.0, 2.0};
    Vector2D v2{3.0, 4.0};
    
    // Addition och subtraktion
    Vector2D v3 = v1 + v2;
    REQUIRE(v3 == Vector2D(4.0, 6.0));
    
    Vector2D v4 = v2 - v1;
    REQUIRE(v4 == Vector2D(2.0, 2.0));

    // Sammansatta operatorer
    Vector2D v5{1.0, 2.0};
    v5 += v2;
    REQUIRE(v5 == Vector2D(4.0, 6.0));

    // Negering
    Vector2D v6 = -v1;
    REQUIRE(v6 == Vector2D(-1.0, -2.0));
}

// Testar multiplikation och division med konstant
TEST_CASE ("test_scalar_arithmetic") {
    Vector2D v1{1.0, 2.0};
    
    // Multiplikation (både från höger och vänster)
    Vector2D v2 = v1 * 0.5;
    Vector2D v3 = 0.5 * v1;
    REQUIRE(v2 == Vector2D(0.5, 1.0));
    REQUIRE(v3 == Vector2D(0.5, 1.0));
    REQUIRE(v2 == v3);

    // Division (endast från höger)
    Vector2D v4 = v1 / 2.0;
    REQUIRE(v4 == Vector2D(0.5, 1.0));

    // Sammansatta operatorer
    Vector2D v5{1.0, 2.0};
    v5 *= 3.0;
    REQUIRE(v5 == Vector2D(3.0, 6.0));
    
    v5 /= 3.0;
    REQUIRE(v5 == Vector2D(1.0, 2.0));
}

// Testar skalärprodukt och längd
TEST_CASE ("test_math_operations") {
    Vector2D v1{1.0, 2.0};
    Vector2D v2{3.0, 4.0};
    
    // Skalärprodukt (1*3 + 2*4 = 11)
    double dot_product = v1 * v2; 
    REQUIRE(dot_product == 11.0);

    // Längd med Pythagoras sats
    Vector2D v3{3.0, 4.0};
    REQUIRE(v3.length() == 5.0);
}

// Testar strömutmatning (operator<<)
TEST_CASE ("test_stream_output") {
    Vector2D v{3.0, 4.0};
    std::ostringstream oss;
    oss << v;
    REQUIRE(oss.str() == "(3, 4)");
}

// Testar ströminmatning (operator>>)
TEST_CASE ("test_stream_input") {
    // Test av lyckad inläsning
    Vector2D v1{0.0, 0.0};
    std::istringstream iss1("(5, 6)");
    iss1 >> v1;
    REQUIRE(v1 == Vector2D(5.0, 6.0));
    REQUIRE(!iss1.fail());

    // Test av felaktig inläsning (saknar parentes)
    Vector2D v2{1.0, 2.0};
    std::istringstream iss2("3, 4)");
    iss2 >> v2;
    REQUIRE(iss2.fail()); // Failbit ska sättas
    REQUIRE(v2 == Vector2D(1.0, 2.0)); // Objektet får inte uppdateras vid fel

    Vector2D vector;
    std::istringstream s("ogaboga hehe (6   ,   7)");
    s >> vector;
    REQUIRE(vector == Vector2D(0, 0));
    REQUIRE(s.fail());


    std::istringstream s1("(67,  76), lala");
    s1 >> vector;
    REQUIRE(vector == Vector2D(67, 76));
    REQUIRE(!s1.fail());

    
}
