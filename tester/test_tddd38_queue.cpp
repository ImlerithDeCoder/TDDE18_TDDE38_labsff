#include "../src/TDDD38_static_queue/queue.hpp"
#include "catch2/catch_test_macros.hpp"
#include <cassert>



TEST_CASE("gives tests") {
  // create empty queue of int, with a maximum of 5 elements
  Queue<int, 5> q1{};

  // const-reference to q1, used to check that all const functions
  // work correctly
  Queue<int, 5> const& q2{q1};
  
  REQUIRE(q1.empty());
  REQUIRE(!q1.full());

  // calling front on empty queues should throw an exception
  REQUIRE_THROWS(q1.front());
  REQUIRE_THROWS(q2.front());

  for (int i{10}; i > 0; --i)
  {
    q1.enqueue(i);
    REQUIRE(!q1.empty());
    REQUIRE(!q1.full());

    REQUIRE(q1.front() == i);
    REQUIRE(q2.front() == i);
    
    REQUIRE(q1.dequeue() == i);
    REQUIRE(q1.empty());
  }

  for (int i{1}; i <= 4; ++i)
  {
    q1.enqueue(i);
    REQUIRE(!q1.empty());
    REQUIRE(!q1.full());
  }

  q1.enqueue(5);
  REQUIRE(!q1.empty());
  REQUIRE(q1.full());
  
  REQUIRE_THROWS(q1.enqueue(6));
  
  Queue<int, 10> q3{q1.copy_and_expand<5>()};

  REQUIRE(!q3.empty());
  REQUIRE(!q3.full());
  
  for (int i{1}; i <= 4; ++i)
  {
    REQUIRE(q1.front() == i);
    REQUIRE(q2.front() == i);
    
    REQUIRE(q1.dequeue() == i);
    REQUIRE(!q1.empty());
    REQUIRE(!q1.full());
  }
  
  REQUIRE(q1.front() == 5);
  REQUIRE(q2.front() == 5);
  
  REQUIRE(q1.dequeue() == 5);

  REQUIRE_THROWS(q1.front());
  REQUIRE_THROWS(q2.front());
  
  for (int i{1}; i <= 4; ++i)
  {
    REQUIRE(q3.front() == i);
    REQUIRE(q3.dequeue() == i);

    REQUIRE(!q3.empty());
    REQUIRE(!q3.full());
  }

  REQUIRE(q3.front() == 5);
  REQUIRE(q3.dequeue() == 5);
  REQUIRE(q3.empty());
  REQUIRE(!q3.full());
  
}