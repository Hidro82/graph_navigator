#include <gtest/gtest.h>

// #include <list>
// #include <queue>
// #include <stack>
// #include <vector>
// #include <array>

#include "test_header.hpp"

// #include "../vector/s21_vector.h"
// #include "../array/s21_array.h"
// #include "../stack/s21_stack.h"
// #include "../abstract/s21_abstract.h"

namespace s21 {
// >>>>>>> VECTOR <<<<<<<<

class Test_vector {
 public:
  s21::Vector<int> empty_Vector;
  s21::Vector<int> five_Vector{1, 2, 3, 4, 5};
  s21::Vector<int> four_Vector{1, 2, 3, 4};
  s21::Vector<char> char_Vector;
  s21::Vector<float> float_Vector;
  s21::Vector<double> double_Vector;
  std::vector<int> origin_five_vector{1, 2, 3, 4, 5};
  std::vector<int> origin_four_vector{1, 2, 3, 4};
  std::vector<int> origin_int;
  std::vector<char> origin_char;
  std::vector<float> origin_float;
  std::vector<double> origin_double;
  std::vector<int>::iterator it_origin = origin_five_vector.begin();
  s21::Vector<int> s21_vector_lesser{534789, 2479056, 987654, 30, 73, 1, 35674};
  std::vector<int> std_vector_lesser{534789, 2479056, 987654, 30, 73, 1, 35674};
  s21::Vector<int> s21_vector_copy_lesser{1, 2};
  std::vector<int> std_vector_copy_lesser{1, 2};
  s21::Vector<int> s21_vector_copy_larger{9, 8, 7, 6, 5, 4, 3};
  std::vector<int> std_vector_copy_larger{9, 8, 7, 6, 5, 4, 3};
  s21::Vector<int> s21_vector_larger{1, 2};
  std::vector<int> std_vector_larger{1, 2};
  s21::Vector<int> s21_vector_ass{-333, -999, 123, 11765, 3};
  std::vector<int> std_vector_ass{-333, -999, 123, 11765, 3};
  s21::Vector<int> s21_vector_move{1, 2};
  std::vector<int> std_vector_move{1, 2};
  s21::Vector<int> s21_vector_s{111, 222, 333, 444, 555};
  std::vector<int> std_vector_s{111, 222, 333, 444, 555};
  s21::Vector<int> s21_vector_swap{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> std_vector_swap{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
};

TEST(Vector, constructor_default) {
  Test_vector logger;
  EXPECT_EQ(logger.empty_Vector.size(), logger.origin_int.size());
  EXPECT_EQ(logger.empty_Vector.capacity(), logger.origin_int.capacity());
  EXPECT_EQ(logger.empty_Vector.empty(), logger.origin_int.empty());
}

TEST(Vector, constructor_init) {
  s21::Vector<int> s21_vector(3);
  std::vector<int> std_vector(3);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, constructor_initializer_lit) {
  Test_vector logger;
  EXPECT_EQ(logger.five_Vector[0], logger.origin_five_vector[0]);
  EXPECT_EQ(logger.five_Vector[4], logger.origin_five_vector[4]);
  EXPECT_EQ(logger.five_Vector.size(), logger.origin_five_vector.size());
  EXPECT_EQ(logger.five_Vector.capacity(),
            logger.origin_five_vector.capacity());
  EXPECT_EQ(logger.five_Vector.empty(), logger.origin_five_vector.empty());
}

TEST(Vector, constructor_copy_empty) {
  Test_vector logger;
  s21::Vector<int> s21_copy(logger.empty_Vector);
  std::vector<int> std_copy(logger.origin_int);
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
}

TEST(Vector, constructor_copy_not_empty) {
  Test_vector logger;
  s21::Vector<int> s21_copy(logger.five_Vector);
  std::vector<int> std_copy(logger.origin_five_vector);
  EXPECT_EQ(s21_copy[0], std_copy[0]);
  EXPECT_EQ(s21_copy[s21_copy.size() - 1], std_copy[std_copy.size() - 1]);
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
}

TEST(Vector, constructor_move_not_empty) {
  Test_vector logger;
  s21::Vector<int> s21_copy(std::move(logger.five_Vector));
  std::vector<int> std_copy(std::move(logger.origin_five_vector));
  EXPECT_EQ(s21_copy[0], std_copy[0]);
  EXPECT_EQ(s21_copy[s21_copy.size() - 1], std_copy[std_copy.size() - 1]);
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
}

TEST(Vector, constructor_move_empty) {
  Test_vector logger;
  s21::Vector<int> s21_copy(std::move(logger.empty_Vector));
  std::vector<int> std_copy(std::move(logger.origin_int));
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
}

TEST(Vector, operator_copy_empty) {
  Test_vector logger;
  s21::Vector<int> s21_copy;
  std::vector<int> std_copy;
  s21_copy = logger.empty_Vector;
  std_copy = logger.origin_int;
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
}

TEST(Vector, operator_copy_not_empty) {
  Test_vector logger;
  s21::Vector<int> s21_copy;
  std::vector<int> std_copy;
  s21_copy = logger.five_Vector;
  std_copy = logger.origin_five_vector;
  EXPECT_EQ(s21_copy[0], std_copy[0]);
  EXPECT_EQ(s21_copy[s21_copy.size() - 1], std_copy[std_copy.size() - 1]);
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
}

TEST(Vector, operator_move_not_empty) {
  Test_vector logger;
  s21::Vector<int> s21_copy;
  std::vector<int> std_copy;
  s21_copy = std::move(logger.five_Vector);
  std_copy = std::move(logger.origin_five_vector);
  EXPECT_EQ(s21_copy[0], std_copy[0]);
  EXPECT_EQ(s21_copy[s21_copy.size() - 1], std_copy[std_copy.size() - 1]);
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
}

TEST(Vector, operator_move_empty) {
  Test_vector logger;
  s21::Vector<int> s21_copy;
  std::vector<int> std_copy;
  s21_copy = std::move(logger.empty_Vector);
  std_copy = std::move(logger.origin_int);

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
}

TEST(Vector, copy_assignment_lesser_buffer) {
  Test_vector logger;
  logger.s21_vector_copy_lesser = logger.s21_vector_lesser;
  logger.std_vector_copy_lesser = logger.std_vector_lesser;
  EXPECT_EQ(logger.s21_vector_copy_lesser[0], logger.std_vector_copy_lesser[0]);
  EXPECT_EQ(logger.s21_vector_copy_lesser[1], logger.std_vector_copy_lesser[1]);
  EXPECT_EQ(logger.s21_vector_copy_lesser[2], logger.std_vector_copy_lesser[2]);
  EXPECT_EQ(logger.s21_vector_copy_lesser[3], logger.std_vector_copy_lesser[3]);
  EXPECT_EQ(logger.s21_vector_copy_lesser[4], logger.std_vector_copy_lesser[4]);
  EXPECT_EQ(logger.s21_vector_copy_lesser[5], logger.std_vector_copy_lesser[5]);
  EXPECT_EQ(logger.s21_vector_copy_lesser[6], logger.std_vector_copy_lesser[6]);
  EXPECT_EQ(logger.s21_vector_copy_lesser.size(),
            logger.std_vector_copy_lesser.size());
  EXPECT_EQ(logger.s21_vector_copy_lesser.capacity(),
            logger.std_vector_copy_lesser.capacity());
  EXPECT_EQ(logger.s21_vector_copy_lesser.empty(),
            logger.std_vector_copy_lesser.empty());
}

TEST(Vector, copy_assignment_larger_buffer) {
  Test_vector logger;
  logger.s21_vector_copy_larger = logger.s21_vector_copy_larger;
  logger.std_vector_copy_larger = logger.std_vector_copy_larger;
  EXPECT_EQ(logger.s21_vector_copy_larger[0], logger.std_vector_copy_larger[0]);
  EXPECT_EQ(logger.s21_vector_copy_larger[1], logger.std_vector_copy_larger[1]);
  EXPECT_EQ(logger.s21_vector_copy_larger.size(),
            logger.std_vector_copy_larger.size());
  EXPECT_EQ(logger.s21_vector_copy_larger.capacity(),
            logger.std_vector_copy_larger.capacity());
  EXPECT_EQ(logger.s21_vector_copy_larger.empty(),
            logger.std_vector_copy_larger.empty());
}

TEST(Vector, move_assigment) {
  Test_vector logger;
  logger.s21_vector_move = std::move(logger.s21_vector_ass);
  logger.std_vector_move = std::move(logger.std_vector_ass);
  EXPECT_EQ(logger.s21_vector_move[0], logger.std_vector_move[0]);
  EXPECT_EQ(logger.s21_vector_move[1], logger.std_vector_move[1]);
  EXPECT_EQ(logger.s21_vector_move[2], logger.std_vector_move[2]);
  EXPECT_EQ(logger.s21_vector_move[3], logger.std_vector_move[3]);
  EXPECT_EQ(logger.s21_vector_move[4], logger.std_vector_move[4]);
  EXPECT_EQ(logger.s21_vector_move.size(), logger.std_vector_move.size());
  EXPECT_EQ(logger.s21_vector_move.capacity(),
            logger.std_vector_move.capacity());
  EXPECT_EQ(logger.s21_vector_move.empty(), logger.std_vector_move.empty());
  EXPECT_EQ(logger.s21_vector_ass.size(), logger.std_vector_ass.size());
  EXPECT_EQ(logger.s21_vector_ass.capacity(), logger.std_vector_ass.capacity());
  EXPECT_EQ(logger.s21_vector_ass.empty(), logger.std_vector_ass.empty());
}

TEST(Vector, function_at) {
  Test_vector logger;
  EXPECT_EQ(logger.five_Vector.at(0), logger.origin_five_vector.at(0));
  EXPECT_EQ(logger.five_Vector.at(1), logger.origin_five_vector.at(1));
  EXPECT_EQ(logger.five_Vector.at(2), logger.origin_five_vector.at(2));
  EXPECT_EQ(logger.five_Vector.at(3), logger.origin_five_vector.at(3));
}

TEST(Vector, operator_square) {
  Test_vector logger;
  EXPECT_EQ(logger.five_Vector[0], logger.origin_five_vector[0]);
  EXPECT_EQ(logger.five_Vector[1], logger.origin_five_vector[1]);
  EXPECT_EQ(logger.five_Vector[2], logger.origin_five_vector[2]);
  EXPECT_EQ(logger.five_Vector[3], logger.origin_five_vector[3]);
}

TEST(Vector, function_front) {
  Test_vector logger;
  EXPECT_EQ(logger.origin_five_vector.front(), logger.five_Vector.front());
}

TEST(Vector, function_back) {
  Test_vector logger;
  EXPECT_EQ(logger.five_Vector.back(), logger.origin_five_vector.back());
}

TEST(Vector, iterator_element_access) {
  s21::Vector<char> s21_vector{'p', 'e', 'r', 'f', 'o',
                               'r', 'a', 't', 'o', 'r'};
  std::vector<char> std_vector{'p', 'e', 'r', 'f', 'o',
                               'r', 'a', 't', 'o', 'r'};
  s21::Vector<char>::iterator s21_it = s21_vector.begin();
  std::vector<char>::iterator std_it = std_vector.begin();
  while (s21_it != s21_vector.end()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
}

TEST(vector_iterator_suit, const_iterator_element_access) {
  s21::Vector<char> s21_vector{'p', 'e', 'r', 'f', 'o',
                               'r', 'a', 't', 'o', 'r'};
  std::vector<char> std_vector{'p', 'e', 'r', 'f', 'o',
                               'r', 'a', 't', 'o', 'r'};
  s21::Vector<char>::const_iterator s21_it = s21_vector.begin();
  std::vector<char>::const_iterator std_it = std_vector.begin();
  while (s21_it != s21_vector.end()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
}

TEST(Vector, function_data) {
  Test_vector logger;
  EXPECT_EQ(*logger.five_Vector.data(), *logger.origin_five_vector.data());
}

TEST(Vector, function_data_e) {
  s21::Vector<char> s21_vector_empty;
  std::vector<char> std_vector_empty;
  EXPECT_EQ(s21_vector_empty.data(), nullptr);
  EXPECT_EQ(std_vector_empty.data(), nullptr);
  s21::Vector<char> s21_vector{'L', 'I', 'Z', 'A'};
  std::vector<char> std_vector{'L', 'I', 'Z', 'A'};
  EXPECT_NE(s21_vector.data(), nullptr);
  EXPECT_NE(std_vector.data(), nullptr);
}

TEST(Vector, function_insert_begin) {
  s21::Vector<int> s21_vector{1, 2, 3, 5, 9, 10};
  std::vector<int> std_vector{1, 2, 3, 5, 9, 10};
  s21::Vector<int>::iterator s21_it = s21_vector.begin();
  std::vector<int>::iterator std_it = std_vector.begin();
  s21_it = s21_vector.insert(s21_it, 666);
  std_it = std_vector.insert(std_it, 666);
  EXPECT_EQ(*s21_it, *std_it);
  EXPECT_EQ(s21_vector.at(0), std_vector.at(0));
  EXPECT_EQ(s21_vector.at(1), std_vector.at(1));
  EXPECT_EQ(s21_vector.at(2), std_vector.at(2));
  EXPECT_EQ(s21_vector.at(3), std_vector.at(3));
  EXPECT_EQ(s21_vector.at(4), std_vector.at(4));
  EXPECT_EQ(s21_vector.at(5), std_vector.at(5));
  EXPECT_EQ(s21_vector.at(6), std_vector.at(6));
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, function_insert_mid) {
  s21::Vector<int> s21_vector{1, 2, 3, 5, 9, 10};
  std::vector<int> std_vector{1, 2, 3, 5, 9, 10};
  s21::Vector<int>::iterator s21_it = s21_vector.begin();
  std::vector<int>::iterator std_it = std_vector.begin();
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  s21_it = s21_vector.insert(s21_it, 666);
  std_it = std_vector.insert(std_it, 666);
  EXPECT_EQ(*s21_it, *std_it);
  EXPECT_EQ(s21_vector.at(0), std_vector.at(0));
  EXPECT_EQ(s21_vector.at(1), std_vector.at(1));
  EXPECT_EQ(s21_vector.at(2), std_vector.at(2));
  EXPECT_EQ(s21_vector.at(3), std_vector.at(3));
  EXPECT_EQ(s21_vector.at(4), std_vector.at(4));
  EXPECT_EQ(s21_vector.at(5), std_vector.at(5));
  EXPECT_EQ(s21_vector.at(6), std_vector.at(6));
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, function_insert_end) {
  s21::Vector<int> s21_vector{1, 2, 3, 5, 9, 10};
  std::vector<int> std_vector{1, 2, 3, 5, 9, 10};
  s21::Vector<int>::iterator s21_it = s21_vector.end();
  std::vector<int>::iterator std_it = std_vector.end();
  s21_it = s21_vector.insert(s21_it, 666);
  std_it = std_vector.insert(std_it, 666);
  EXPECT_EQ(*s21_it, *std_it);
  EXPECT_EQ(s21_vector.at(0), std_vector.at(0));
  EXPECT_EQ(s21_vector.at(1), std_vector.at(1));
  EXPECT_EQ(s21_vector.at(2), std_vector.at(2));
  EXPECT_EQ(s21_vector.at(3), std_vector.at(3));
  EXPECT_EQ(s21_vector.at(4), std_vector.at(4));
  EXPECT_EQ(s21_vector.at(5), std_vector.at(5));
  EXPECT_EQ(s21_vector.at(6), std_vector.at(6));
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, function_insert_multi) {
  s21::Vector<int> s21_vector{1, 2, 3, 5, 9, 10};
  std::vector<int> std_vector{1, 2, 3, 5, 9, 10};
  s21::Vector<int>::iterator s21_it = s21_vector.begin();
  std::vector<int>::iterator std_it = std_vector.begin();
  s21_it = s21_vector.insert(s21_it, 666);
  std_it = std_vector.insert(std_it, 666);
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  s21_it = s21_vector.insert(s21_it, 666);
  std_it = std_vector.insert(std_it, 666);
  EXPECT_EQ(*s21_it, *std_it);
  EXPECT_EQ(s21_vector.at(0), std_vector.at(0));
  EXPECT_EQ(s21_vector.at(1), std_vector.at(1));
  EXPECT_EQ(s21_vector.at(2), std_vector.at(2));
  EXPECT_EQ(s21_vector.at(3), std_vector.at(3));
  EXPECT_EQ(s21_vector.at(4), std_vector.at(4));
  EXPECT_EQ(s21_vector.at(5), std_vector.at(5));
  EXPECT_EQ(s21_vector.at(6), std_vector.at(6));
  EXPECT_EQ(s21_vector.at(7), std_vector.at(7));
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, function_erase_begin) {
  s21::Vector<int> s21_vector{1, 2, 3, 5, 9, 10};
  std::vector<int> std_vector{1, 2, 3, 5, 9, 10};
  s21::Vector<int>::iterator s21_it = s21_vector.begin();
  std::vector<int>::iterator std_it = std_vector.begin();
  s21_vector.erase(s21_it);
  std_vector.erase(std_it);
  EXPECT_EQ(s21_vector.at(0), std_vector.at(0));
  EXPECT_EQ(s21_vector.at(1), std_vector.at(1));
  EXPECT_EQ(s21_vector.at(2), std_vector.at(2));
  EXPECT_EQ(s21_vector.at(3), std_vector.at(3));
  EXPECT_EQ(s21_vector.at(4), std_vector.at(4));
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, function_erase_mid) {
  s21::Vector<int> s21_vector{1, 2, 3, 5, 9, 10};
  std::vector<int> std_vector{1, 2, 3, 5, 9, 10};
  s21::Vector<int>::iterator s21_it = s21_vector.begin();
  std::vector<int>::iterator std_it = std_vector.begin();
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  s21_vector.erase(s21_it);
  std_vector.erase(std_it);
  EXPECT_EQ(s21_vector.at(0), std_vector.at(0));
  EXPECT_EQ(s21_vector.at(1), std_vector.at(1));
  EXPECT_EQ(s21_vector.at(2), std_vector.at(2));
  EXPECT_EQ(s21_vector.at(3), std_vector.at(3));
  EXPECT_EQ(s21_vector.at(4), std_vector.at(4));
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, function_erase_end) {
  s21::Vector<int> s21_vector{1, 2, 3, 5, 9, 10};
  std::vector<int> std_vector{1, 2, 3, 5, 9, 10};
  s21::Vector<int>::iterator s21_it = s21_vector.end() - 1;
  std::vector<int>::iterator std_it = std_vector.end() - 1;
  s21_vector.erase(s21_it);
  std_vector.erase(std_it);
  EXPECT_EQ(s21_vector.at(0), std_vector.at(0));
  EXPECT_EQ(s21_vector.at(1), std_vector.at(1));
  EXPECT_EQ(s21_vector.at(2), std_vector.at(2));
  EXPECT_EQ(s21_vector.at(3), std_vector.at(3));
  EXPECT_EQ(s21_vector.at(4), std_vector.at(4));
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, function_erase_multi) {
  s21::Vector<int> s21_vector{1, 2, 3, 5, 9, 10};
  std::vector<int> std_vector{1, 2, 3, 5, 9, 10};
  s21::Vector<int>::iterator s21_it = s21_vector.begin();
  std::vector<int>::iterator std_it = std_vector.begin();
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  s21_vector.erase(s21_it);
  std_vector.erase(std_it);
  s21_it = s21_vector.begin();
  std_it = std_vector.begin();
  s21_vector.erase(s21_it);
  std_vector.erase(std_it);
  EXPECT_EQ(s21_vector.at(0), std_vector.at(0));
  EXPECT_EQ(s21_vector.at(1), std_vector.at(1));
  EXPECT_EQ(s21_vector.at(2), std_vector.at(2));
  EXPECT_EQ(s21_vector.at(3), std_vector.at(3));
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, empty_testing) {
  Test_vector logger;
  EXPECT_FALSE(logger.five_Vector.empty());
  EXPECT_TRUE(logger.empty_Vector.empty());
}

TEST(Vector, size_testing) {
  Test_vector logger;
  EXPECT_EQ(logger.empty_Vector.size(), 0);
  EXPECT_EQ(logger.five_Vector.size(), 5);
}

TEST(Vector, max_size_testing) {
  Test_vector logger;
  EXPECT_EQ(logger.empty_Vector.max_size(), logger.origin_int.max_size());
  EXPECT_EQ(logger.char_Vector.max_size(), logger.origin_char.max_size());
  EXPECT_EQ(logger.float_Vector.max_size(), logger.origin_float.max_size());
  EXPECT_EQ(logger.double_Vector.max_size(), logger.origin_double.max_size());
}

TEST(Vector, reserve_testing) {
  Test_vector logger;
  logger.five_Vector.reserve(2);
  logger.origin_five_vector.reserve(2);
  EXPECT_EQ(logger.five_Vector.capacity(),
            logger.origin_five_vector.capacity());
  logger.five_Vector.reserve(1000);
  logger.origin_five_vector.reserve(1000);
  EXPECT_EQ(logger.five_Vector.capacity(),
            logger.origin_five_vector.capacity());
  logger.five_Vector.reserve(0);
  logger.origin_five_vector.reserve(0);
  EXPECT_EQ(logger.five_Vector.capacity(),
            logger.origin_five_vector.capacity());
  //        EXPECT_ANY_THROW(logger.five_Vector.reserve(-1));  // google leaks
}

TEST(Vector, capacity_testing) {
  Test_vector logger;
  EXPECT_EQ(logger.five_Vector.capacity(),
            logger.origin_five_vector.capacity());
  logger.five_Vector.push_back(3);
  logger.origin_five_vector.push_back(4);
  EXPECT_EQ(logger.five_Vector.capacity(),
            logger.origin_five_vector.capacity());
  logger.five_Vector.pop_back();
  logger.origin_five_vector.pop_back();
  EXPECT_EQ(logger.five_Vector.capacity(),
            logger.origin_five_vector.capacity());
}

TEST(Vector, shrink_to_fit_testing) {
  Test_vector logger;
  logger.five_Vector.reserve(3);
  logger.origin_five_vector.reserve(3);
  logger.five_Vector.shrink_to_fit();
  logger.origin_five_vector.shrink_to_fit();
  EXPECT_EQ(logger.five_Vector.capacity(),
            logger.origin_five_vector.capacity());
  EXPECT_EQ(logger.five_Vector.size(), logger.origin_five_vector.size());
  logger.five_Vector.reserve(100);
  logger.origin_five_vector.reserve(100);
  logger.five_Vector.shrink_to_fit();
  logger.origin_five_vector.shrink_to_fit();
  EXPECT_EQ(logger.five_Vector.capacity(),
            logger.origin_five_vector.capacity());
  EXPECT_EQ(logger.five_Vector.size(), logger.origin_five_vector.size());
  logger.five_Vector.reserve(0);
  logger.origin_five_vector.reserve(0);
  logger.five_Vector.shrink_to_fit();
  logger.origin_five_vector.shrink_to_fit();
  EXPECT_EQ(logger.five_Vector.capacity(),
            logger.origin_five_vector.capacity());
  EXPECT_EQ(logger.five_Vector.size(), logger.origin_five_vector.size());
}

TEST(Vector, clear_testing) {
  Test_vector logger;
  logger.five_Vector.clear();
  logger.origin_five_vector.clear();
  EXPECT_EQ(logger.five_Vector.capacity(),
            logger.origin_five_vector.capacity());
  EXPECT_EQ(logger.five_Vector.size(), logger.origin_five_vector.size());
}

TEST(Vector, function_swap) {
  Test_vector logger;
  logger.s21_vector_s.swap(logger.s21_vector_swap);
  logger.std_vector_s.swap(logger.std_vector_swap);
  EXPECT_EQ(logger.s21_vector_swap.at(0), logger.std_vector_swap.at(0));
  EXPECT_EQ(logger.s21_vector_swap.at(1), logger.std_vector_swap.at(1));
  EXPECT_EQ(logger.s21_vector_swap.at(2), logger.std_vector_swap.at(2));
  EXPECT_EQ(logger.s21_vector_swap.at(3), logger.std_vector_swap.at(3));
  EXPECT_EQ(logger.s21_vector_swap.at(4), logger.std_vector_swap.at(4));
  EXPECT_EQ(logger.s21_vector_swap.size(), logger.std_vector_swap.size());
  EXPECT_EQ(logger.s21_vector_swap.capacity(),
            logger.std_vector_swap.capacity());
  EXPECT_EQ(logger.std_vector_s.at(0), logger.std_vector_s.at(0));
  EXPECT_EQ(logger.std_vector_s.at(1), logger.std_vector_s.at(1));
  EXPECT_EQ(logger.std_vector_s.at(2), logger.std_vector_s.at(2));
  EXPECT_EQ(logger.std_vector_s.at(3), logger.std_vector_s.at(3));
  EXPECT_EQ(logger.std_vector_s.at(4), logger.std_vector_s.at(4));
  EXPECT_EQ(logger.std_vector_s.at(5), logger.std_vector_s.at(5));
  EXPECT_EQ(logger.std_vector_s.at(6), logger.std_vector_s.at(6));
  EXPECT_EQ(logger.std_vector_s.at(7), logger.std_vector_s.at(7));
  EXPECT_EQ(logger.std_vector_s.at(8), logger.std_vector_s.at(8));
  EXPECT_EQ(logger.std_vector_s.at(9), logger.std_vector_s.at(9));
  EXPECT_EQ(logger.std_vector_s.size(), logger.std_vector_s.size());
  EXPECT_EQ(logger.std_vector_s.capacity(), logger.std_vector_s.capacity());
  EXPECT_EQ(logger.std_vector_s.empty(), logger.std_vector_s.empty());
}

TEST(Vector, function_push_back) {
  s21::Vector<int> s21_vector{1, 2, 3};
  std::vector<int> std_vector{1, 2, 3};
  s21_vector.push_back(666);
  std_vector.push_back(666);
  s21_vector.push_back(123);
  std_vector.push_back(123);
  ASSERT_EQ(s21_vector.at(0), std_vector.at(0));
  ASSERT_EQ(s21_vector.at(1), std_vector.at(1));
  ASSERT_EQ(s21_vector.at(2), std_vector.at(2));
  ASSERT_EQ(s21_vector.at(3), std_vector.at(3));
  ASSERT_EQ(s21_vector.at(4), std_vector.at(4));
  ASSERT_EQ(s21_vector.size(), std_vector.size());
  ASSERT_EQ(s21_vector.capacity(), std_vector.capacity());
  ASSERT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, function_pop_back) {
  s21::Vector<int> s21_vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> std_vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21_vector.pop_back();
  std_vector.pop_back();
  s21_vector.pop_back();
  std_vector.pop_back();
  ASSERT_EQ(s21_vector.at(0), std_vector.at(0));
  ASSERT_EQ(s21_vector.at(1), std_vector.at(1));
  ASSERT_EQ(s21_vector.at(2), std_vector.at(2));
  ASSERT_EQ(s21_vector.at(3), std_vector.at(3));
  ASSERT_EQ(s21_vector.at(4), std_vector.at(4));
  ASSERT_EQ(s21_vector.at(5), std_vector.at(5));
  ASSERT_EQ(s21_vector.at(6), std_vector.at(6));
  ASSERT_EQ(s21_vector.at(7), std_vector.at(7));
  ASSERT_EQ(s21_vector.size(), std_vector.size());
  ASSERT_EQ(s21_vector.capacity(), std_vector.capacity());
  ASSERT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, function_reserve) {
  s21::Vector<double> s21_vector_empty;
  std::vector<double> std_vector_empty;
  s21_vector_empty.reserve(100);
  std_vector_empty.reserve(100);
  ASSERT_EQ(s21_vector_empty.size(), std_vector_empty.size());
  ASSERT_EQ(s21_vector_empty.capacity(), std_vector_empty.capacity());
  ASSERT_EQ(s21_vector_empty.empty(), std_vector_empty.empty());
  s21::Vector<int> s21_vector{1, 2, 3};
  std::vector<int> std_vector{1, 2, 3};
  s21_vector.reserve(50);
  std_vector.reserve(50);
  ASSERT_EQ(s21_vector.at(0), std_vector.at(0));
  ASSERT_EQ(s21_vector.at(1), std_vector.at(1));
  ASSERT_EQ(s21_vector.at(2), std_vector.at(2));
  ASSERT_EQ(s21_vector.size(), std_vector.size());
  ASSERT_EQ(s21_vector.capacity(), std_vector.capacity());
  ASSERT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, function_shrink_to_fit) {
  s21::Vector<int> s21_vector{1, 2, 3};
  std::vector<int> std_vector{1, 2, 3};
  s21_vector.reserve(50);
  std_vector.reserve(50);
  s21_vector.shrink_to_fit();
  std_vector.shrink_to_fit();
  ASSERT_EQ(s21_vector.at(0), std_vector.at(0));
  ASSERT_EQ(s21_vector.at(1), std_vector.at(1));
  ASSERT_EQ(s21_vector.at(2), std_vector.at(2));
  ASSERT_EQ(s21_vector.size(), std_vector.size());
  ASSERT_EQ(s21_vector.capacity(), std_vector.capacity());
  ASSERT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(Vector, function_emplace_begin) {
  s21::Vector<int> s21_vector{1, 2, 3, 5, 9, 10};
  std::vector<int> std_vector{1, 2, 3, 5, 9, 10};
  s21::Vector<int>::const_iterator s21_it = s21_vector.begin();
  std::vector<int>::iterator std_it = std_vector.begin();
  s21_it = s21_vector.emplace(s21_it, 666);
  std_it = std_vector.emplace(std_it, 666);
  EXPECT_EQ(*s21_it, *std_it);
  EXPECT_EQ(s21_vector.at(0), std_vector.at(0));
  EXPECT_EQ(s21_vector.at(1), std_vector.at(1));
  EXPECT_EQ(s21_vector.at(2), std_vector.at(2));
  EXPECT_EQ(s21_vector.at(3), std_vector.at(3));
  EXPECT_EQ(s21_vector.at(4), std_vector.at(4));
  EXPECT_EQ(s21_vector.at(5), std_vector.at(5));
  EXPECT_EQ(s21_vector.at(6), std_vector.at(6));
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

// >>>>>>>>>>> ARRAY <<<<<<<<<<<<<<<<
class TestArray {
 public:
  s21::Array<int, 0> s21_array_empty;
  s21::Array<int, 3> copy_array{234, 21, 11};
  s21::Array<char, 0> copy_ar1;
  s21::Array<double, 5> copy_array1{2.5, 3.4, 255.3, 1.2, 0.5};
  s21::Array<double, 5> copy_array2{-5.3, 1.18, -4.3, 255.34, 1.23};

  std::array<int, 0> std_array_empty;
  std::array<int, 3> orig_array{234, 21, 11};
  std::array<char, 0> orig_ar1;
  std::array<double, 5> orig_array1{2.5, 3.4, 255.3, 1.2, 0.5};
  std::array<double, 5> orig_array2{-5.3, 1.18, -4.3, 255.34, 1.23};
};

TEST(Array, constructor_default) {
  TestArray tester;
  EXPECT_EQ(tester.s21_array_empty.size(), tester.std_array_empty.size());
  EXPECT_EQ(tester.s21_array_empty.empty(), tester.std_array_empty.empty());
}

TEST(Array, constructor_initializer) {
  TestArray tester;
  EXPECT_EQ(tester.copy_array1[1], tester.orig_array1[1]);
  EXPECT_EQ(tester.copy_array1.front(), tester.orig_array1.front());
  EXPECT_EQ(tester.copy_array1.back(), tester.orig_array1.back());
  EXPECT_EQ(tester.copy_array1.size(), tester.orig_array1.size());
  EXPECT_EQ(tester.copy_array1.empty(), tester.orig_array1.empty());
}

TEST(Array, constructor_copy_empty) {
  TestArray tester;
  s21::Array<int, 0> s21_array_copy(tester.s21_array_empty);
  std::array<int, 0> std_array_copy(tester.std_array_empty);
  EXPECT_EQ(s21_array_copy.size(), std_array_copy.size());
  EXPECT_EQ(s21_array_copy.empty(), std_array_copy.empty());
}

TEST(Array, simple_test) {
  TestArray logger;
  for (int i{}; i < 3; i++)
    ASSERT_EQ(logger.orig_array.at(i), logger.copy_array.at(i));
  ASSERT_EQ(logger.orig_array.size(), logger.copy_array.size());
  ASSERT_EQ(logger.orig_array.max_size(), logger.copy_array.max_size());
  ASSERT_EQ(logger.orig_ar1.empty(), logger.copy_ar1.empty());
}
TEST(Array, swap_test) {
  TestArray logger;
  logger.orig_array1.swap(logger.orig_array2);
  logger.copy_array1.swap(logger.copy_array2);
  for (int i{}; i < 5; i++) {
    ASSERT_DOUBLE_EQ(logger.orig_array1[i], logger.copy_array1[i]);
    ASSERT_DOUBLE_EQ(logger.orig_array2[i], logger.copy_array2[i]);
  }
  ASSERT_EQ(logger.orig_array1.size(), logger.copy_array1.size());
  ASSERT_EQ(logger.orig_array2.max_size(), logger.copy_array2.max_size());
  ASSERT_EQ(logger.orig_array1.front(), logger.copy_array1.front());
  ASSERT_EQ(logger.orig_array2.front(), logger.copy_array2.front());
  ASSERT_EQ(logger.orig_array1.back(), logger.copy_array1.back());
  ASSERT_EQ(logger.orig_array2.back(), logger.copy_array2.back());
}

TEST(Array, copy_constructor_test) {
  std::array<int, 3> orig_array3{234, 21, 11};
  s21::Array<int, 3> copy_array3{234, 21, 11};
  std::array<int, 3> orig_array4(orig_array3);
  s21::Array<int, 3> copy_array4(copy_array3);
  for (int i{}; i < 3; i++) {
    ASSERT_EQ(orig_array3.at(i), copy_array3.at(i));
    ASSERT_EQ(orig_array4.at(i), copy_array4.at(i));
  }
  ASSERT_EQ(orig_array3.size(), copy_array3.size());
  ASSERT_EQ(orig_array3.max_size(), copy_array3.max_size());
  ASSERT_EQ(orig_array4.size(), copy_array4.size());
  ASSERT_EQ(orig_array4.max_size(), copy_array4.max_size());
  std::array<char, 0> orig_ar5;
  s21::Array<char, 0> copy_ar5;
  std::array<char, 0> orig_ar6(orig_ar5);
  s21::Array<char, 0> copy_ar6(copy_ar5);
  ASSERT_EQ(orig_ar5.empty(), copy_ar5.empty());
  ASSERT_EQ(orig_ar6.empty(), copy_ar6.empty());
}

TEST(Array, move_constructor_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::Array<int, 5> copy_array1{234, 21, 11, 34, 999};
  std::array<int, 5> orig_array2(std::move(orig_array1));
  s21::Array<int, 5> copy_array2(std::move(copy_array1));
  for (size_t i{}; i < copy_array2.size(); i++) {
    ASSERT_EQ(orig_array2.at(i), copy_array2.at(i));
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.max_size());
  ASSERT_EQ(orig_array2.size(), copy_array2.size());
  ASSERT_EQ(orig_array2.max_size(), copy_array2.max_size());
  std::array<char, 0> orig_ar1;
  s21::Array<char, 0> copy_ar1;
  ASSERT_EQ(orig_ar1.empty(), copy_ar1.empty());
}

TEST(Array, move_operator_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::Array<int, 5> copy_array1{234, 21, 11, 34, 999};
  std::array<int, 5> orig_array2{25};
  s21::Array<int, 5> copy_array2{25};
  orig_array2 = std::move(orig_array1);
  copy_array2 = std::move(copy_array1);
  for (size_t i{}; i < copy_array2.size(); i++) {
    ASSERT_EQ(orig_array2.at(i), copy_array2.at(i));
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.max_size());
  ASSERT_EQ(orig_array2.size(), copy_array2.size());
  ASSERT_EQ(orig_array2.max_size(), copy_array2.max_size());
  std::array<char, 0> orig_ar1;
  s21::Array<char, 0> copy_ar1;
  ASSERT_EQ(orig_ar1.empty(), copy_ar1.empty());
}

TEST(Array, iterator_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::Array<int, 5> copy_array1{234, 21, 11, 34, 999};
  int *orig_beg = orig_array1.begin();
  int *copy_beg = copy_array1.begin();
  int *orig_end = orig_array1.end();
  int *copy_end = copy_array1.end();
  while (orig_beg < orig_end && copy_beg < copy_end) {
    ASSERT_EQ(*orig_beg++, *copy_beg++);
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.max_size());
  s21::Array<char, 0> copy_ar1;
  ASSERT_TRUE(copy_ar1.begin() == copy_ar1.end());
  s21::Array<double, 3> my_arr{2.3, 4.5555, 6.1234};
  double *d = my_arr.data();
  ASSERT_DOUBLE_EQ(my_arr[0], *d);
}

TEST(Array, fill_test) {
  std::array<size_t, 10> orig_array;
  s21::Array<size_t, 10> my_arr;
  orig_array.fill(555);
  my_arr.fill(555);
  for (size_t i = 0; i < orig_array.size(); i++)
    ASSERT_EQ(orig_array[i], my_arr[i]);
  ASSERT_EQ(orig_array.size(), my_arr.size());
  ;
}
// >>>>>>>>> STACK <<<<<<<<<<<<<<
TEST(Stack, simple_test) {
  s21::Stack<int> my_stack;
  std::stack<int> orig_stack;
  my_stack.push(1);
  my_stack.push(2);
  my_stack.push(2555);
  my_stack.push(365434);
  orig_stack.push(1);
  orig_stack.push(2);
  orig_stack.push(2555);
  orig_stack.push(365434);
  while (!orig_stack.empty() && !my_stack.empty()) {
    ASSERT_EQ(orig_stack.top(), my_stack.top());
    orig_stack.pop();
    my_stack.pop();
  }
  ASSERT_EQ(orig_stack.empty(), my_stack.empty());
}

TEST(Stack, swap_test) {
  std::stack<double> orig_stack1;
  orig_stack1.push(2.55);
  orig_stack1.push(3.55);
  orig_stack1.push(222.55);
  orig_stack1.push(984.55);
  orig_stack1.push(123.55);
  orig_stack1.push(0.55);
  orig_stack1.push(-34.55);
  std::stack<double> orig_stack2;
  orig_stack2.push(342.22);
  orig_stack2.push(355.01);
  orig_stack2.push(123.99);
  orig_stack2.push(888.34);
  orig_stack2.push(-23.11);
  orig_stack2.push(1002.88);
  orig_stack2.push(1.55);
  s21::Stack<double> my_stack1;
  my_stack1.push(2.55);
  my_stack1.push(3.55);
  my_stack1.push(222.55);
  my_stack1.push(984.55);
  my_stack1.push(123.55);
  my_stack1.push(0.55);
  my_stack1.push(-34.55);
  s21::Stack<double> my_stack2;
  my_stack2.push(342.22);
  my_stack2.push(355.01);
  my_stack2.push(123.99);
  my_stack2.push(888.34);
  my_stack2.push(-23.11);
  my_stack2.push(1002.88);
  my_stack2.push(1.55);
  orig_stack1.swap(orig_stack2);
  my_stack1.swap(my_stack2);
  while (!orig_stack1.empty() && !my_stack1.empty()) {
    ASSERT_DOUBLE_EQ(orig_stack1.top(), my_stack1.top());
    orig_stack1.pop();
    my_stack1.pop();
  }
  while (!orig_stack2.empty() && !my_stack2.empty()) {
    ASSERT_DOUBLE_EQ(orig_stack2.top(), my_stack2.top());
    orig_stack2.pop();
    my_stack2.pop();
  }
  ASSERT_EQ(orig_stack2.empty(), my_stack2.empty());
}

TEST(Stack, copy_constructor_test) {
  std::stack<int> orig_stack1;
  orig_stack1.push(55);
  orig_stack1.push(555);
  orig_stack1.push(5555);
  orig_stack1.push(55555);
  std::stack<int> orig_stack2(orig_stack1);
  s21::Stack<int> my_stack1;
  my_stack1.push(55);
  my_stack1.push(555);
  my_stack1.push(5555);
  my_stack1.push(55555);
  s21::Stack<int> my_stack2(my_stack1);
  while (!orig_stack2.empty() && !my_stack2.empty()) {
    ASSERT_EQ(orig_stack2.top(), my_stack2.top());
    orig_stack2.pop();
    my_stack2.pop();
  }
  s21::Stack<int> my_stack3;
  std::stack<int> orig_stack3;
  s21::Stack<int> my_stack4(my_stack3);
  std::stack<int> orig_stack4(orig_stack3);
  ASSERT_EQ(orig_stack4.empty(), my_stack4.empty());
}

TEST(Stack, move_constructor_test) {
  std::stack<int> orig_stack1;
  orig_stack1.push(55);
  orig_stack1.push(555);
  orig_stack1.push(5555);
  orig_stack1.push(55555);
  std::stack<int> orig_stack2(std::move(orig_stack1));
  s21::Stack<int> copy_stack1;
  copy_stack1.push(55);
  copy_stack1.push(555);
  copy_stack1.push(5555);
  copy_stack1.push(55555);
  s21::Stack<int> copy_stack2(std::move(copy_stack1));
  while (!orig_stack2.empty() && !copy_stack2.empty()) {
    ASSERT_EQ(orig_stack2.top(), copy_stack2.top());
    orig_stack2.pop();
    copy_stack2.pop();
  }
  ASSERT_EQ(orig_stack1.size(), copy_stack1.size());
}

TEST(Stack, move_operator_test) {
  std::stack<int> orig_stack1;
  orig_stack1.push(55);
  orig_stack1.push(555);
  orig_stack1.push(5555);
  orig_stack1.push(55555);
  std::stack<int> orig_stack2;
  orig_stack2.push(1);
  orig_stack2.push(2);
  orig_stack2 = std::move(orig_stack1);
  s21::Stack<int> copy_stack1;
  copy_stack1.push(55);
  copy_stack1.push(555);
  copy_stack1.push(5555);
  copy_stack1.push(55555);
  s21::Stack<int> copy_stack2{1, 2};
  copy_stack2 = std::move(copy_stack1);
  while (!orig_stack2.empty() && !copy_stack2.empty()) {
    ASSERT_EQ(orig_stack2.top(), copy_stack2.top());
    orig_stack2.pop();
    copy_stack2.pop();
  }
  ASSERT_EQ(orig_stack1.size(), copy_stack1.size());
}

TEST(Stack, emplace_test) {
  std::stack<int> orig_stack1;
  orig_stack1.push(55);
  orig_stack1.push(555);
  orig_stack1.push(5555);
  orig_stack1.push(55555);
  orig_stack1.emplace(345);
  orig_stack1.emplace(234);
  orig_stack1.emplace(889);
  s21::Stack<int> copy_stack1;
  copy_stack1.push(55);
  copy_stack1.push(555);
  copy_stack1.push(5555);
  copy_stack1.push(55555);
  copy_stack1.emplace_front(345);
  copy_stack1.emplace_front(234);
  copy_stack1.emplace_front(889);
  while (!orig_stack1.empty() && !copy_stack1.empty()) {
    ASSERT_EQ(orig_stack1.top(), copy_stack1.top());
    orig_stack1.pop();
    copy_stack1.pop();
  }
  ASSERT_EQ(orig_stack1.size(), copy_stack1.size());
}

}  // namespace s21

// int main(int argc, char *argv[]) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }