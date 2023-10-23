
#include "gtest/gtest.h"
#include "test_header.hpp"

TEST(Constructors, Default_multi) {
  s21::multiset<int> s21;
  std::multiset<int> stl;
  ASSERT_TRUE(s21.empty() == stl.empty());
}

TEST(Constructors, Parametres_multi) {
  s21::multiset<int> s21{1, 5, 6, 8, -15, 21};
  std::multiset<int> stl{1, 5, 6, 8, -15, 21};
  s21::multiset<int>::iterator s21It = s21.begin();
  std::multiset<int>::iterator stlIt = stl.begin();
  bool equal = true;
  for (; (s21It != s21.end()) && (stlIt != stl.end()); ++s21It, ++stlIt) {
    if (*s21It != *stlIt) {
      equal = false;
      break;
    }
  }
  ASSERT_TRUE(equal);
}

TEST(Constructors, Copy_multi) {
  s21::multiset<int> st1{76, -68, 15, 0, 8, -15, 21};
  s21::multiset<int> st2(st1);
  s21::multiset<int>::iterator it1 = st1.begin();
  s21::multiset<int>::iterator it2 = st2.begin();
  bool equal = true;
  for (; (it1 != st1.end()) && (it2 != st2.end()); ++it1, ++it2) {
    if (*it1 != *it2) {
      equal = false;
      break;
    }
  }
  ASSERT_TRUE(equal);
}

TEST(Constructors, Move_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int> st2((s21::multiset<int> &&) st1);
  ASSERT_TRUE(st1.empty() && !st2.empty());
}

TEST(Constructors, Destructor_multi) {
  s21::multiset<int> s21{1, 5, 6, 8, -15, 21};
  s21.~multiset<int>();
  ASSERT_TRUE(s21.empty());
}

TEST(Overloads, Dereferencing_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(135);
  ASSERT_TRUE(*it1 == 135);
}

TEST(Overloads, PreIncrement_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.begin();
  s21::multiset<int>::iterator it2 = ++it1;
  ASSERT_TRUE(*it1 == -4 && *it2 == -4);
}

TEST(Overloads, PostIncrement_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.begin();
  s21::multiset<int>::iterator it2 = it1++;
  ASSERT_TRUE(*it1 == -4 && *it2 == -15);
}

TEST(Overloads, PreDecrement_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(135);
  s21::multiset<int>::iterator it2 = --it1;
  ASSERT_TRUE(*it1 == 67 && *it2 == 67);
}

TEST(Overloads, PostDecrement_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(135);
  s21::multiset<int>::iterator it2 = it1--;
  ASSERT_TRUE(*it1 == 67 && *it2 == 135);
}

TEST(Overloads, Equal_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(135);
  s21::multiset<int>::iterator it2 = --it1;
  ASSERT_TRUE(it1 == it2);
}

TEST(Overloads, NotEqual_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(135);
  s21::multiset<int>::iterator it2 = it1--;
  ASSERT_TRUE(it1 != it2);
}

TEST(Overloads, MoveAssign_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int> st2;
  st2 = (s21::multiset<int> &&) st1;
  ASSERT_TRUE(st1.empty() && !st2.empty());
}

TEST(Iterators, Begin_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.begin();
  ASSERT_TRUE(*it1 == -15);
}

TEST(Iterators, End_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(135);
  ++it1;
  ASSERT_TRUE(it1 == st1.end());
}

TEST(Capacity, Empty_multi) {
  s21::multiset<int> st1;
  ASSERT_TRUE(st1.empty());
}

TEST(Capacity, Size_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  ASSERT_TRUE(st1.size() == 7);
}

TEST(Capacity, MaxSize_multi) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  ASSERT_TRUE(st1.max_size() == UINT32_MAX);
}

TEST(LookUp, Count) {
  s21::multiset<int> st1{-4, 8, 135, 67, 67, 5, -15, 1};
  ASSERT_TRUE(st1.count(67) == 2);
}

TEST(LookUp, Find) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(67);
  ASSERT_TRUE(*it1 == 67);
}

TEST(LookUp, Contains) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  ASSERT_TRUE(st1.contains(67));
}

TEST(LookUp, EqualRange) {
  std::multiset<int> st1{-4, 8, 135, 67, 67, 67, 5, -15, 1};
  std::multiset<int> st2{-4, 8, 135, 67, 67, 67, 5, -15, 1};
  auto par1 = st1.equal_range(67);
  auto par2 = st2.equal_range(67);
  ASSERT_TRUE(*par1.first == *par2.first && *par1.second == *par2.second);
}

TEST(LookUp, LowerBound) {
  s21::multiset<int> st1{-4, 8, 135, 67, 67, 67, 5, -15, 1};
  std::multiset<int> st2{-4, 8, 135, 67, 67, 67, 5, -15, 1};
  auto it1 = st1.lower_bound(67);
  auto it2 = st2.lower_bound(67);
  ASSERT_TRUE(*it1 == *it2);
}

TEST(LookUp, UpperBound) {
  s21::multiset<int> st1{-4, 8, 135, 67, 67, 67, 5, -15, 1};
  std::multiset<int> st2{-4, 8, 135, 67, 67, 67, 5, -15, 1};
  auto it1 = st1.upper_bound(67);
  auto it2 = st2.upper_bound(67);
  ASSERT_TRUE(*it1 == *it2);
}

TEST(Modifieres, Clear) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  st1.clear();
  ASSERT_TRUE(st1.empty());
}

TEST(Modifieres, Insert) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  st1.insert(-200);
  ASSERT_TRUE(*st1.begin() == -200);
}

//     -4
// -15      8
//       5     135
//     1      67
TEST(Modifieres, InsertDuplicate) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  size_t beforeAdd = st1.size();
  st1.insert(67);
  size_t afterAdd = st1.size();
  ASSERT_TRUE(beforeAdd == 7 && afterAdd == 8);
}

TEST(Modifieres, Erase) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(8);
  st1.erase(it1);
  ASSERT_TRUE(*st1.find(8) == 0);
}

TEST(Modifieres, Swap) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int> st2{1, 3, 6, 7, -12, 21};
  st1.swap(st2);
  ASSERT_TRUE(*st1.find(21) && *st2.find(135));
}

TEST(Modifieres, Merge) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int> st2{1, 3, 6, 7, -12, 21};
  st1.merge(st2);
  ASSERT_TRUE(*st1.find(21) && *st1.find(135));
}

TEST(Modifieres, Emplace) {
  s21::multiset<int> st;
  st.emplace(15000, 150000);
  ASSERT_TRUE(*st.find(15000));
}

TEST(Const, Iterator) {
  const s21::multiset<int> st{-1, 23, 5, -19};
  s21::multiset<int>::const_iterator it = st.find(5);
  ASSERT_TRUE(*it == 5);
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
