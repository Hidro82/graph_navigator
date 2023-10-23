// #include <limits>
// #include <queue>
#include "gtest/gtest.h"
#include "test_header.hpp"
// #include "queue.hpp"

TEST(Constructors, Default) {
  s21::queue<int> s21;
  std::queue<int> stl;
  ASSERT_TRUE(s21.empty() == stl.empty());
}

TEST(Constructors, Parametres) {
  s21::queue<int> s21{1, 5, 6, 8, -15, 21};
  std::queue<int> stl;
  stl.push(21);
  ASSERT_TRUE(s21.back() == stl.back());
}

TEST(Constructors, Copy) {
  s21::queue<int> qu1{1, 5, 6, 8, -15, 21};
  s21::queue<int> qu2(qu1);
  ASSERT_TRUE(qu1.back() == qu2.back());
}

TEST(Constructors, Move) {
  s21::queue<int> qu1{1, 5, 6, 8, -15, 21};
  s21::queue<int> qu2((s21::queue<int> &&) qu1);
  ASSERT_TRUE(qu1.empty() && (qu2.back() == 21));
}

TEST(Constructors, Destructor) {
  s21::queue<int> qu1{1, 5, 6, 8, -15, 21};
  qu1.~queue();
  ASSERT_TRUE(qu1.empty());
}

TEST(Overload, Move) {
  s21::queue<int> qu1{1, 5, 6, 8, -15, 21};
  s21::queue<int> qu2;
  qu2 = (s21::queue<int> &&) qu1;
  ASSERT_TRUE(qu1.empty() && (qu2.back() == 21));
}

TEST(Overload, Copy) {
  s21::queue<int> qu1{1, 5, 6, 8, -15, 21};
  s21::queue<int> qu2;
  qu2 = qu1;
  ASSERT_TRUE(qu1.back() == qu2.back());
}

TEST(ElementAccess, Front) {
  s21::queue<int> qu1{1, 5, 6, 8, -15, 21};
  ASSERT_TRUE(qu1.front() == 1);
}

TEST(ElementAccess, Back) {
  s21::queue<int> qu1{1, 5, 6, 8, -15, 21};
  ASSERT_TRUE(qu1.back() == 21);
}

TEST(Capacity, Empty) {
  s21::queue<int> qu1{1, 5, 6, 8, -15, 21};
  ASSERT_TRUE(!qu1.empty());
}

TEST(Capacity, Size) {
  s21::queue<int> qu1{1, 5, 6, 8, -15, 21};
  ASSERT_TRUE(qu1.size() == 6);
}

TEST(Modifiers, Push) {
  s21::queue<int> qu1{1, 5, 6, 8, -15, 21};
  qu1.push(200);
  ASSERT_TRUE(qu1.back() == 200);
}

TEST(Modifiers, Pop) {
  s21::queue<int> qu1{1, 5, 6, 8, -15, 21};
  qu1.pop();
  ASSERT_TRUE(qu1.front() == 5);
}

TEST(Modifiers, Swap) {
  s21::queue<int> qu1{1, 5, 6, 8, -15, 21};
  s21::queue<int> qu2{3, 95, -6, 14, 5, 132, 98};
  qu1.swap(qu2);
  ASSERT_TRUE(qu1.front() == 3 && qu2.front() == 1);
}

TEST(Modifiers, Emplace) {
  s21::queue<int> qu;
  qu.emplace(15000, 150000);
  ASSERT_TRUE(qu.back() == 150000);
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
