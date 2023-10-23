#include "s21_matrix_oop.hpp"

// Support functions
void S21Matrix::InitializeMatrix() {
  if (rows_ <= 0 && cols_ <= 0) {
    throw std::invalid_argument("Matrix parameters less or equal to zero");
  }
  for (int i = 0; i < rows_; i++) {
    matrix.push_back(std::vector<double>(cols_));
  }
}

void S21Matrix::DeleteMatrix() {
  matrix.clear();
  rows_ = 0;
  cols_ = 0;
}

bool S21Matrix::SizeCompare(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  return true;
}

void S21Matrix::PlusMinus(const S21Matrix &other, const int &sign) {
  if (SizeCompare(other) == false) {
    throw std::out_of_range("Matrix parameters are not equal to each other");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int k = 0; k < cols_; ++k) {
      matrix[i][k] = matrix[i][k] + sign * other.matrix[i][k];
    }
  }
}

void S21Matrix::CutMatrix(S21Matrix &A, const int &rows_del,
                          const int &columns_del, S21Matrix &R) {
  for (int i = 0, j = 0; i < A.rows_; ++i) {
    if (i == rows_del) {
      continue;
    }
    for (int k = 0, l = 0; k < A.cols_; ++k) {
      if (k == columns_del) {
        continue;
      }
      R.matrix[j][l] = A.matrix[i][k];
      ++l;
    }
    ++j;
  }
}

void S21Matrix::CopyMatrix(const S21Matrix &A) {
  if (!EqMatrix(A)) {
    DeleteMatrix();
    rows_ = A.rows_;
    cols_ = A.cols_;
    InitializeMatrix();
    for (int i = 0; i < rows_; ++i) {
      for (int k = 0; k < cols_; ++k) {
        matrix[i][k] = A.matrix[i][k];
      }
    }
  }
}
