#ifndef CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H_

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int new_rows_);
  void SetCols(int new_cols_);

  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  bool EqMatrix(const S21Matrix& other) const noexcept;
  S21Matrix Transpose() const noexcept;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int i, int j) const;

  friend S21Matrix operator*(const double num, S21Matrix& other);

  int SwapRows(int m);
  double CalcMinor(int crossed_out_rows, int crossed_out_columns,
                   int order) const;
  void PrintMatrix();

 protected:
 private:
  int rows_, cols_;
  double* matrix_;
};

#endif  // CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H_
