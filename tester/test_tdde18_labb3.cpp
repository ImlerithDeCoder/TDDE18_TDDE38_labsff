#include <catch2/catch_test_macros.hpp>
#include "../src/TDDE18_labb3/link_list.hpp"
#include <iostream>
#include <utility> // För std::move

TEST_CASE("inserting") {
    SECTION("simple insert") {
        LinkList<int> list;
        list.insert(5);
        list.insert(3);
        list.insert(7);
        list.insert(7);
        list.insert(6);
        list.insert(8);
        list.insert(7);
        list.insert(2);

        REQUIRE(list.to_string() == "[2, 3, 5, 6, 7, 7, 7, 8]");
        
        REQUIRE(list.at(0) == 2);
        REQUIRE(list.at(1) == 3);
        REQUIRE(list.at(2) == 5);

        REQUIRE(list.length() == 8);

        

    };
}
TEST_CASE("removing") {
    SECTION("remove") {
        LinkList<int> list;
        list.insert(5);
        list.insert(3);
        list.insert(7);
        

        list.remove(1);
        REQUIRE(list.to_string() == "[3, 7]");
        
        
        list.remove(1);
        REQUIRE(list.to_string() == "[3]");

        list.insert(6);
        list.insert(8);
        list.insert(9);

        list.remove(0);
        REQUIRE(list.to_string() == "[6, 8, 9]");

        list.remove(list.length()-1);
        REQUIRE(list.to_string() == "[6, 8]");
    };
}

TEST_CASE( "Create an empty list" ) {
  LinkList<int> l;

  REQUIRE( l.is_empty() == true );
  REQUIRE( l.length() == 0 );
}

TEST_CASE("The Big Five: Minneshantering och kopiering") {
    
    SECTION("Copy Constructor gör en djup kopia") {
        LinkList<int> original;
        original.insert(10);
        original.insert(20);

        // Anropar copy constructor
        LinkList<int> copy(original);

        REQUIRE(copy.to_string() == "[10, 20]");
        REQUIRE(copy.length() == 2);

        // Bevisa djup kopia: ändra i originalet, kopian ska förbli orörd
        original.insert(15);
        REQUIRE(original.to_string() == "[10, 15, 20]");
        REQUIRE(copy.to_string() == "[10, 20]"); 
    }

    SECTION("Copy Assignment Operator gör en djup kopia") {
        LinkList<int> original;
        original.insert(1);
        original.insert(2);

        LinkList<int> assigned;
        assigned.insert(99); // Befintlig data som ska skrivas över

        // Anropar copy assignment operator
        assigned = original;

        REQUIRE(assigned.to_string() == "[1, 2]");
        REQUIRE(assigned.length() == 2);
        REQUIRE(original.to_string() == "[1, 2]");

        // Bevisa djup kopia: ta bort från originalet, assigned ska förbli orörd
        original.remove(0);
        REQUIRE(original.to_string() == "[2]");
        REQUIRE(assigned.to_string() == "[1, 2]");

        // Testa self-assignment (ska inte krascha eller förstöra datan)
        assigned = assigned;
        REQUIRE(assigned.to_string() == "[1, 2]");
    }

    SECTION("Move Constructor stjäl minnet effektivt") {
        LinkList<int> dying_list;
        dying_list.insert(5);
        dying_list.insert(10);

        // Anropar move constructor
        LinkList<int> moved_to(std::move(dying_list));

        // moved_to ska ha datan
        REQUIRE(moved_to.to_string() == "[5, 10]");
        REQUIRE(moved_to.length() == 2); 
    }

    SECTION("Move Assignment Operator stjäl minne till ett existerande objekt") {
        LinkList<int> dying_list;
        dying_list.insert(42);
        dying_list.insert(43);

        LinkList<int> existing;
        existing.insert(1);
        existing.insert(2);

        // Anropar move assignment operator
        existing = std::move(dying_list);

        // existing har nu tagit över dying_lists gamla data
        REQUIRE(existing.to_string() == "[42, 43]");
        REQUIRE(existing.length() == 2);

        // Testa self-move assignment (ska inte krascha)
        existing = std::move(existing);
        REQUIRE(existing.to_string() == "[42, 43]");
    }

    SECTION("Destructor (Indirekt test via scoping)") {
        // Det är svårt att testa minnesläckor direkt i standard-C++ utan externa verktyg,
        // men vi kan se till att konstruktion och destruktion i en loop inte kraschar.
        REQUIRE_NOTHROW([]() {
            for (int i = 0; i < 100; ++i) {
                LinkList<int> temp;
                temp.insert(1);
                temp.insert(2);
                temp.insert(3);
                // temp förstörs här i varje iteration.
                // Om destuktorn var trasig skulle vi eventuellt se en segfault.
            }
        }());
    }
}