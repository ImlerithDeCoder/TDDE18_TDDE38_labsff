#include <catch2/catch_test_macros.hpp>
#include "../src/TDDE18_labb2/main.cpp"
#include <sstream>

TEST_CASE("Konstruktorer och validering (is_valid)", "[Time]") {
    SECTION("Standardkonstruktorn ger 00:00:00 och är giltig") {
        Time t;
        REQUIRE(t.is_valid() == true);
    }

    SECTION("Konstruktor med argument (sek, min, tim) sätter rätt värden") {
        Time t(15, 30, 12); // 15 sek, 30 min, 12 timmar
        REQUIRE(t.is_valid() == true);
    }

    SECTION("Ogiltiga tider fångas upp av is_valid") {
        Time t1(60, 0, 0); // 60 sekunder är ogiltigt
        REQUIRE(t1.is_valid() == false);

        Time t2(0, 60, 0); // 60 minuter är ogiltigt
        REQUIRE(t2.is_valid() == false);

        Time t3(0, 0, 24); // 24 timmar är ogiltigt (ska vara 0-23)
        REQUIRE(t3.is_valid() == false);

        Time t4(-1, 15, 12); // Negativa värden är ogiltiga
        REQUIRE(t4.is_valid() == false);

        Time t5(36, 36, 24);
        REQUIRE(t5.is_valid() == false);

    }
}

TEST_CASE("Konvertering till text (to_string) och is_am", "[Time]") {
    SECTION("24-timmarsformat (standard)") {
        Time t(15, 30, 14); // 14:30:15
        REQUIRE(t.to_string(false) == "14:30:15");
    }

    SECTION("12-timmarsformat med AM/PM") {
        Time t_pm(15, 30, 14); // 14:30:15
        REQUIRE(t_pm.to_string(true) == "2:30:15[ PM]"); // Borde vara 2 på eftermiddagen
        REQUIRE(t_pm.is_am() == false);

        Time t_am(15, 30, 9); // 09:30:15
        REQUIRE(t_am.to_string(true) == "9:30:15[ AM]");
        REQUIRE(t_am.is_am() == true);

    }
}

TEST_CASE("Matematiska operatorer (+, ++, --)", "[Time]") {
    Time t(0, 0, 12); // 12:00:00

    SECTION("Addition med sekunder (operator+)") {
        Time t2 = t + 3661; // Lägg till 1 timme, 1 minut och 1 sekund
        REQUIRE(t2 == Time(1, 1, 13)); 
    }

    SECTION("Prefix increment (operator++)") {
        ++t;
        REQUIRE(t == Time(1, 0, 12)); // En sekund mer
    }

    SECTION("Prefix decrement (operator--)") {
        --t;
        REQUIRE(t == Time(59, 59, 11)); // En sekund mindre blir 11:59:59
    }
}

TEST_CASE("Jämförelseoperatorer (==, !=, <, >)", "[Time]") {
    Time t1(10, 20, 10);
    Time t2(10, 20, 10);
    Time t3(15, 20, 10); // 5 sekunder mer än t1

    SECTION("Lika med och inte lika med") {
        REQUIRE(t1 == t2);
        REQUIRE(t1 != t3);
    }

    SECTION("Större än och mindre än") {
        REQUIRE(t1 < t3);
        REQUIRE(t3 > t1);
        REQUIRE(t1 <= t2);
        REQUIRE(t3 >= t1);
    }
}

TEST_CASE("Strömutmatning och ströminmatning (<< och >>)", "[Time]") {
    SECTION("Utmatning (operator<<)") {
        std::stringstream ss;
        Time t(5, 10, 8); // 08:10:05
        ss << t;
        REQUIRE(ss.str() == "8:10:5"); // Eller hur nu exakt din to_string bygger upp det
    }

    SECTION("Inmatning (operator>>)") {
        std::stringstream ss("15 : 30 : 14 "); 
        Time t;
        ss >> t;
        // Inmatningen bör konvertera detta till rätt interna sekunder/minuter/timmar (24h)
        REQUIRE(t == Time(15, 30, 14)); 
    }


}