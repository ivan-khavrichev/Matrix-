#include "s21_matrix_oop.h"

#include <cstring>
#include <iostream>

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1)
    throw std::invalid_argument(
        "Incorrect input, matrix should have positive size");

  matrix_ = new double[rows_ * cols_]();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(new double[rows_ * cols_]()) {
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(new double[rows_ * cols_]()) {
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);

  other.rows_ = 0;
  other.cols_ = 0;
  delete[] other.matrix_;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  delete[] matrix_;
  matrix_ = nullptr;
}

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetRows(int new_rows_) {
  if (new_rows_ < 0)
    throw std::invalid_argument(
        "Incorrect input, matrix should have positive size");

  S21Matrix tmp_(new_rows_, cols_);
  int tmp_rows_ = 0;
  if (new_rows_ > rows_) {
    tmp_rows_ = rows_;
  } else {
    tmp_rows_ = new_rows_;
  }

  for (int i = 0; i < tmp_rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      tmp_(i, j) = (*this)(i, j);
    }
  }

  *this = std::move(tmp_);
}

void S21Matrix::SetCols(int new_cols_) {
  if (new_cols_ < 0)
    throw std::invalid_argument(
        "Incorrect input, matrix should have positive size");

  S21Matrix tmp_(rows_, new_cols_);
  int tmp_cols_ = 0;
  if (new_cols_ > cols_) {
    tmp_cols_ = cols_;
  } else {
    tmp_cols_ = new_cols_;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < tmp_cols_; ++j) {
      tmp_(i, j) = (*this)(i, j);
    }
  }

  *this = std::move(tmp_);
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Matrices must be of the same dimension");

  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      (*this)(i, j) += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Matrices must be of the same dimension");

  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      (*this)(i, j) -= other(i, j);
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::logic_error("Inconsistency in the number of columns and rows");

  S21Matrix res_(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int m = 0; m < cols_; ++m) {
        res_(i, j) += (*this)(i, m) * other(m, j);
      }
    }
  }

  *this = std::move(res_);
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      (*this)(i, j) *= num;
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      if (fabs((*this)(i, j) - other(i, j)) > 1e-6) {
        return false;
      }
    }
  }

  return true;
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix res_(cols_, rows_);
  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      res_(i, j) = (*this)(j, i);
    }
  }

  return res_;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::logic_error("Matrix must be square");

  if (rows_ < 2)
    throw std::logic_error("Matrix must be non-zero and non-unique");

  int order_ = this->rows_ - 1;
  S21Matrix tmp_(*this);
  S21Matrix res_(this->rows_, this->cols_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      res_(i, j) = pow(-1, i + j) * tmp_.CalcMinor(i, j, order_);
    }
  }

  return (res_);
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) throw std::logic_error("Matrix must be square");

  double res_ = 1;
  int count_ = 0;
  int sign_ = 0;
  double number_ = 0;
  S21Matrix tmp_(*this);
  for (int j = 0; j < cols_; ++j) {
    sign_ = tmp_.SwapRows(j);
    for (int i = tmp_.rows_ - 1; i > count_; --i) {
      number_ = tmp_(i, j) / tmp_(j, j);
      for (int m = 0; m < tmp_.cols_; ++m) {
        tmp_(i, m) -= number_ * tmp_(j, m);
      }
    }
    res_ *= sign_ * tmp_(j, j);
    ++count_;
  }

  if (fabs(res_) <= 1e-6) res_ = fabs(res_);

  return res_;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det_ = Determinant();
  if (fabs(det_) <= 1e-6)
    throw std::logic_error(
        "The determinant of the matrix cannot be equal to zero");

  S21Matrix res_ = CalcComplements().Transpose();
  res_.MulNumber(1 / det_);

  return res_;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix res_(*this);
  res_.SumMatrix(other);
  return res_;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix res_(*this);
  res_.SubMatrix(other);
  return res_;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix res_(*this);
  res_.MulMatrix(other);
  return res_;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix res_(*this);
  res_.MulNumber(num);
  return res_;
}

S21Matrix operator*(const double num, S21Matrix& other) {
  S21Matrix res_(other);
  res_.MulNumber(num);
  return res_;
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (&other != this) {
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double[rows_ * cols_]();
    std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
  }

  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (&other != this) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }

  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return (*this);
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return (*this);
}

double& S21Matrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0)
    throw std::out_of_range("Incorrect input, index is out of range");

  return matrix_[i * cols_ + j];
}

double S21Matrix::CalcMinor(int crossed_out_rows, int crossed_out_columns,
                            int order) const {
  double minor_ = 0;
  S21Matrix minor_element_(order, order);
  for (int n = 0, i = 0; i < this->rows_; ++i, ++n) {
    if (i != crossed_out_rows) {
      for (int m = 0, j = 0; j < this->cols_; ++j, ++m) {
        if (j != crossed_out_columns) {
          minor_element_(n, m) = (*this)(i, j);
        } else {
          --m;
        }
      }
    } else {
      --n;
    }
  }

  minor_ = minor_element_.Determinant();

  return minor_;
}

int S21Matrix::SwapRows(int m) {
  int flag_ = 1;
  double max_ = fabs((*this)(m, m));
  int max_rows_ = 0;
  for (int i = m; i < this->rows_; ++i) {
    if (max_ < fabs((*this)(i, m))) {
      max_ = fabs((*this)(i, m));
      max_rows_ = i;
      flag_ = -1;
    }
  }

  if (flag_ == -1) {
    for (int j = 0; j < this->rows_; ++j) {
      double tmp_ = (*this)(m, j);
      (*this)(m, j) = (*this)(max_rows_, j);
      (*this)(max_rows_, j) = tmp_;
    }
  }

  return flag_;
}

void S21Matrix::PrintMatrix() {
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      std::cout << (*this)(i, j) << "\t";
    }
    std::cout << std::endl;
  }
}
