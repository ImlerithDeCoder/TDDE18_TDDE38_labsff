#include <catch2/catch_test_macros.hpp>
#include "../src/TDDE18_labb3/link_list.hpp"

TEST_CASE("inserting") {
    SECTION("simple insert") {
        LinkList<int> list;
        list.insert(5);
        list.insert(3);
        //list.insert(7);
        //list.insert(7);
        //list.insert(6);
        //list.insert(8);
        //list.insert(7);

        std::cout << list.to_string() << std::endl;

        REQUIRE(list.to_string() == "[3, 5, 6, 7, 7, 7, 8]");
        
        REQUIRE(list.at(0) == 3);
        REQUIRE(list.at(1) == 5);
        REQUIRE(list.at(2) == 7);
        
    };


}