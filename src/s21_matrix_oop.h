#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstring>

#define EPS 1e-7

class S21Matrix {
 private:
    int rows_, columns_;
    double **matrix_;

 public:
//  Methods for filling matrix
    void print_matrix();
    void fill_matrix();
    void set_values(const double* num_array);

//  Constructors and destructor

    S21Matrix();
    S21Matrix(int rows, int columns);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

//  Operators overloads

    void operator = (const S21Matrix& other);
    void operator = (S21Matrix&& other);
    void operator -= (const S21Matrix& other);
    void operator += (const S21Matrix& other);
    S21Matrix operator - (const S21Matrix& other);
    S21Matrix operator + (const S21Matrix& other);
    void operator *= (const S21Matrix& other);
    void operator *= (double num);
    S21Matrix operator * (const S21Matrix& other);
    S21Matrix operator * (double num);
    bool operator == (const S21Matrix& other);
    bool operator != (const S21Matrix& other);
    double& operator() (int i, int j);

// Main methods

    void set_rows(int new_rows);
    void set_columns(int new_cols);
    void set_size(int new_rows, int new_cols);
    int get_rows();
    int get_cols();
    bool eq_matrix(const S21Matrix& other);
    void sum_matrix(const S21Matrix& other);
    void sub_matrix(const S21Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const S21Matrix& other);
    S21Matrix transpose();
    S21Matrix calc_complements();
    double determinant();
    S21Matrix inverse_matrix();
    void fill_minor_matrix(const S21Matrix& prev_matrix, int deleted_row,
                                  int deleted_col, S21Matrix* minor);

// Internal methods

 private:
    bool is_squared_();
    void set_equal_values_(const S21Matrix& other);
    double find_determinant_(const S21Matrix& matrix, double *determinant);
    bool is_rows_and_cols_eq_(const S21Matrix& matrix1, const S21Matrix& matrix2);
    bool is_null_(const S21Matrix& matrix1, const S21Matrix& matrix2);
    bool is_null_(const S21Matrix& matrix);
    void copy_constructor_(const S21Matrix& other);
    void remove_matrix_();
};

#endif  // SRC_S21_MATRIX_OOP_H_
