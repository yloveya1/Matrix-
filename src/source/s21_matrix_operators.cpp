#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool is_equal = (rows_ == other.rows_ && cols_ == other.cols_);
  for (int i = 0; is_equal && i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-6) {
        is_equal = false;
        break;
      }
    }
  }
  return is_equal;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw out_of_range("Incorrect input, matrices should have the same size");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw out_of_range(
        "Incorrect input, cols_ of this matrix is not equal to the rows_ of "
        "other");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw out_of_range(
        "the number of columns of the first matrix does not equal the number "
        "of rows of the second matrix");
  }
  S21Matrix result(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < this->cols_; k++)
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      res.matrix_[i][j] = matrix_[j][i];
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_) {
    throw out_of_range("the matrix is not square");
  }
  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = matrix_[0][0];
  } else {
    S21Matrix new_matrix(rows_ - 1, cols_ - 1);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        to_cut_matrix(*this, i, j, new_matrix);
        res.matrix_[i][j] = pow(-1, i + j) * new_matrix.Determinant();
      }
    }
  }
  return res;
}

void S21Matrix::to_cut_matrix(const S21Matrix& a, const int m, const int n,
                              S21Matrix& new_matrix) {
  for (int i = 0, i2 = 0; i < a.rows_; i++) {
    if (i == m) continue;
    for (int j = 0, j2 = 0; j < a.cols_; j++) {
      if (j == n) continue;

      new_matrix.matrix_[i2][j2] = a.matrix_[i][j];
      j2++;
    }
    i2++;
  }
}

double S21Matrix::Determinant() {
  if (cols_ != rows_) {
    throw out_of_range("the matrix is not square");
  }
  double determinant = 0;
  int sign = 1;
  if (this->rows_ == 1) {
    determinant = this->matrix_[0][0];
  } else if (this->rows_ == 2) {
    determinant = (this->matrix_[0][0] * this->matrix_[1][1]) -
                  (this->matrix_[0][1] * this->matrix_[1][0]);
  } else {
    S21Matrix new_matrix(this->rows_ - 1, this->rows_ - 1);
    for (int i = 0; i < this->cols_; i++, sign = -sign) {
      to_cut_matrix(*this, 0, i, new_matrix);
      determinant += sign * this->matrix_[0][i] * new_matrix.Determinant();
    }
  }

  return determinant;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (fabs(det) < 1e-10) {
    throw out_of_range("matrix determinant is 0");
  }
  S21Matrix transpose_calc = this->CalcComplements().Transpose();
  transpose_calc.MulNumber(1.0 / det);
  return transpose_calc;
}