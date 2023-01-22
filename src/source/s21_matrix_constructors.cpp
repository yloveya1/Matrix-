#include "s21_matrix_oop.h"

int S21Matrix::getRows() { return rows_; }

int S21Matrix::getCols() { return cols_; }

void S21Matrix::setRows(const int rows) {
  if (rows < 1)
    throw invalid_argument("Incorrect input, rows should be more than 0");
  S21Matrix temp(*this);
  this->cleanData();
  this->rows_ = rows;
  this->cols_ = temp.cols_;
  matrix_ = new double*[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols_];
    i < temp.rows_ ? memcpy(matrix_[i], temp.matrix_[i], cols_ * sizeof(double))
                   : memset(matrix_[i], 0, cols_ * sizeof(double));
  }
}

void S21Matrix::setCols(const int cols) {
  if (cols < 1)
    throw invalid_argument("Incorrect input, cols should be more than 0");
  S21Matrix temp(*this);
  this->cleanData();
  this->rows_ = temp.rows_;
  this->cols_ = cols;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      j < temp.cols_ ? matrix_[i][j] = temp.matrix_[i][j] : matrix_[i][j] = 0;
    }
  }
}

S21Matrix::S21Matrix() : S21Matrix::S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  this->matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

void S21Matrix::cleanData() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i]) delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

S21Matrix::~S21Matrix() {
  this->cleanData();
  cols_ = rows_ = 0;
}