#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <math.h>
#include <string.h>

#include <exception>
#include <iostream>

#define SUCCESS 1
#define FAILURE 0

using namespace std;

class S21Matrix {
 private:
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated
  void to_cut_matrix(const S21Matrix& a, const int m, const int n,
                     S21Matrix& new_matrix);
  void cleanData();

 public:
  friend S21Matrix operator*(const double num, const S21Matrix& o);
  S21Matrix();  // Default constructor
  S21Matrix(int rows, int cols);
  int getRows();
  int getCols();
  void setRows(const int rows);
  void setCols(const int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();  // Destructor

  // // some operators overloads
  S21Matrix operator+(const S21Matrix& o) const;
  S21Matrix operator-(const S21Matrix& o) const;
  S21Matrix operator*(const S21Matrix& o) const;
  S21Matrix operator*(double num) const;

  bool operator==(const S21Matrix& o) const;
  S21Matrix& operator=(const S21Matrix& o);
  S21Matrix& operator+=(const S21Matrix& o);
  S21Matrix& operator-=(const S21Matrix& o);
  S21Matrix& operator*=(const S21Matrix& o);
  S21Matrix& operator*=(const double num);

  double& operator()(int row, int col) const;  // index operator overload

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
};

#endif  // __S21MATRIX_H__