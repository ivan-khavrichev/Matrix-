#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(TestMatrix, constructors) {
  S21Matrix A;
  ASSERT_EQ(A.GetRows(), 0);
  ASSERT_EQ(A.GetCols(), 0);

  S21Matrix B(2, 4);
  ASSERT_EQ(B.GetRows(), 2);
  ASSERT_EQ(B.GetCols(), 4);

  S21Matrix C(B);
  ASSERT_EQ(B.GetRows(), 2);
  ASSERT_EQ(B.GetCols(), 4);
  ASSERT_EQ(B.GetRows(), 2);
  ASSERT_EQ(B.GetCols(), 4);

  S21Matrix M(4, 4);
  S21Matrix N(std::move(M));
  ASSERT_EQ(M.GetCols(), 0);
  ASSERT_EQ(M.GetRows(), 0);
  ASSERT_EQ(N.GetCols(), 4);
  ASSERT_EQ(N.GetRows(), 4);

  EXPECT_THROW(S21Matrix G(34, -1), std::invalid_argument);

  S21Matrix H(1, 1);
  ASSERT_EQ(H.GetRows(), 1);
  ASSERT_EQ(H.GetCols(), 1);
}

TEST(TestMatrix, mutators) {
  S21Matrix B(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  B.SetRows(3);
  ASSERT_EQ(B.GetRows(), 3);
  ASSERT_EQ(B.GetCols(), 2);
  ASSERT_EQ(B(0, 0), 1);
  ASSERT_EQ(B(0, 1), 2);
  ASSERT_EQ(B(1, 0), 3);
  ASSERT_EQ(B(1, 1), 4);
  ASSERT_EQ(B(2, 0), 0);
  ASSERT_EQ(B(2, 1), 0);

  B.SetRows(1);
  ASSERT_EQ(B.GetRows(), 1);
  ASSERT_EQ(B.GetCols(), 2);
  B(0, 0) = 1;
  B(0, 1) = 2;

  EXPECT_THROW(B.SetRows(0), std::invalid_argument);
  EXPECT_THROW(B.SetRows(-2), std::invalid_argument);

  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A.SetCols(3);
  ASSERT_EQ(A.GetRows(), 2);
  ASSERT_EQ(A.GetCols(), 3);

  ASSERT_EQ(A(0, 0), 1);
  ASSERT_EQ(A(0, 1), 2);
  ASSERT_EQ(A(0, 2), 0);
  ASSERT_EQ(A(1, 0), 3);
  ASSERT_EQ(A(1, 1), 4);
  ASSERT_EQ(A(1, 2), 0);

  A.SetCols(1);
  ASSERT_EQ(A.GetRows(), 2);
  ASSERT_EQ(A.GetCols(), 1);
  ASSERT_EQ(A(0, 0), 1);
  ASSERT_EQ(A(1, 0), 3);

  EXPECT_THROW(A.SetCols(0), std::invalid_argument);
  EXPECT_THROW(A.SetCols(-2), std::invalid_argument);
}

TEST(FUNCTIONS, SetRows_More) {
  S21Matrix test(3, 3);
  test(0, 0) = 1;
  test(0, 1) = 2;
  test(0, 2) = 3;
  test(1, 0) = 0;
  test(1, 1) = 4;
  test(1, 2) = 2;
  test(2, 0) = 5;
  test(2, 1) = 2;
  test(2, 2) = 1;

  test.SetRows(4);

  GTEST_ASSERT_EQ(test.GetRows(), 4);
  GTEST_ASSERT_EQ(test(3, 0), 0);
}

TEST(FUNCTIONS, SetRows_Less) {
  S21Matrix test(3, 3);
  test(0, 0) = 1;
  test(0, 1) = 2;
  test(0, 2) = 3;
  test(1, 0) = 0;
  test(1, 1) = 4;
  test(1, 2) = 2;
  test(2, 0) = 5;
  test(2, 1) = 2;
  test(2, 2) = 1;

  test.SetRows(2);

  GTEST_ASSERT_EQ(test.GetRows(), 2);
}

TEST(FUNCTIONS, SetCols_More) {
  S21Matrix test(3, 3);
  test(0, 0) = 1;
  test(0, 1) = 2;
  test(0, 2) = 3;
  test(1, 0) = 0;
  test(1, 1) = 4;
  test(1, 2) = 2;
  test(2, 0) = 5;
  test(2, 1) = 2;
  test(2, 2) = 1;

  test.SetCols(4);

  GTEST_ASSERT_EQ(test.GetCols(), 4);
  GTEST_ASSERT_EQ(test(2, 3), 0);
}

TEST(FUNCTIONS, SetCols_Less) {
  S21Matrix test(3, 3);
  test(0, 0) = 1;
  test(0, 1) = 2;
  test(0, 2) = 3;
  test(1, 0) = 0;
  test(1, 1) = 4;
  test(1, 2) = 2;
  test(2, 0) = 5;
  test(2, 1) = 2;
  test(2, 2) = 1;

  test.SetCols(2);

  GTEST_ASSERT_EQ(test.GetCols(), 2);
}

TEST(CONSTRUCTORS, Default) {
  S21Matrix tt;

  GTEST_ASSERT_TRUE(tt.GetRows() == 0);
  GTEST_ASSERT_TRUE(tt.GetCols() == 0);
}

TEST(CONSTRUCTORS, MoveMatrix) {
  S21Matrix tt(5, 5);
  tt(0, 0) = 2;
  S21Matrix tt2(std::move(tt));

  GTEST_ASSERT_FALSE(tt.GetCols() == tt2.GetCols());
  GTEST_ASSERT_TRUE(tt2(0, 0) == 2);
}

TEST(CONSTRUCTORS, CopyMatrix) {
  S21Matrix res1(3, 3);
  int counter = 0;
  for (int i = 0; i < res1.GetRows(); ++i) {
    for (int j = 0; j < res1.GetCols(); ++j) {
      counter++;
      res1(i, j) = counter;
    }
  }

  S21Matrix res2(res1);

  GTEST_ASSERT_TRUE(res2.GetCols() == res1.GetCols());
  GTEST_ASSERT_TRUE(res2.GetRows() == res1.GetRows());
  GTEST_ASSERT_TRUE(res1 == res2);
}

TEST(TestMatrix, operator_brackets) {
  S21Matrix A(1, 2);
  ASSERT_EQ(A(0, 0), 0);
  A(0, 0) = 4;
  ASSERT_EQ(A(0, 0), 4);
  A(0, 1) = 3;
  ASSERT_EQ(A(0, 1), 3);

  EXPECT_THROW(A(0, 3), std::out_of_range);
  EXPECT_THROW(A(3, 0), std::out_of_range);
  EXPECT_THROW(A(-2, 1), std::out_of_range);
  EXPECT_THROW(A(0, -3), std::out_of_range);
}

TEST(TestSumMatrix, sum_matrix_1) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix R(2, 2);
  S21Matrix WR(2, 3);
  S21Matrix OP(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 1;
  A(1, 0) = 1;
  A(1, 1) = 1;
  B(0, 0) = 2;
  B(0, 1) = 2;
  B(1, 0) = 2;
  B(1, 1) = 2;
  R(0, 0) = 3;
  R(0, 1) = 3;
  R(1, 0) = 3;
  R(1, 1) = 3;
  S21Matrix AA(A);
  AA += B;
  OP = A + B;
  A.SumMatrix(B);

  ASSERT_TRUE(A == R);
  ASSERT_TRUE(OP == R);
  ASSERT_TRUE(AA == R);

  EXPECT_THROW(A.SumMatrix(WR), std::logic_error);
}

TEST(TestSumMatrix, sum_matrix_2) {
  S21Matrix A(1, 1);
  S21Matrix B(1, 1);
  S21Matrix R(1, 1);
  A(0, 0) = 1.25;
  S21Matrix AA(A);
  B(0, 0) = 2.25;
  R(0, 0) = 3.5;
  S21Matrix OP(1, 1);
  OP = A + B;
  AA += B;
  ASSERT_TRUE(OP == R);
  A.SumMatrix(B);
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
}

TEST(TestSumMatrix, sum_matrix_3) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix R(3, 3);
  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 4.25;
  A(1, 2) = 5.25;
  A(2, 0) = 6.25;
  A(2, 1) = 7.25;
  A(2, 2) = 8.25;
  S21Matrix AA(A);
  B(0, 0) = 9.65;
  B(0, 1) = 8.65;
  B(0, 2) = 7.65;
  B(1, 0) = 6.65;
  B(1, 1) = 5.65;
  B(1, 2) = 4.65;
  B(2, 0) = 3.65;
  B(2, 1) = 2.65;
  B(2, 2) = 1.65;

  R(0, 0) = 9.9;
  R(0, 1) = 9.9;
  R(0, 2) = 9.9;
  R(1, 0) = 9.9;
  R(1, 1) = 9.9;
  R(1, 2) = 9.9;
  R(2, 0) = 9.9;
  R(2, 1) = 9.9;
  R(2, 2) = 9.9;
  S21Matrix OP(3, 3);
  OP = A + B;
  AA += B;
  A.SumMatrix(B);
  ASSERT_TRUE(OP == R);
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
}

TEST(TestSumMatrix, sum_matrix_4) {
  S21Matrix A(1, 1);
  S21Matrix B(2, 1);

  EXPECT_THROW(A.SumMatrix(B), std::logic_error);
  EXPECT_THROW(A + B, std::logic_error);
  EXPECT_THROW(A += B, std::logic_error);
}

TEST(TestSumMatrix, sum_matrix_5) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);
  S21Matrix R(4, 4);
  A(0, 0) = 1.80377;
  A(0, 1) = 3.93870;
  A(0, 2) = 3.13429;
  A(0, 3) = 2.28155;
  A(1, 0) = 1.39307;
  A(1, 1) = 1.05586;
  A(1, 2) = 2.21357;
  A(1, 3) = 2.20440;
  A(2, 0) = 2.74323;
  A(2, 1) = 2.41325;
  A(2, 2) = 3.86805;
  A(2, 3) = 2.73013;
  A(3, 0) = 2.74323;
  A(3, 1) = 2.41325;
  A(3, 2) = 3.86805;
  A(3, 3) = 2.73013;
  S21Matrix AA(A);
  B(0, 0) = 1.26273;
  B(0, 1) = 1.04840;
  B(0, 2) = 3.52904;
  B(0, 3) = 2.43282;
  B(1, 0) = 3.77110;
  B(1, 1) = 3.91306;
  B(1, 2) = 2.02829;
  B(1, 3) = 2.98469;
  B(2, 0) = 1.57829;
  B(2, 1) = 1.88621;
  B(2, 2) = 1.51431;
  B(2, 3) = 2.45186;
  B(3, 0) = 3.68725;
  B(3, 1) = 2.39301;
  B(3, 2) = 1.84984;
  B(3, 3) = 2.48786;

  R(0, 0) = 3.0665;
  R(0, 1) = 4.9871;
  R(0, 2) = 6.66333;
  R(0, 3) = 4.71437;
  R(1, 0) = 5.16417;
  R(1, 1) = 4.96892;
  R(1, 2) = 4.24186;
  R(1, 3) = 5.18909;
  R(2, 0) = 4.32152;
  R(2, 1) = 4.29946;
  R(2, 2) = 5.38236;
  R(2, 3) = 5.18199;
  R(3, 0) = 6.43048;
  R(3, 1) = 4.80626;
  R(3, 2) = 5.71789;
  R(3, 3) = 5.21799;

  S21Matrix OP(4, 4);
  OP = A + B;
  AA += B;
  A.SumMatrix(B);
  ASSERT_TRUE(OP == R);
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
}

TEST(TestSumMatrix, sum_matrix_6) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  S21Matrix R(3, 4);
  S21Matrix OP(3, 4);

  A(0, 0) = 1.80377;
  A(0, 1) = 3.93870;
  A(0, 2) = 3.13429;
  A(0, 3) = 2.28155;
  A(1, 0) = 1.39307;
  A(1, 1) = 1.05586;
  A(1, 2) = 2.21357;
  A(1, 3) = 2.20440;
  A(2, 0) = 2.74323;
  A(2, 1) = 2.41325;
  A(2, 2) = 3.86805;
  A(2, 3) = 2.73013;
  S21Matrix AA(A);
  B(0, 0) = 1.26273;
  B(0, 1) = 1.04840;
  B(0, 2) = 3.52904;
  B(0, 3) = 2.43282;
  B(1, 0) = 3.77110;
  B(1, 1) = 3.91306;
  B(1, 2) = 2.02829;
  B(1, 3) = 2.98469;
  B(2, 0) = 1.57829;
  B(2, 1) = 1.88621;
  B(2, 2) = 1.51431;
  B(2, 3) = 2.45186;

  R(0, 0) = 3.0665;
  R(0, 1) = 4.9871;
  R(0, 2) = 6.66333;
  R(0, 3) = 4.71437;
  R(1, 0) = 5.16417;
  R(1, 1) = 4.96892;
  R(1, 2) = 4.24186;
  R(1, 3) = 5.18909;
  R(2, 0) = 4.32152;
  R(2, 1) = 4.29946;
  R(2, 2) = 5.38236;
  R(2, 3) = 5.18199;

  OP = A + B;
  A.SumMatrix(B);
  AA += B;
  ASSERT_TRUE(OP == R);
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
}

TEST(TestSumMatrix, sum_matrix_7) {
  S21Matrix A(4, 3);
  S21Matrix B(3, 4);

  EXPECT_THROW(A.SumMatrix(B), std::logic_error);
}

TEST(TestSumMatrix, sum_matrix_op) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix R(2, 2);
  S21Matrix WR(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 1;
  A(1, 0) = 1;
  A(1, 1) = 1;
  B(0, 0) = 2;
  B(0, 1) = 2;
  B(1, 0) = 2;
  B(1, 1) = 2;
  R(0, 0) = 3;
  R(0, 1) = 3;
  R(1, 0) = 3;
  R(1, 1) = 3;
  ASSERT_TRUE((A + B) == R);

  EXPECT_THROW(A + WR, std::logic_error);
}

TEST(TestMatrix, sum) {
  S21Matrix a = S21Matrix(2, 2);
  S21Matrix b = S21Matrix(2, 3);

  EXPECT_THROW(a.SumMatrix(b), std::logic_error);

  a(0, 0) = 2.1;
  a(0, 1) = 0.99999;
  a(1, 0) = -2.1;
  a(1, 1) = 34565131.45646;

  S21Matrix c = S21Matrix(2, 2);
  c(0, 0) = 2.1;
  c(0, 1) = 0.00000001;
  c(1, 0) = 2.1;
  c(1, 1) = 0.45646;

  S21Matrix res = S21Matrix(2, 2);
  res(0, 0) = 2.1 + 2.1;
  res(0, 1) = 0.99999 + 0.00000001;
  res(1, 0) = -2.1 + 2.1;
  res(1, 1) = 34565131.45646 + 0.45646;

  a.SumMatrix(c);
  ASSERT_EQ(a.EqMatrix(res), true);
}

TEST(TestMatrix, operator_sum) {
  S21Matrix a = S21Matrix(2, 2);
  S21Matrix b = S21Matrix(2, 3);

  EXPECT_THROW(a + b, std::logic_error);

  a(0, 0) = 2.1;
  a(0, 1) = 0.99999;
  a(1, 0) = -2.1;
  a(1, 1) = 34565131.45646;

  S21Matrix c = S21Matrix(2, 2);
  c(0, 0) = 2.1;
  c(0, 1) = 0.00000001;
  c(1, 0) = 2.1;
  c(1, 1) = 0.45646;

  S21Matrix res = S21Matrix(2, 2);
  res(0, 0) = 2.1 + 2.1;
  res(0, 1) = 0.99999 + 0.00000001;
  res(1, 0) = -2.1 + 2.1;
  res(1, 1) = 34565131.45646 + 0.45646;

  ASSERT_EQ((a + c).EqMatrix(res), true);
}

TEST(TestMatrix, operator_app_sum) {
  S21Matrix a = S21Matrix(2, 2);
  S21Matrix b = S21Matrix(2, 3);

  EXPECT_THROW(a += b, std::logic_error);

  a(0, 0) = 2.1;
  a(0, 1) = 0.99999;
  a(1, 0) = -2.1;
  a(1, 1) = 34565131.45646;

  S21Matrix c = S21Matrix(2, 2);
  c(0, 0) = 2.1;
  c(0, 1) = 0.00000001;
  c(1, 0) = 2.1;
  c(1, 1) = 0.45646;

  S21Matrix res = S21Matrix(2, 2);
  res(0, 0) = 2.1 + 2.1;
  res(0, 1) = 0.99999 + 0.00000001;
  res(1, 0) = -2.1 + 2.1;
  res(1, 1) = 34565131.45646 + 0.45646;

  a += c;

  ASSERT_EQ(a.EqMatrix(res), true);
}

TEST(TestSubMatrix, sub_matrix_1) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix R(2, 2);
  S21Matrix OP(2, 2);
  S21Matrix WR(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 1;
  A(1, 0) = 1;
  A(1, 1) = 1;
  B(0, 0) = 2;
  B(0, 1) = 2;
  B(1, 0) = 2;
  B(1, 1) = 2;
  R(0, 0) = 3;
  R(0, 1) = 3;
  R(1, 0) = 3;
  R(1, 1) = 3;
  S21Matrix RR(R);
  OP = R - B;
  R.SubMatrix(B);
  RR -= B;
  ASSERT_TRUE(R == A);
  ASSERT_TRUE(RR == A);
  ASSERT_TRUE(OP == A);

  EXPECT_THROW(R.SubMatrix(WR), std::logic_error);
}

TEST(TestSubMatrix, sub_matrix_2) {
  S21Matrix A(1, 1);
  S21Matrix B(1, 1);
  S21Matrix R(1, 1);
  S21Matrix OP(1, 1);
  A(0, 0) = 1.25;
  B(0, 0) = 2.25;
  R(0, 0) = 3.5;
  S21Matrix RR(R);
  OP = R - B;
  R.SubMatrix(B);
  RR -= B;
  ASSERT_TRUE(R == A);
  ASSERT_TRUE(RR == A);
  ASSERT_TRUE(OP == A);
}

TEST(TestSubMatrix, sub_matrix_3) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix R(3, 3);
  S21Matrix OP(3, 3);
  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 4.25;
  A(1, 2) = 5.25;
  A(2, 0) = 6.25;
  A(2, 1) = 7.25;
  A(2, 2) = 8.25;

  B(0, 0) = 9.65;
  B(0, 1) = 8.65;
  B(0, 2) = 7.65;
  B(1, 0) = 6.65;
  B(1, 1) = 5.65;
  B(1, 2) = 4.65;
  B(2, 0) = 3.65;
  B(2, 1) = 2.65;
  B(2, 2) = 1.65;

  R(0, 0) = 9.9;
  R(0, 1) = 9.9;
  R(0, 2) = 9.9;
  R(1, 0) = 9.9;
  R(1, 1) = 9.9;
  R(1, 2) = 9.9;
  R(2, 0) = 9.9;
  R(2, 1) = 9.9;
  R(2, 2) = 9.9;
  S21Matrix RR(R);
  OP = R - B;
  R.SubMatrix(B);
  RR -= B;
  ASSERT_TRUE(R == A);
  ASSERT_TRUE(RR == A);
  ASSERT_TRUE(OP == A);
}

TEST(TestSubMatrix, sub_matrix_4) {
  S21Matrix A(1, 1);
  S21Matrix B(2, 1);

  EXPECT_THROW(A.SumMatrix(B), std::logic_error);
}

TEST(TestSubMatrix, sub_matrix_5) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);
  S21Matrix R(4, 4);
  S21Matrix OP(4, 4);
  A(0, 0) = 1.80377;
  A(0, 1) = 3.93870;
  A(0, 2) = 3.13429;
  A(0, 3) = 2.28155;
  A(1, 0) = 1.39307;
  A(1, 1) = 1.05586;
  A(1, 2) = 2.21357;
  A(1, 3) = 2.20440;
  A(2, 0) = 2.74323;
  A(2, 1) = 2.41325;
  A(2, 2) = 3.86805;
  A(2, 3) = 2.73013;
  A(3, 0) = 2.74323;
  A(3, 1) = 2.41325;
  A(3, 2) = 3.86805;
  A(3, 3) = 2.73013;

  B(0, 0) = 1.26273;
  B(0, 1) = 1.04840;
  B(0, 2) = 3.52904;
  B(0, 3) = 2.43282;
  B(1, 0) = 3.77110;
  B(1, 1) = 3.91306;
  B(1, 2) = 2.02829;
  B(1, 3) = 2.98469;
  B(2, 0) = 1.57829;
  B(2, 1) = 1.88621;
  B(2, 2) = 1.51431;
  B(2, 3) = 2.45186;
  B(3, 0) = 3.68725;
  B(3, 1) = 2.39301;
  B(3, 2) = 1.84984;
  B(3, 3) = 2.48786;

  R(0, 0) = 3.0665;
  R(0, 1) = 4.9871;
  R(0, 2) = 6.66333;
  R(0, 3) = 4.71437;
  R(1, 0) = 5.16417;
  R(1, 1) = 4.96892;
  R(1, 2) = 4.24186;
  R(1, 3) = 5.18909;
  R(2, 0) = 4.32152;
  R(2, 1) = 4.29946;
  R(2, 2) = 5.38236;
  R(2, 3) = 5.18199;
  R(3, 0) = 6.43048;
  R(3, 1) = 4.80626;
  R(3, 2) = 5.71789;
  R(3, 3) = 5.21799;

  S21Matrix RR(R);
  OP = R - B;
  R.SubMatrix(B);
  RR -= B;
  ASSERT_TRUE(R == A);
  ASSERT_TRUE(RR == A);
  ASSERT_TRUE(OP == A);
}

TEST(TestSubMatrix, sub_matrix_6) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  S21Matrix R(3, 4);
  A(0, 0) = 1.80377;
  A(0, 1) = 3.93870;
  A(0, 2) = 3.13429;
  A(0, 3) = 2.28155;
  A(1, 0) = 1.39307;
  A(1, 1) = 1.05586;
  A(1, 2) = 2.21357;
  A(1, 3) = 2.20440;
  A(2, 0) = 2.74323;
  A(2, 1) = 2.41325;
  A(2, 2) = 3.86805;
  A(2, 3) = 2.73013;

  B(0, 0) = 1.26273;
  B(0, 1) = 1.04840;
  B(0, 2) = 3.52904;
  B(0, 3) = 2.43282;
  B(1, 0) = 3.77110;
  B(1, 1) = 3.91306;
  B(1, 2) = 2.02829;
  B(1, 3) = 2.98469;
  B(2, 0) = 1.57829;
  B(2, 1) = 1.88621;
  B(2, 2) = 1.51431;
  B(2, 3) = 2.45186;

  R(0, 0) = 3.0665;
  R(0, 1) = 4.9871;
  R(0, 2) = 6.66333;
  R(0, 3) = 4.71437;
  R(1, 0) = 5.16417;
  R(1, 1) = 4.96892;
  R(1, 2) = 4.24186;
  R(1, 3) = 5.18909;
  R(2, 0) = 4.32152;
  R(2, 1) = 4.29946;
  R(2, 2) = 5.38236;
  R(2, 3) = 5.18199;
  S21Matrix OP(4, 4);
  S21Matrix RR(R);
  OP = R - B;
  R.SubMatrix(B);
  RR -= B;
  ASSERT_TRUE(R == A);
  ASSERT_TRUE(RR == A);
  ASSERT_TRUE(OP == A);
}

TEST(TestSubMatrix, sub_matrix_7) {
  S21Matrix A(4, 3);
  S21Matrix B(3, 4);

  EXPECT_THROW(A.SubMatrix(B), std::logic_error);
}

TEST(TestMatrix, sub) {
  S21Matrix a = S21Matrix(2, 2);
  S21Matrix b = S21Matrix(2, 3);

  EXPECT_THROW(a.SubMatrix(b), std::logic_error);

  a(0, 0) = 2.1;
  a(0, 1) = 0.99999;
  a(1, 0) = -2.1;
  a(1, 1) = 34565131.45646;

  S21Matrix c = S21Matrix(2, 2);
  c(0, 0) = 2.1;
  c(0, 1) = 0.00000001;
  c(1, 0) = 2.1;
  c(1, 1) = 0.45646;

  S21Matrix res = S21Matrix(2, 2);
  res(0, 0) = 2.1 - 2.1;
  res(0, 1) = 0.99999 - 0.00000001;
  res(1, 0) = -2.1 - 2.1;
  res(1, 1) = 34565131.45646 - 0.45646;

  a.SubMatrix(c);
  ASSERT_EQ(a.EqMatrix(res), true);
}

TEST(TestMatrix, operator_sub) {
  S21Matrix a = S21Matrix(2, 2);
  S21Matrix b = S21Matrix(2, 3);

  EXPECT_THROW(a - b, std::logic_error);

  a(0, 0) = 2.1;
  a(0, 1) = 0.99999;
  a(1, 0) = -2.1;
  a(1, 1) = 34565131.45646;

  S21Matrix c = S21Matrix(2, 2);
  c(0, 0) = 2.1;
  c(0, 1) = 0.00000001;
  c(1, 0) = 2.1;
  c(1, 1) = 0.45646;

  S21Matrix res = S21Matrix(2, 2);
  res(0, 0) = 2.1 - 2.1;
  res(0, 1) = 0.99999 - 0.00000001;
  res(1, 0) = -2.1 - 2.1;
  res(1, 1) = 34565131.45646 - 0.45646;

  ASSERT_EQ((a - c).EqMatrix(res), true);
}

TEST(TestMatrix, operator_app_sub) {
  S21Matrix a = S21Matrix(2, 2);
  S21Matrix b = S21Matrix(2, 3);

  EXPECT_THROW(a -= b, std::logic_error);

  a(0, 0) = 2.1;
  a(0, 1) = 0.99999;
  a(1, 0) = -2.1;
  a(1, 1) = 34565131.45646;

  S21Matrix c = S21Matrix(2, 2);
  c(0, 0) = 2.1;
  c(0, 1) = 0.00000001;
  c(1, 0) = 2.1;
  c(1, 1) = 0.45646;

  S21Matrix res = S21Matrix(2, 2);
  res(0, 0) = 2.1 - 2.1;
  res(0, 1) = 0.99999 - 0.00000001;
  res(1, 0) = -2.1 - 2.1;
  res(1, 1) = 34565131.45646 - 0.45646;

  a -= c;

  ASSERT_EQ(a.EqMatrix(res), true);
}

TEST(TestMulMatrix, mul_matrix_1) {
  S21Matrix A(1, 1);
  S21Matrix B(1, 1);
  S21Matrix R(1, 1);
  A(0, 0) = -1.57;
  B(0, 0) = 2;
  R(0, 0) = -3.14;

  S21Matrix AA(A);
  S21Matrix OP(1, 1);
  OP = A * B;
  A.MulMatrix(B);
  AA *= B;
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
  ASSERT_TRUE(OP == R);
}

TEST(TestMulMatrix, mul_matrix_2) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  S21Matrix R(3, 3);
  A(0, 0) = 0;
  A(0, 1) = 1;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(2, 0) = 6;
  A(2, 1) = 7;

  B(0, 0) = 9;
  B(0, 1) = 8;
  B(0, 2) = 7;
  B(1, 0) = 6;
  B(1, 1) = 5;
  B(1, 2) = 4;

  R(0, 0) = 6;
  R(0, 1) = 5;
  R(0, 2) = 4;
  R(1, 0) = 51;
  R(1, 1) = 44;
  R(1, 2) = 37;
  R(2, 0) = 96;
  R(2, 1) = 83;
  R(2, 2) = 70;

  S21Matrix AA(A);
  S21Matrix OP(3, 3);
  OP = A * B;
  A.MulMatrix(B);
  AA *= B;
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
  ASSERT_TRUE(OP == R);
}

TEST(TestMulMatrix, mul_matrix_3) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 4);
  S21Matrix R(3, 4);
  A(0, 0) = 0;
  A(0, 1) = 1;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(2, 0) = 6;
  A(2, 1) = 7;

  B(0, 0) = 9;
  B(0, 1) = 8;
  B(0, 2) = 7;
  B(0, 3) = 7;
  B(1, 0) = 6;
  B(1, 1) = 5;
  B(1, 2) = 4;
  B(1, 3) = 7;

  R(0, 0) = 6;
  R(0, 1) = 5;
  R(0, 2) = 4;
  R(0, 3) = 7;
  R(1, 0) = 51;
  R(1, 1) = 44;
  R(1, 2) = 37;
  R(1, 3) = 49;
  R(2, 0) = 96;
  R(2, 1) = 83;
  R(2, 2) = 70;
  R(2, 3) = 91;

  S21Matrix AA(A);
  S21Matrix OP(3, 4);
  OP = A * B;
  A.MulMatrix(B);
  AA *= B;
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
  ASSERT_TRUE(OP == R);
}

TEST(TestMulMatrix, mul_matrix_4) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);
  S21Matrix R(4, 4);
  A(0, 0) = 1.80377;
  A(0, 1) = 3.93870;
  A(0, 2) = 3.13429;
  A(0, 3) = 2.28155;
  A(1, 0) = 1.39307;
  A(1, 1) = 1.05586;
  A(1, 2) = 2.21357;
  A(1, 3) = 2.20440;
  A(2, 0) = 2.74323;
  A(2, 1) = 2.41325;
  A(2, 2) = 3.86805;
  A(2, 3) = 2.73013;
  A(3, 0) = 2.74323;
  A(3, 1) = 2.41325;
  A(3, 2) = 3.86805;
  A(3, 3) = 2.73013;

  B(0, 0) = 1.26273;
  B(0, 1) = 1.04840;
  B(0, 2) = 3.52904;
  B(0, 3) = 2.43282;
  B(1, 0) = 3.77110;
  B(1, 1) = 3.91306;
  B(1, 2) = 2.02829;
  B(1, 3) = 2.98469;
  B(2, 0) = 1.57829;
  B(2, 1) = 1.88621;
  B(2, 2) = 1.51431;
  B(2, 3) = 2.45186;
  B(3, 0) = 3.68725;
  B(3, 1) = 2.39301;
  B(3, 2) = 1.84984;
  B(3, 3) = 2.48786;

  R(0, 0) = 30.4903699;
  R(0, 1) = 28.6751430;
  R(0, 2) = 23.3211914;
  R(0, 3) = 29.5050635;
  R(1, 0) = 17.3626542;
  R(1, 1) = 15.0425472;
  R(1, 2) = 14.4876085;
  R(1, 3) = 17.4521057;
  R(2, 0) = 28.7361424;
  R(2, 1) = 26.1483774;
  R(2, 2) = 25.4834697;
  R(2, 3) = 30.1526862;
  R(3, 0) = 28.7361424;
  R(3, 1) = 26.1483774;
  R(3, 2) = 25.4834697;
  R(3, 3) = 30.1526862;

  S21Matrix AA(A);
  S21Matrix OP(4, 4);
  OP = A * B;
  A.MulMatrix(B);
  AA *= B;
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
  ASSERT_TRUE(OP == R);
}

TEST(TestMulMatrix, mul_matrix_5) {
  S21Matrix A(2, 5);
  S21Matrix B(5, 2);
  S21Matrix R(2, 2);
  B(0, 0) = 1.55365;
  B(0, 1) = 3.68359;
  B(1, 0) = 3.58831;
  B(1, 1) = 3.84431;
  B(2, 0) = 1.41244;
  B(2, 1) = 1.80059;
  B(3, 0) = 2.20100;
  B(3, 1) = 3.95030;
  B(4, 0) = 1.89133;
  B(4, 1) = 2.32189;

  A(0, 0) = 2.15746;
  A(0, 1) = 1.61630;
  A(0, 2) = 2.02538;
  A(0, 3) = 1.24788;
  A(0, 4) = 1.55167;
  A(1, 0) = 3.91035;
  A(1, 1) = 1.25229;
  A(1, 2) = 3.80819;
  A(1, 3) = 1.16017;
  A(1, 4) = 3.14779;

  R(0, 0) = 17.6937548103;
  R(0, 1) = 26.3399427289;
  R(1, 0) = 24.4548037217;
  R(1, 1) = 37.9671476326;

  S21Matrix AA(A);
  S21Matrix OP(2, 2);
  OP = A * B;
  A.MulMatrix(B);
  AA *= B;
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
  ASSERT_TRUE(OP == R);
}

TEST(TestMulMatrix, mul_matrix_6) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);

  EXPECT_THROW(A.MulMatrix(B);, std::logic_error);
}

TEST(TestMatrix, mul) {
  S21Matrix a = S21Matrix(2, 2);
  S21Matrix b = S21Matrix(3, 2);

  EXPECT_THROW(a.MulMatrix(b), std::logic_error);

  a(0, 0) = 2.1;
  a(0, 1) = 0.99999;
  a(1, 0) = -2.1;
  a(1, 1) = 34565131.45646;

  S21Matrix c = S21Matrix(2, 2);
  c(0, 0) = 2.1;
  c(0, 1) = 0.00000001;
  c(1, 0) = 2.1;
  c(1, 1) = 0.45646;

  S21Matrix res = S21Matrix(2, 2);
  res(0, 0) = 2.1 * 2.1 + 0.99999 * 2.1;
  res(0, 1) = 2.1 * 0.00000001 + 0.99999 * 0.45646;
  res(1, 0) = -2.1 * 2.1 + 34565131.45646 * 2.1;
  res(1, 1) = -2.1 * 0.00000001 + 34565131.45646 * 0.45646;

  a.MulMatrix(c);
  ASSERT_EQ(a.EqMatrix(res), true);
}

TEST(TestMatrix, operator_mul) {
  S21Matrix a = S21Matrix(2, 2);
  S21Matrix b = S21Matrix(3, 2);

  EXPECT_THROW(a * b, std::logic_error);

  a(0, 0) = 2.1;
  a(0, 1) = 0.99999;
  a(1, 0) = -2.1;
  a(1, 1) = 34565131.45646;

  S21Matrix c = S21Matrix(2, 2);
  c(0, 0) = 2.1;
  c(0, 1) = 0.00000001;
  c(1, 0) = 2.1;
  c(1, 1) = 0.45646;

  S21Matrix res = S21Matrix(2, 2);
  res(0, 0) = 2.1 * 2.1 + 0.99999 * 2.1;
  res(0, 1) = 2.1 * 0.00000001 + 0.99999 * 0.45646;
  res(1, 0) = -2.1 * 2.1 + 34565131.45646 * 2.1;
  res(1, 1) = -2.1 * 0.00000001 + 34565131.45646 * 0.45646;

  ASSERT_EQ((a * c).EqMatrix(res), true);
}

TEST(TestMatrix, operator_app_mul) {
  S21Matrix a = S21Matrix(2, 2);
  S21Matrix b = S21Matrix(3, 2);

  EXPECT_THROW(a *= b, std::logic_error);

  a(0, 0) = 2.1;
  a(0, 1) = 0.99999;
  a(1, 0) = -2.1;
  a(1, 1) = 34565131.45646;

  S21Matrix c = S21Matrix(2, 2);
  c(0, 0) = 2.1;
  c(0, 1) = 0.00000001;
  c(1, 0) = 2.1;
  c(1, 1) = 0.45646;

  S21Matrix res = S21Matrix(2, 2);
  res(0, 0) = 2.1 * 2.1 + 0.99999 * 2.1;
  res(0, 1) = 2.1 * 0.00000001 + 0.99999 * 0.45646;
  res(1, 0) = -2.1 * 2.1 + 34565131.45646 * 2.1;
  res(1, 1) = -2.1 * 0.00000001 + 34565131.45646 * 0.45646;

  a *= c;
  ASSERT_EQ(a.EqMatrix(res), true);
}

TEST(TestMatrix, mul_1) {
  S21Matrix a = S21Matrix(2, 3);
  a(0, 0) = 2.1;
  a(0, 1) = 0.99999;
  a(0, 2) = 0.0001;
  a(1, 0) = -2.1;
  a(1, 1) = 34565131.45646;
  a(1, 2) = -131.456;

  S21Matrix b = S21Matrix(3, 2);
  b(0, 0) = 2.1;
  b(0, 1) = 0.00000001;
  b(1, 0) = 2.1;
  b(1, 1) = 0.45646;
  b(2, 0) = -5;
  b(2, 1) = 0.45646;

  S21Matrix res = S21Matrix(2, 2);
  res(0, 0) = 2.1 * 2.1 + 0.99999 * 2.1 + 0.0001 * (-5);
  res(0, 1) = 2.1 * 0.00000001 + 0.99999 * 0.45646 + 0.0001 * 0.45646;
  res(1, 0) = -2.1 * 2.1 + 34565131.45646 * 2.1 - 131.456 * (-5);
  res(1, 1) = -2.1 * 0.00000001 + 34565131.45646 * 0.45646 - 131.456 * 0.45646;

  a.MulMatrix(b);
  ASSERT_EQ(a.EqMatrix(res), true);
}

TEST(TestMatrix, mul_2) {
  S21Matrix a = S21Matrix(3, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  a(2, 0) = 5;
  a(2, 1) = 6;

  S21Matrix b = S21Matrix(2, 3);
  b(0, 0) = 0;
  b(0, 1) = 1;
  b(0, 2) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;
  b(1, 2) = 5;

  S21Matrix res = S21Matrix(3, 3);
  res(0, 0) = 1 * 0 + 2 * 3;
  res(0, 1) = 1 * 1 + 2 * 4;
  res(0, 2) = 1 * 2 + 2 * 5;
  res(1, 0) = 3 * 0 + 4 * 3;
  res(1, 1) = 3 * 1 + 4 * 4;
  res(1, 2) = 3 * 2 + 4 * 5;
  res(2, 0) = 5 * 0 + 6 * 3;
  res(2, 1) = 5 * 1 + 6 * 4;
  res(2, 2) = 5 * 2 + 6 * 5;

  a.MulMatrix(b);
  ASSERT_EQ(a.EqMatrix(res), true);
}

TEST(TestMulNumber, mul_number_1) {
  S21Matrix A(1, 1);
  S21Matrix R(1, 1);
  double num = -4.0;

  A(0, 0) = 1.25;
  R(0, 0) = -5.0;

  S21Matrix AA(A);
  S21Matrix OP(1, 1);
  OP = A * num;
  A.MulNumber(num);
  AA *= num;
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
  ASSERT_TRUE(OP == R);
}

TEST(TestMulNumber, mul_number_2) {
  S21Matrix A(3, 3);
  S21Matrix R(3, 3);
  double num = 4.0;
  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 4.25;
  A(1, 2) = 5.25;
  A(2, 0) = 6.25;
  A(2, 1) = 7.25;
  A(2, 2) = 8.25;

  R(0, 0) = 1;
  R(0, 1) = 5;
  R(0, 2) = 9;
  R(1, 0) = 13;
  R(1, 1) = 17;
  R(1, 2) = 21;
  R(2, 0) = 25;
  R(2, 1) = 29;
  R(2, 2) = 33;

  S21Matrix AA(A);
  S21Matrix OP(3, 3);
  OP = A * num;
  A.MulNumber(num);
  AA *= num;
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
  ASSERT_TRUE(OP == R);
}

TEST(TestMulNumber, mul_number_3) {
  S21Matrix A(2, 3);
  S21Matrix R(2, 3);
  double num = 4.0;

  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 4.25;
  A(1, 2) = 5.25;

  R(0, 0) = 1;
  R(0, 1) = 5;
  R(0, 2) = 9;
  R(1, 0) = 13;
  R(1, 1) = 17;
  R(1, 2) = 21;

  S21Matrix AA(A);
  S21Matrix OP(2, 3);
  OP = A * num;
  A.MulNumber(num);
  AA *= num;
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
  ASSERT_TRUE(OP == R);
}

TEST(TestMulNumber, mul_number_4) {
  S21Matrix A(4, 4);
  S21Matrix R(4, 4);
  double num = 0.7;

  A(0, 0) = 1.80377;
  A(0, 1) = 3.93870;
  A(0, 2) = 3.13429;
  A(0, 3) = 2.28155;
  A(1, 0) = 1.39307;
  A(1, 1) = 1.05586;
  A(1, 2) = 2.21357;
  A(1, 3) = 2.20440;
  A(2, 0) = 2.74323;
  A(2, 1) = 2.41325;
  A(2, 2) = 3.86805;
  A(2, 3) = 2.73013;
  A(3, 0) = 2.74323;
  A(3, 1) = 2.41325;
  A(3, 2) = 3.86805;
  A(3, 3) = 2.73013;

  R(0, 0) = 1.80377 * 0.7;
  R(0, 1) = 3.93870 * 0.7;
  R(0, 2) = 3.13429 * 0.7;
  R(0, 3) = 2.28155 * 0.7;
  R(1, 0) = 1.39307 * 0.7;
  R(1, 1) = 1.05586 * 0.7;
  R(1, 2) = 2.21357 * 0.7;
  R(1, 3) = 2.20440 * 0.7;
  R(2, 0) = 2.74323 * 0.7;
  R(2, 1) = 2.41325 * 0.7;
  R(2, 2) = 3.86805 * 0.7;
  R(2, 3) = 2.73013 * 0.7;
  R(3, 0) = 2.74323 * 0.7;
  R(3, 1) = 2.41325 * 0.7;
  R(3, 2) = 3.86805 * 0.7;
  R(3, 3) = 2.73013 * 0.7;

  S21Matrix AA(A);
  S21Matrix OP(4, 4);
  OP = A * num;
  A.MulNumber(num);
  AA *= num;
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
  ASSERT_TRUE(OP == R);
}

TEST(TestMulNumber, mul_number_5) {
  S21Matrix A(2, 3);
  S21Matrix R(2, 3);
  double num = 1234.56;

  S21Matrix AA(A);
  S21Matrix OP(2, 3);
  OP = A * num;
  A.MulNumber(num);
  AA *= num;
  ASSERT_TRUE(A == R);
  ASSERT_TRUE(AA == R);
  ASSERT_TRUE(OP == R);
}

TEST(TestMatrix, mul_number) {
  S21Matrix a = S21Matrix(3, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  a(2, 0) = 5;
  a(2, 1) = 6;

  double val = 0.1;

  S21Matrix res = S21Matrix(3, 2);
  res(0, 0) = 1 * val;
  res(0, 1) = 2 * val;
  res(1, 0) = 3 * val;
  res(1, 1) = 4 * val;
  res(2, 0) = 5 * val;
  res(2, 1) = 6 * val;

  a.MulNumber(val);
  ASSERT_EQ(a.EqMatrix(res), true);
}

TEST(TestMatrix, operator_mul_number) {
  S21Matrix a = S21Matrix(3, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  a(2, 0) = 5;
  a(2, 1) = 6;

  double val = 0.1;

  S21Matrix res = S21Matrix(3, 2);
  res(0, 0) = 1 * val;
  res(0, 1) = 2 * val;
  res(1, 0) = 3 * val;
  res(1, 1) = 4 * val;
  res(2, 0) = 5 * val;
  res(2, 1) = 6 * val;

  ASSERT_EQ((val * a).EqMatrix(res), true);
  ASSERT_EQ((a * val).EqMatrix(res), true);
}

TEST(TestMatrix, operator_app_mul_number) {
  S21Matrix a = S21Matrix(3, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  a(2, 0) = 5;
  a(2, 1) = 6;

  double val = 0.1;

  S21Matrix res = S21Matrix(3, 2);
  res(0, 0) = 1 * val;
  res(0, 1) = 2 * val;
  res(1, 0) = 3 * val;
  res(1, 1) = 4 * val;
  res(2, 0) = 5 * val;
  res(2, 1) = 6 * val;

  a *= val;
  ASSERT_EQ(a.EqMatrix(res), true);
}

TEST(TestEqMatrix, eq_matrix_1) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 1;
  A(1, 0) = 1;
  A(1, 1) = 1;

  B(0, 0) = 1;
  B(0, 1) = 1;
  B(1, 0) = 1;
  B(1, 1) = 1;
  ASSERT_TRUE(A.EqMatrix(B));
  ASSERT_TRUE(A == B);
  A(0, 1) = 2;
  ASSERT_FALSE(A.EqMatrix(B));
}

TEST(TestEqMatrix, eq_matrix_2) {
  S21Matrix A(1, 1);
  S21Matrix B(1, 1);
  A(0, 0) = 5;
  B(0, 0) = 6;
  ASSERT_FALSE(A.EqMatrix(B));
  B(0, 0) = 5;
  ASSERT_TRUE(A.EqMatrix(B));
  ASSERT_TRUE(A == B);
}

TEST(TestEqMatrix, eq_matrix_3) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 4.25;
  A(1, 2) = 5.25;
  A(2, 0) = 6.25;
  A(2, 1) = 7.25;
  A(2, 2) = 8.25;

  B(0, 0) = 0.25;
  B(0, 1) = 1.25;
  B(0, 2) = 2.25;
  B(1, 0) = 3.25;
  B(1, 1) = 4.25;
  B(1, 2) = 5.25;
  B(2, 0) = 6.25;
  B(2, 1) = 7.25;
  B(2, 2) = 8.25;
  ASSERT_TRUE(A.EqMatrix(B));
  ASSERT_TRUE(A == B);
}

TEST(TestEqMatrix, eq_matrix_4) {
  S21Matrix A(2, 3);
  S21Matrix B(3, 3);
  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 4.25;
  A(1, 2) = 5.25;

  B(0, 0) = 0.25;
  B(0, 1) = 1.25;
  B(0, 2) = 2.25;
  B(1, 0) = 3.25;
  B(1, 1) = 4.25;
  B(1, 2) = 5.25;
  B(2, 0) = 6.25;
  B(2, 1) = 7.25;
  B(2, 2) = 8.25;
  ASSERT_FALSE(A.EqMatrix(B));
}

TEST(TestEqMatrix, eq_matrix_5) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);
  A(0, 0) = 1.80377;
  A(0, 1) = 3.93870;
  A(0, 2) = 3.13429;
  A(0, 3) = 2.28155;
  A(1, 0) = 1.39307;
  A(1, 1) = 1.05586;
  A(1, 2) = 2.21357;
  A(1, 3) = 2.20440;
  A(2, 0) = 2.74323;
  A(2, 1) = 2.41325;
  A(2, 2) = 3.86805;
  A(2, 3) = 2.73013;
  A(3, 0) = 2.74323;
  A(3, 1) = 2.41325;
  A(3, 2) = 3.86805;
  A(3, 3) = 2.73013;

  B(0, 0) = 1.80377;
  B(0, 1) = 3.93870;
  B(0, 2) = 3.13429;
  B(0, 3) = 2.28155;
  B(1, 0) = 1.39307;
  B(1, 1) = 1.05586;
  B(1, 2) = 2.21357;
  B(1, 3) = 2.20440;
  B(2, 0) = 2.74323;
  B(2, 1) = 2.41325;
  B(2, 2) = 3.86805;
  B(2, 3) = 2.73013;
  B(3, 0) = 2.74323;
  B(3, 1) = 2.41325;
  B(3, 2) = 3.86805;
  B(3, 3) = 2.73013;
  ASSERT_TRUE(A.EqMatrix(B));
  ASSERT_TRUE(A == B);
}

TEST(TestEqMatrix, eq_matrix_6) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  A(0, 0) = 1.80377;
  A(0, 1) = 3.93870;
  A(0, 2) = 3.13429;
  A(0, 3) = 2.28155;
  A(1, 0) = 1.39307;
  A(1, 1) = 1.05586;
  A(1, 2) = 2.21357;
  A(1, 3) = 2.20440;
  A(2, 0) = 2.74323;
  A(2, 1) = 2.41325;
  A(2, 2) = 3.86805;
  A(2, 3) = 2.73013;

  B(0, 0) = 1.80377;
  B(0, 1) = 3.93870;
  B(0, 2) = 3.13429;
  B(0, 3) = 2.28155;
  B(1, 0) = 1.39307;
  B(1, 1) = 1.05586;
  B(1, 2) = 2.21357;
  B(1, 3) = 2.20440;
  B(2, 0) = 2.74323;
  B(2, 1) = 2.41325;
  B(2, 2) = 3.86805;
  B(2, 3) = 2.73013;

  ASSERT_TRUE(A.EqMatrix(B));
  ASSERT_TRUE(A == B);
}

TEST(TestEqMatrix, eq_matrix_7) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 0;
  A(0, 1) = 0;
  A(1, 0) = 0;
  A(1, 1) = 0;

  ASSERT_TRUE(A.EqMatrix(B));
  ASSERT_TRUE(A == B);
}

TEST(TestDeterminant, comp_1) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 3.0;
  A(1, 1) = 2.0;
  A(1, 2) = 1.0;
  A(2, 0) = 7.0;
  A(2, 1) = 5.0;
  A(2, 2) = 2.0;
  S21Matrix B(3, 3);
  B(0, 0) = -1.0;
  B(0, 1) = 1.0;
  B(0, 2) = 1.0;
  B(1, 0) = 11.0;
  B(1, 1) = -19.0;
  B(1, 2) = 9.0;
  B(2, 0) = -4.0;
  B(2, 1) = 8.0;
  B(2, 2) = -4.0;
  S21Matrix R(3, 3);

  R = A.CalcComplements();
  ASSERT_TRUE(R.EqMatrix(B));
}

TEST(TestDeterminant, comp_2) {
  S21Matrix A(4, 4);
  A(0, 0) = 1.80377;
  A(0, 1) = 3.93870;
  A(0, 2) = 3.13429;
  A(0, 3) = 2.28155;
  A(1, 0) = 1.39307;
  A(1, 1) = 1.05586;
  A(1, 2) = 2.21357;
  A(1, 3) = 2.20440;
  A(2, 0) = 2.74323;
  A(2, 1) = 2.41325;
  A(2, 2) = 3.86805;
  A(2, 3) = 2.73013;
  A(3, 0) = 2.74323;
  A(3, 1) = 2.41325;
  A(3, 2) = 3.86805;
  A(3, 3) = 2.73013;
  S21Matrix B(4, 4);
  B(0, 0) = 0;
  B(0, 1) = 0;
  B(0, 2) = 0;
  B(0, 3) = 0;
  B(1, 0) = 0;
  B(1, 1) = 0;
  B(1, 2) = 0;
  B(1, 3) = 0;
  B(2, 0) = -5.0123523428;
  B(2, 1) = -0.9933255993;
  B(2, 2) = 5.5038169258;
  B(2, 3) = -1.8833757880;
  B(3, 0) = 5.0123523428;
  B(3, 1) = 0.9933255993;
  B(3, 2) = -5.5038169258;
  B(3, 3) = 1.8833757880;
  S21Matrix R(4, 4);

  R = A.CalcComplements();
  ASSERT_TRUE(R.EqMatrix(B));
}

TEST(TestDeterminant, comp_3) {
  S21Matrix A(4, 4);
  A(0, 0) = 1.80377;
  A(0, 1) = 3.93870;
  A(0, 2) = 3.13429;
  A(0, 3) = 2.28155;
  A(1, 0) = 1.39307;
  A(1, 1) = 1.05586;
  A(1, 2) = 2.21357;
  A(1, 3) = 2.20440;
  A(2, 0) = 2.74323;
  A(2, 1) = 2.41325;
  A(2, 2) = 3.86805;
  A(2, 3) = 2.73013;
  A(3, 0) = 2.29065;
  A(3, 1) = 3.09765;
  A(3, 2) = 1.84139;
  A(3, 3) = 3.86339;
  S21Matrix B(4, 4);
  B(0, 0) = -8.0642664633;
  B(0, 1) = 4.1987149757;
  B(0, 2) = 3.1661056480;
  B(0, 3) = -0.0941589509;
  B(1, 0) = -19.1443430067;
  B(1, 1) = -4.4198224214;
  B(1, 2) = 8.7731760020;
  B(1, 3) = 10.7131854857;
  B(2, 0) = 15.1040957594;
  B(2, 1) = -1.3457695400;
  B(2, 2) = -1.9412358558;
  B(2, 3) = -6.9511236616;
  B(3, 0) = 5.0123523428;
  B(3, 1) = 0.9933255993;
  B(3, 2) = -5.5038169258;
  B(3, 3) = 1.8833757880;
  S21Matrix R(4, 4);

  R = A.CalcComplements();
  ASSERT_TRUE(R.EqMatrix(B));
}

TEST(TestDeterminant, comp_4) {
  S21Matrix A(3, 4);
  EXPECT_THROW(A.CalcComplements(), std::logic_error);
}

TEST(TestDeterminant, comp_5) {
  S21Matrix A(1, 1);
  EXPECT_THROW(A.CalcComplements(), std::logic_error);
}

TEST(TestDeterminant, comp_6) {
  S21Matrix A(4, 3);
  EXPECT_THROW(A.CalcComplements(), std::logic_error);
}

TEST(TestDeterminant, comp_7) {
  S21Matrix A(1, 1);
  EXPECT_THROW(A.CalcComplements(), std::logic_error);
}

TEST(TestMatrix, complements) {
  S21Matrix a = S21Matrix(3, 4);

  EXPECT_THROW(a.CalcComplements(), std::logic_error);

  S21Matrix v = S21Matrix(1, 1);
  v(0, 0) = 5;

  EXPECT_THROW(v.CalcComplements(), std::logic_error);

  S21Matrix b = S21Matrix(3, 3);
  b(0, 0) = 1.;
  b(0, 1) = 2.;
  b(0, 2) = 3.;

  b(1, 0) = 0.;
  b(1, 1) = 4.;
  b(1, 2) = 2.;

  b(2, 0) = 5.;
  b(2, 1) = 2.;
  b(2, 2) = 1.;

  S21Matrix res(3, 3);
  S21Matrix R(3, 3);
  res(0, 0) = 0.;
  res(0, 1) = 10.;
  res(0, 2) = -20.;

  res(1, 0) = 4.;
  res(1, 1) = -14.;
  res(1, 2) = 8.;

  res(2, 0) = -8.;
  res(2, 1) = -2.;
  res(2, 2) = 4.;

  R = b.CalcComplements();
  ASSERT_TRUE(R.EqMatrix(res));
}

TEST(TestDeterminant, det_1) {
  S21Matrix A(3, 3);
  A(0, 0) = 3.0;
  A(0, 1) = 3.0;
  A(0, 2) = 3.0;
  A(1, 0) = 2.0;
  A(1, 1) = 4.0;
  A(1, 2) = 4.0;
  A(2, 0) = 1.0;
  A(2, 1) = 3.0;
  A(2, 2) = 6.0;
  double res = 18;
  double det = A.Determinant();

  ASSERT_DOUBLE_EQ(det, res);
}

TEST(TestDeterminant, det_2) {
  S21Matrix A(3, 3);
  A(0, 0) = 0.13807;
  A(0, 1) = 4.10035;
  A(0, 2) = 7.04436;
  A(1, 0) = 5.32393;
  A(1, 1) = 1.70957;
  A(1, 2) = 5.99774;
  A(2, 0) = 3.47567;
  A(2, 1) = 6.88200;
  A(2, 2) = 0.32512;
  double res = 289.00034;
  double det = A.Determinant();

  ASSERT_NEAR(det, res, 10E-6);
}

TEST(TestDeterminant, det_4) {
  S21Matrix A(2, 8);
  EXPECT_THROW(A.Determinant(), std::logic_error);
}

TEST(TestDeterminant, det_5) {
  S21Matrix B(3, 1);
  EXPECT_THROW(B.Determinant(), std::logic_error);
}

TEST(TestDeterminant, det_6) {
  S21Matrix A(1, 1);
  A(0, 0) = 5.4321;
  double res = 5.4321;
  double det = A.Determinant();
  ASSERT_DOUBLE_EQ(det, res);
}

TEST(TestDeterminant, det_7) {
  S21Matrix A(2, 2);
  A(0, 0) = 0;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 1;
  double res = -10;
  double det = A.Determinant();
  ASSERT_DOUBLE_EQ(det, res);
}

TEST(TestMatrix, determinant) {
  S21Matrix a = S21Matrix(3, 4);

  EXPECT_THROW(a.Determinant(), std::logic_error);

  S21Matrix v = S21Matrix(1, 1);
  v(0, 0) = 5;
  ASSERT_EQ(v.Determinant(), 5);

  S21Matrix b = S21Matrix(2, 2);
  b(0, 0) = 5;
  b(0, 1) = 5;
  b(1, 0) = 5;
  b(1, 1) = 5;
  ASSERT_EQ(b.Determinant(), 0);
  b(1, 1) = 10;
  ASSERT_EQ(b.Determinant(), 25);

  S21Matrix c = S21Matrix(4, 4);
  c(0, 0) = -1.2;
  c(0, 1) = 1;
  c(0, 2) = 1.17;
  c(0, 3) = 42;

  c(1, 0) = 1;
  c(1, 1) = 2;
  c(1, 2) = 0.12;
  c(1, 3) = -42;

  c(2, 0) = 0.3;
  c(2, 1) = 3;
  c(2, 2) = 5.35;
  c(2, 3) = 4.2;

  c(3, 0) = 2.4;
  c(3, 1) = 4;
  c(3, 2) = -6.14;
  c(3, 3) = -4.2;

  ASSERT_NEAR(c.Determinant(), -1884.078, 10E-6);
}

TEST(TestMatrix, transpose_1) {
  S21Matrix a = S21Matrix(3, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  a(2, 0) = 5;
  a(2, 1) = 6;

  S21Matrix res = S21Matrix(2, 3);
  res(0, 0) = 1;
  res(0, 1) = 3;
  res(0, 2) = 5;
  res(1, 0) = 2;
  res(1, 1) = 4;
  res(1, 2) = 6;

  S21Matrix t = a.Transpose();
  ASSERT_EQ(t.EqMatrix(res), true);

  t = t.Transpose();
  ASSERT_EQ(t.EqMatrix(a), true);
}

TEST(TestMatrix, transpose_2) {
  S21Matrix a = S21Matrix(1, 1);
  a(0, 0) = 1;

  S21Matrix res = S21Matrix(1, 1);
  res(0, 0) = 1;

  S21Matrix t = a.Transpose();
  ASSERT_EQ(t.EqMatrix(res), true);
}

TEST(TestMatrix, transpose_3) {
  S21Matrix a = S21Matrix(3, 1);
  a(0, 0) = 1;
  a(1, 0) = 2;
  a(2, 0) = 3;

  S21Matrix res = S21Matrix(1, 3);
  res(0, 0) = 1;
  res(0, 1) = 2;
  res(0, 2) = 3;

  S21Matrix t = a.Transpose();
  ASSERT_EQ(t.EqMatrix(res), true);

  t = t.Transpose();
  ASSERT_EQ(t.EqMatrix(a), true);
}

TEST(TestDeterminant, inverse_1) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 3.0;
  A(1, 1) = 2.0;
  A(1, 2) = 1.0;
  A(2, 0) = 7.0;
  A(2, 1) = 5.0;
  A(2, 2) = 2.0;
  S21Matrix B(3, 3);
  B(0, 0) = -0.25;
  B(0, 1) = 2.75;
  B(0, 2) = -1.0;
  B(1, 0) = 0.25;
  B(1, 1) = -4.75;
  B(1, 2) = 2.0;
  B(2, 0) = 0.25;
  B(2, 1) = 2.25;
  B(2, 2) = -1.0;
  S21Matrix R(3, 3);

  R = A.InverseMatrix();
  ASSERT_TRUE(R.EqMatrix(B));
}

TEST(TestDeterminant, inverse_2) {
  S21Matrix A(3, 3);
  A(0, 0) = 0.13807;
  A(0, 1) = 4.10035;
  A(0, 2) = 7.04436;
  A(1, 0) = 5.32393;
  A(1, 1) = 1.70957;
  A(1, 2) = 5.99774;
  A(2, 0) = 3.47567;
  A(2, 1) = 6.88200;
  A(2, 2) = 0.32512;
  S21Matrix B(3, 3);
  B(0, 0) = -0.1409016702;
  B(0, 1) = 0.1631353754;
  B(0, 2) = 0.0434255769;
  B(1, 0) = 0.0661426507;
  B(1, 1) = -0.0845638486;
  B(1, 2) = 0.1269049405;
  B(2, 0) = 0.1062191989;
  B(2, 1) = 0.0460250861;
  B(2, 2) = -0.0747194127;
  S21Matrix R(3, 3);

  R = A.InverseMatrix();
  ASSERT_TRUE(R.EqMatrix(B));
}

TEST(TestDeterminant, inverse_3) {
  S21Matrix A(4, 4);
  A(0, 0) = 1.80377;
  A(0, 1) = 3.93870;
  A(0, 2) = 3.13429;
  A(0, 3) = 2.28155;
  A(1, 0) = 1.39307;
  A(1, 1) = 1.05586;
  A(1, 2) = 2.21357;
  A(1, 3) = 2.20440;
  A(2, 0) = 2.74323;
  A(2, 1) = 2.41325;
  A(2, 2) = 3.86805;
  A(2, 3) = 2.73013;
  A(3, 0) = 2.74323;
  A(3, 1) = 2.41325;
  A(3, 2) = 3.86805;
  A(3, 3) = 2.73013;
}

TEST(TestDeterminant, inverse_4) {
  S21Matrix A(4, 4);
  A(0, 0) = 1.80377;
  A(0, 1) = 3.93870;
  A(0, 2) = 3.13429;
  A(0, 3) = 2.28155;
  A(1, 0) = 1.39307;
  A(1, 1) = 1.05586;
  A(1, 2) = 2.21357;
  A(1, 3) = 2.20440;
  A(2, 0) = 2.74323;
  A(2, 1) = 2.41325;
  A(2, 2) = 3.86805;
  A(2, 3) = 2.73013;
  A(3, 0) = 2.29065;
  A(3, 1) = 3.09765;
  A(3, 2) = 1.84139;
  A(3, 3) = 3.86339;
  S21Matrix B(4, 4);
  B(0, 0) = -0.6892499107;
  B(0, 1) = -1.6362600080;
  B(0, 2) = 1.2909415507;
  B(0, 3) = 0.4284039249;
  B(1, 0) = 0.3588626362;
  B(1, 1) = -0.3777606089;
  B(1, 2) = -0.1150224313;
  B(1, 3) = 0.0848991764;
  B(2, 0) = 0.2706058939;
  B(2, 1) = 0.7498401502;
  B(2, 2) = -0.1659167199;
  B(2, 3) = -0.4704092234;
  B(3, 0) = -0.0080477312;
  B(3, 1) = 0.9156520525;
  B(3, 2) = -0.5941100018;
  B(3, 3) = 0.1609714411;
  S21Matrix R(4, 4);

  R = A.InverseMatrix();
  ASSERT_TRUE(R.EqMatrix(B));
}

TEST(TestDeterminant, inverse_5) {
  S21Matrix A(3, 4);
  EXPECT_THROW(A.InverseMatrix(), std::logic_error);
}

TEST(TestDeterminant, inverse_6) {
  S21Matrix A(1, 1);
  EXPECT_THROW(A.InverseMatrix(), std::logic_error);
}

TEST(TestDeterminant, inverse_7) {
  S21Matrix A(4, 3);
  EXPECT_THROW(A.InverseMatrix(), std::logic_error);
}

TEST(TestDeterminant, inverse_8) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 1.0;
  A(1, 1) = 2.0;
  A(1, 2) = 4.0;
  A(2, 0) = 7.0;
  A(2, 1) = 5.0;
  A(2, 2) = 2.0;
  S21Matrix B(3, 3);
  B(0, 0) = -1.7777777778;
  B(0, 1) = 1.2222222222;
  B(0, 2) = 0.2222222222;
  B(1, 0) = 2.8888888889;
  B(1, 1) = -2.1111111111;
  B(1, 2) = -0.1111111111;
  B(2, 0) = -1.0;
  B(2, 1) = 1.0;
  B(2, 2) = 0.0;
  S21Matrix R(3, 3);

  R = A.InverseMatrix();
  ASSERT_TRUE(R.EqMatrix(B));
}

TEST(TestMatrix, inverse) {
  S21Matrix a = S21Matrix(3, 4);

  EXPECT_THROW(a.InverseMatrix(), std::logic_error);

  S21Matrix b = S21Matrix(3, 3);
  b(0, 0) = 1.;
  b(0, 1) = 2.;
  b(0, 2) = 3.;

  b(1, 0) = 0.;
  b(1, 1) = 4.;
  b(1, 2) = 2.;

  b(2, 0) = 5.;
  b(2, 1) = 2.;
  b(2, 2) = 1.;

  S21Matrix res = S21Matrix(3, 3);
  res(0, 0) = 0.;
  res(0, 1) = -0.1;
  res(0, 2) = 0.2;

  res(1, 0) = -0.25;
  res(1, 1) = 0.35;
  res(1, 2) = 0.05;

  res(2, 0) = 0.5;
  res(2, 1) = -0.2;
  res(2, 2) = -0.1;
  S21Matrix inv = b.InverseMatrix();

  ASSERT_EQ(inv == res, true);

  b(2, 0) = 2.;
  b(2, 1) = 4.;
  b(2, 2) = 6.;

  EXPECT_THROW(b.InverseMatrix(), std::logic_error);
}

TEST(OVERRIDE, Equal) {
  S21Matrix res1(3, 3);
  S21Matrix res2(3, 3);

  res1(1, 1) = 3;
  res2(1, 1) = 3;

  GTEST_ASSERT_TRUE(res1 == res2);
}

TEST(OVERRIDE, PlusEqual) {
  S21Matrix res1(3, 3);
  S21Matrix res2(3, 3);
  S21Matrix res3(3, 3);

  res1(1, 1) = 3;
  res2(1, 1) = 3;
  res3(1, 1) = 6.000000;

  res1 += res2;
  GTEST_ASSERT_TRUE(res1(1, 1) == res3(1, 1));
}

TEST(OVERRIDE, c) {
  S21Matrix res1(3, 3);
  S21Matrix res2(3, 3);

  res1(0, 0) = 3;
  res1(0, 1) = 3;
  res1(0, 2) = 3;
  res1(1, 0) = 4;
  res1(1, 1) = 4;
  res1(1, 2) = 4;
  res1(2, 0) = 5;
  res1(2, 1) = 5;
  res1(2, 2) = 5;

  res2(0, 0) = 18;
  res2(0, 1) = 18;
  res2(0, 2) = 18;
  res2(1, 0) = 24;
  res2(1, 1) = 24;
  res2(1, 2) = 24;
  res2(2, 0) = 30;
  res2(2, 1) = 30;
  res2(2, 2) = 30;

  res1 = 3 * res1;
  res1 = res1 * 2;

  GTEST_ASSERT_TRUE(res1 == res2);
}

TEST(OVERRIDE, MulMatrixNumberEqual) {
  S21Matrix res1(3, 3);
  S21Matrix res2(3, 3);

  res1(0, 0) = 3;
  res1(0, 1) = 3;
  res1(0, 2) = 3;
  res1(1, 0) = 4;
  res1(1, 1) = 4;
  res1(1, 2) = 4;
  res1(2, 0) = 5;
  res1(2, 1) = 5;
  res1(2, 2) = 5;

  res2(0, 0) = 18;
  res2(0, 1) = 18;
  res2(0, 2) = 18;
  res2(1, 0) = 24;
  res2(1, 1) = 24;
  res2(1, 2) = 24;
  res2(2, 0) = 30;
  res2(2, 1) = 30;
  res2(2, 2) = 30;

  res1 *= 6;

  GTEST_ASSERT_TRUE(res1 == res2);
}

TEST(OVERRIDE, Mul) {
  S21Matrix res1(3, 3);
  S21Matrix res2(3, 3);
  S21Matrix expected(3, 3);

  res1(0, 0) = 3;
  res1(0, 1) = 2;
  res1(0, 2) = 1;
  res1(1, 0) = 4;
  res1(1, 1) = 5;
  res1(1, 2) = 6;
  res1(2, 0) = 7;
  res1(2, 1) = 8;
  res1(2, 2) = 9;

  res2(0, 0) = 3;
  res2(0, 1) = 2;
  res2(0, 2) = 1;
  res2(1, 0) = 4;
  res2(1, 1) = 5;
  res2(1, 2) = 6;
  res2(2, 0) = 7;
  res2(2, 1) = 8;
  res2(2, 2) = 9;

  expected(0, 0) = 24;
  expected(0, 1) = 24;
  expected(0, 2) = 24;
  expected(1, 0) = 74;
  expected(1, 1) = 81;
  expected(1, 2) = 88;
  expected(2, 0) = 116;
  expected(2, 1) = 126;
  expected(2, 2) = 136;

  res1 = res1 * res2;
  GTEST_ASSERT_TRUE(res1 == expected);
}

TEST(OVERRIDE, MulEqual) {
  S21Matrix res1(3, 3);
  S21Matrix res2(3, 3);
  S21Matrix expected(3, 3);

  res1(0, 0) = 3;
  res1(0, 1) = 2;
  res1(0, 2) = 1;
  res1(1, 0) = 4;
  res1(1, 1) = 5;
  res1(1, 2) = 6;
  res1(2, 0) = 7;
  res1(2, 1) = 8;
  res1(2, 2) = 9;

  res2(0, 0) = 3;
  res2(0, 1) = 2;
  res2(0, 2) = 1;
  res2(1, 0) = 4;
  res2(1, 1) = 5;
  res2(1, 2) = 6;
  res2(2, 0) = 7;
  res2(2, 1) = 8;
  res2(2, 2) = 9;

  expected(0, 0) = 24;
  expected(0, 1) = 24;
  expected(0, 2) = 24;
  expected(1, 0) = 74;
  expected(1, 1) = 81;
  expected(1, 2) = 88;
  expected(2, 0) = 116;
  expected(2, 1) = 126;
  expected(2, 2) = 136;

  res1 *= res2;
  GTEST_ASSERT_TRUE(res1 == expected);
}

TEST(OVERRIDE, ASSignment) {
  S21Matrix res1(3, 3);

  int counter = 0;

  for (int i = 0; i < res1.GetRows(); ++i) {
    for (int j = 0; j < res1.GetCols(); ++j) {
      counter++;
      res1(i, j) = counter;
    }
  }

  S21Matrix res2(2, 2);
  res2 = res1;

  GTEST_ASSERT_TRUE(res1 == res2);
}

TEST(OVERRIDE, Plus) {
  S21Matrix res1(3, 3);
  S21Matrix res2(3, 3);
  int counter = 0;

  for (int i = 0; i < res1.GetRows(); ++i) {
    for (int j = 0; j < res1.GetCols(); ++j) {
      counter++;
      res1(i, j) = counter;
    }
  }

  res2 = res1 + res2;

  GTEST_ASSERT_TRUE(res1 == res2);
}

TEST(OVERRIDE, Minus) {
  S21Matrix res1(3, 3);
  int counter = 0;

  for (int i = 0; i < res1.GetRows(); ++i) {
    for (int j = 0; j < res1.GetCols(); ++j) {
      counter++;
      res1(i, j) = counter;
    }
  }

  res1 = res1 - res1;

  GTEST_ASSERT_EQ(res1(1, 1), 0);
}

TEST(OVERRIDE, MinusEqual) {
  S21Matrix res1(3, 3);
  S21Matrix res2(3, 3);
  int counter = 0;

  for (int i = 0; i < res1.GetRows(); ++i) {
    for (int j = 0; j < res1.GetCols(); ++j) {
      counter++;
      res1(i, j) = counter;
    }
  }

  res1 -= res2;

  GTEST_ASSERT_EQ(res1(1, 1), 5);
}

TEST(FUNCTIONS, Transpose) {
  S21Matrix res1(3, 3);
  S21Matrix res2(3, 3);

  res1(0, 0) = 3;
  res1(0, 1) = 3;
  res1(0, 2) = 3;
  res1(1, 0) = 4;
  res1(1, 1) = 4;
  res1(1, 2) = 4;
  res1(2, 0) = 5;
  res1(2, 1) = 5;
  res1(2, 2) = 5;

  res2(0, 0) = 3;
  res2(0, 1) = 4;
  res2(0, 2) = 5;
  res2(1, 0) = 3;
  res2(1, 1) = 4;
  res2(1, 2) = 5;
  res2(2, 0) = 3;
  res2(2, 1) = 4;
  res2(2, 2) = 5;

  res1 = res1.Transpose();
  GTEST_ASSERT_TRUE(res1 == res2);
}

TEST(FUNCTIONS, Determinant) {
  S21Matrix res1(3, 3);
  int counter = 0;

  for (int i = 0; i < res1.GetRows(); ++i) {
    for (int j = 0; j < res1.GetCols(); ++j) {
      counter++;
      res1(i, j) = counter;
    }
  }
  res1(1, 1) = 1123;

  GTEST_ASSERT_EQ(res1.Determinant(), -13416);
}

TEST(FUNCTIONS, InverseMatrix) {
  S21Matrix test(3, 3);
  S21Matrix expected(3, 3);

  test(0, 0) = 3;
  test(0, 1) = 4;
  test(0, 2) = 5;
  test(1, 0) = 1;
  test(1, 1) = 2;
  test(1, 2) = 6;
  test(2, 0) = 7;
  test(2, 1) = 8;
  test(2, 2) = 9;

  expected(0, 0) = -2.5;
  expected(0, 1) = 1. / 3;
  expected(0, 2) = 3.5 / 3;
  expected(1, 0) = 2.75;
  expected(1, 1) = -2. / 3;
  expected(1, 2) = -3.25 / 3;
  expected(2, 0) = -0.5;
  expected(2, 1) = 1. / 3;
  expected(2, 2) = 1. / 6;

  S21Matrix result = test.InverseMatrix();

  GTEST_ASSERT_TRUE(result == expected);
}

TEST(FUNCTIONS, CalcComplements) {
  S21Matrix test(3, 3);
  test(0, 0) = 1;
  test(0, 1) = 2;
  test(0, 2) = 3;
  test(1, 0) = 0;
  test(1, 1) = 4;
  test(1, 2) = 2;
  test(2, 0) = 5;
  test(2, 1) = 2;
  test(2, 2) = 1;

  S21Matrix expected(3, 3);
  expected(0, 0) = 0;
  expected(0, 1) = 10;
  expected(0, 2) = -20;
  expected(1, 0) = 4;
  expected(1, 1) = -14;
  expected(1, 2) = 8;
  expected(2, 0) = -8;
  expected(2, 1) = -2;
  expected(2, 2) = 4;

  S21Matrix result = test.CalcComplements();

  GTEST_ASSERT_TRUE(result == expected);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
