#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& o) const {
  S21Matrix res(*this);
  res.SumMatrix(o);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) const {
  S21Matrix res(*this);
  res.SubMatrix(o);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& o) const {
  S21Matrix res(*this);
  res.MulMatrix(o);
  return res;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix operator*(const double num, const S21Matrix& o) {
  S21Matrix res(o);
  res.MulNumber(num);
  return res;
}

bool S21Matrix::operator==(const S21Matrix& o) const {
  return this->EqMatrix(o);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
  this->cleanData();
  this->rows_ = o.rows_;
  this->cols_ = o.cols_;
  this->matrix_ = new double*[rows_];
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      memcpy(matrix_[i], o.matrix_[i], cols_ * sizeof(double));
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
  this->SumMatrix(o);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
  this->SubMatrix(o);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
  this->MulMatrix(o);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Incorrect input, index is outside the matrix");
  }
  return matrix_[row][col];
}
