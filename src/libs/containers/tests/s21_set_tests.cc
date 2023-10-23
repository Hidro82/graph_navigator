#include <limits>

#include "gtest/gtest.h"
#include "test_header.hpp"

TEST(Constructors, Default_set) {
  s21::set<int> s21;
  std::set<int> stl;
  ASSERT_TRUE(s21.empty() == stl.empty());
}

TEST(Constructors, Parametres_set) {
  s21::set<int> s21{1, 5, 6, 8, -15, 21};
  std::set<int> stl{1, 5, 6, 8, -15, 21};
  s21::set<int>::iterator s21It = s21.begin();
  std::set<int>::iterator stlIt = stl.begin();
  bool equal = true;
  for (; (s21It != s21.end()) && (stlIt != stl.end()); ++s21It, ++stlIt) {
    if (*s21It != *stlIt) {
      equal = false;
      break;
    }
  }
  ASSERT_TRUE(equal);
}

TEST(Constructors, Copy_set) {
  s21::set<int> st1{76, -68, 15, 0, 8, -15, 21};
  s21::set<int> st2(st1);
  s21::set<int>::iterator it1 = st1.begin();
  s21::set<int>::iterator it2 = st2.begin();
  bool equal = true;
  for (; (it1 != st1.end()) && (it2 != st2.end()); ++it1, ++it2) {
    if (*it1 != *it2) {
      equal = false;
      break;
    }
  }
  ASSERT_TRUE(equal);
}

TEST(Constructors, Move_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int> st2((s21::set<int> &&) st1);
  ASSERT_TRUE(st1.empty() && !st2.empty());
}

TEST(Constructors, Destructor_set) {
  s21::set<int> s21{1, 5, 6, 8, -15, 21};
  s21.~set<int>();
  ASSERT_TRUE(s21.empty());
}

TEST(Overloads, Dereferencing_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int>::iterator it1 = st1.find(135);
  ASSERT_TRUE(*it1 == 135);
}

TEST(Overloads, PreIncrement_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int>::iterator it1 = st1.begin();
  s21::set<int>::iterator it2 = ++it1;
  ASSERT_TRUE(*it1 == -4 && *it2 == -4);
}

TEST(Overloads, PostIncrement_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int>::iterator it1 = st1.begin();
  s21::set<int>::iterator it2 = it1++;
  ASSERT_TRUE(*it1 == -4 && *it2 == -15);
}

TEST(Overloads, PreDecrement_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int>::iterator it1 = st1.find(135);
  s21::set<int>::iterator it2 = --it1;
  ASSERT_TRUE(*it1 == 67 && *it2 == 67);
}

TEST(Overloads, PostDecrement_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int>::iterator it1 = st1.find(135);
  s21::set<int>::iterator it2 = it1--;
  ASSERT_TRUE(*it1 == 67 && *it2 == 135);
}

TEST(Overloads, Equal_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int>::iterator it1 = st1.find(135);
  s21::set<int>::iterator it2 = --it1;
  ASSERT_TRUE(it1 == it2);
}

TEST(Overloads, NotEqual_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int>::iterator it1 = st1.find(135);
  s21::set<int>::iterator it2 = it1--;
  ASSERT_TRUE(it1 != it2);
}

TEST(Overloads, MoveAssign_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int> st2;
  st2 = (s21::set<int> &&) st1;
  ASSERT_TRUE(st1.empty() && !st2.empty());
}

TEST(Iterators, Begin_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int>::iterator it1 = st1.begin();
  ASSERT_TRUE(*it1 == -15);
}

TEST(Iterators, End_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int>::iterator it1 = st1.find(135);
  ++it1;
  ASSERT_TRUE(it1 == st1.end());
}

TEST(Capacity, Empty_set) {
  s21::set<int> st1;
  ASSERT_TRUE(st1.empty());
}

TEST(Capacity, Size_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  ASSERT_TRUE(st1.size() == 7);
}

TEST(Capacity, MaxSize_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  ASSERT_TRUE(st1.max_size() == UINT32_MAX);
}

TEST(LookUp, Find_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int>::iterator it1 = st1.find(67);
  ASSERT_TRUE(*it1 == 67);
}

TEST(LookUp, Contains_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  ASSERT_TRUE(st1.contains(67));
}

TEST(Modifieres, Clear_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  st1.clear();
  ASSERT_TRUE(st1.empty());
}

TEST(Modifieres, Insert_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  st1.insert(-200);
  ASSERT_TRUE(*st1.begin() == -200);
}

TEST(Modifieres, Erase_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int>::iterator it1 = st1.find(8);
  st1.erase(it1);
  ASSERT_TRUE(*st1.find(8) == 0);
}

TEST(Modifieres, Swap_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int> st2{1, 3, 6, 7, -12, 21};
  st1.swap(st2);
  ASSERT_TRUE(*st1.find(21) && *st2.find(135));
}

TEST(Modifieres, Merge_set) {
  s21::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::set<int> st2{1, 3, 6, 7, -12, 21};
  st1.merge(st2);
  ASSERT_TRUE(*st1.find(21) && *st1.find(135));
}

TEST(Modifieres, Emplace_set) {
  s21::set<int> st;
  st.emplace(15000, 150000);
  ASSERT_TRUE(*st.find(15000));
}

TEST(Const, Iterator_set) {
  const s21::set<int> st{-1, 23, 5, -19};
  s21::set<int>::const_iterator it = st.find(5);
  ASSERT_TRUE(*it == 5);
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
