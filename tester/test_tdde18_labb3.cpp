#include <catch2/catch_test_macros.hpp>
#include "../src/TDDE18_labb3/link_list.hpp"
#include <iostream>

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