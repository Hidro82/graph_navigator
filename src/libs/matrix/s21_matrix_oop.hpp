#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class S21Matrix {
 private:
  int rows_, cols_;
  std::vector<std::vector<double>> matrix;

 protected:
  // Support functions
  bool SizeCompare(const S21Matrix &);
  void InitializeMatrix();
  void DeleteMatrix();
  void PlusMinus(const S21Matrix &, const int &);
  void CutMatrix(S21Matrix &, const int &, const int &, S21Matrix &);
  void CopyMatrix(const S21Matrix &);

 public:
  S21Matrix() noexcept;
  S21Matrix(const int &, const int &);
  S21Matrix(const S21Matrix &) noexcept;
  S21Matrix(S21Matrix &&) noexcept;
  ~S21Matrix();

  // Accessors
  int GetRows();
  int GetCols();
  std::vector<std::vector<double>> GetMatrix();

  // mutators
  void SetRows(const int &);
  void SetCols(const int &);
  void SetMatrix(std::vector<std::vector<double>>, const int &, const int &);
  void SetMatrix(std::vector<std::vector<int>>, const int &, const int &);

  // overload operators
  S21Matrix operator+(const S21Matrix &);
  S21Matrix operator-(const S21Matrix &);
  S21Matrix operator*(const S21Matrix &);
  S21Matrix operator*(const double &);
  S21Matrix &operator+=(const S21Matrix &);
  S21Matrix &operator-=(const S21Matrix &);
  S21Matrix &operator*=(const S21Matrix &);
  S21Matrix &operator*=(const double &);
  S21Matrix &operator=(const S21Matrix &);
  bool operator==(const S21Matrix &);
  double &operator()(const int &, const int &);

  // matrix lib
  bool EqMatrix(const S21Matrix &);
  void SumMatrix(const S21Matrix &);
  void SubMatrix(const S21Matrix &);
  void MulNumber(const double &);
  void MulMatrix(const S21Matrix &);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
};

#endif  //  S21_MATRIX_OOP_H_
