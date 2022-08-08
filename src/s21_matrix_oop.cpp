#include "s21_matrix_oop.h"

// int main() {
//     S21Matrix m1(2,2);
//     m1(0,0) = 1;
//     std::cout<<m1(0,0)<<std::endl;

//     return 0;
// }

void S21Matrix::print_matrix() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            printf("%lf ", this->matrix_[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// базовый конструктор
S21Matrix::S21Matrix() : S21Matrix(3, 3) { ; }

// параметризированный конструктор
S21Matrix::S21Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
    if (rows <= 0 || columns <= 0)
        throw std::out_of_range("Out of range");
    this->matrix_ = new double* [rows];
    for (int i = 0 ; i < rows; i++) {
        this->matrix_[i] = new double[columns]();
    }
}

// конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other) : S21Matrix(other.rows_, other.columns_) {
    this->set_equal_values_(other);
}

// конструктор перемещения
S21Matrix::S21Matrix(S21Matrix&& other) : rows_(other.rows_),
            columns_(other.columns_), matrix_(other.matrix_) {
    other.columns_ = 0;
    other.rows_ = 0;
    other.matrix_ = nullptr;
}

// Перегрузка =, вызывается либо присваивание либо инициализация
void S21Matrix::operator = (const S21Matrix& other) {
    if (is_null_(*this))
       this->copy_constructor_(other);
    else
       this->set_equal_values_(other);
}

// вызов конструктора копирования
void S21Matrix::copy_constructor_(const S21Matrix& other) {
    S21Matrix tmp(other);
    this->rows_ = tmp.rows_;
    this->columns_ = tmp.columns_;
    this->matrix_ = tmp.matrix_;
    tmp.matrix_ = nullptr;
}

void S21Matrix::operator=(S21Matrix&& other) {
    this->remove_matrix_();
    rows_ = other.rows_;
    columns_ = other.columns_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
}

// перегрузка присваивания вычитания
void S21Matrix::operator -= (const S21Matrix& other) {
    this->sub_matrix(other);
}

// перегрузка присваивания сложения
void S21Matrix::operator += (const S21Matrix& other) {
    this->sum_matrix(other);
}

// перегрузка вычитания
S21Matrix S21Matrix::operator - (const S21Matrix& other) {
    S21Matrix result(*this);
    result.sub_matrix(other);
    return result;
}

// перегрузка сложения
S21Matrix S21Matrix::operator + (const S21Matrix& other) {
    S21Matrix result(*this);
    result.sum_matrix(other);
    return result;
}

// перегрузка присваивания умножения на матрицу
void S21Matrix::operator *= (const S21Matrix& other) {
    this->mul_matrix(other);
}

// перегрузка присваивания умножения на число
void S21Matrix::operator *= (double num) {
    this->mul_number(num);
}

// перегрузка умножения на матрицу
S21Matrix S21Matrix::operator * (const S21Matrix& other) {
    S21Matrix result(*this);
    result.mul_matrix(other);
    return result;
}

// перегрузка умножения на число
S21Matrix S21Matrix::operator * (double num) {
    S21Matrix result(*this);
    result.mul_number(num);
    return result;
}

// перегрузка равенства матриц
bool S21Matrix::operator == (const S21Matrix& other) {
    return this->eq_matrix(other);
}

// перегрузка неравенства матриц
bool S21Matrix::operator != (const S21Matrix& other) {
    return !(this->eq_matrix(other));
}

// перегрузка индексации
double& S21Matrix::operator() (int i, int j) {
    if (i >= rows_ || j >= columns_ || i < 0 || j < 0)
        throw std::out_of_range("Out of range");
    return this->matrix_[i][j];
}

// деструктор
S21Matrix::~S21Matrix() {
    this->remove_matrix_();
}

// чистка памяти матрицы
void S21Matrix::remove_matrix_() {
    if (!is_null_(*this)) {
        for (int i = 0; i < this->rows_; i++)
            delete [] (this->matrix_[i]);
        delete [] (this->matrix_);
    }
}

// проверка матриц на nullptr
bool S21Matrix::is_null_(const S21Matrix& matrix_1, const S21Matrix& matrix_2) {
    return !(matrix_1.matrix_ != nullptr && matrix_2.matrix_ != nullptr);
}

// проверка матрицы на nullptr
bool S21Matrix::is_null_(const S21Matrix& matrix) {
    return matrix.matrix_ != nullptr ? false : true;
}

// Равны ли rows и cols у матриц
bool S21Matrix::is_rows_and_cols_eq_(const S21Matrix& matrix_1, const S21Matrix& matrix_2) {
    return ((matrix_1.columns_ == matrix_2.columns_) && (matrix_1.rows_ == matrix_2.rows_)) ? true : false;
}

// ресайз матрицы по rows
void S21Matrix::set_rows(int new_rows) {
    if (new_rows <= 0)
        throw std::out_of_range("Out of range");
    if (new_rows != this->rows_) {
        int rows_iter = (this->rows_ < new_rows) ? this->rows_ : new_rows;
        S21Matrix tmp(new_rows, this->columns_);
        for (int i = 0; i < rows_iter; i++)
            for (int j = 0; j < this->columns_; j++)
                tmp.matrix_[i][j] = this->matrix_[i][j];
        this->remove_matrix_();
        this->matrix_ = tmp.matrix_;
        this->rows_ = new_rows;
        tmp.matrix_ = nullptr;
    }
}

// ресайз матрицы по cols
void S21Matrix::set_columns(int new_cols) {
    if (new_cols <= 0)
        throw std::out_of_range("Out of range");
    if (new_cols != this->columns_) {
        int cols_iter = (this->columns_ < new_cols) ? this->columns_ : new_cols;
        S21Matrix tmp(this->rows_, new_cols);
        for (int i = 0; i < this->rows_; i++)
            for (int j = 0; j < cols_iter; j++)
                tmp.matrix_[i][j] = this->matrix_[i][j];
        this->remove_matrix_();
        this->matrix_ = tmp.matrix_;
        this->columns_ = new_cols;
        tmp.matrix_ = nullptr;
    }
}

// ресайз матрицы по двум координатам
void S21Matrix::set_size(int new_rows, int new_cols) {
    if (new_cols <= 0 || new_rows <= 0)
        throw std::out_of_range("Out of range");
    if (new_cols != columns_ || new_rows != rows_) {
        int cols_iter = (columns_ < new_cols) ? columns_ : new_cols;
        int rows_iter = (rows_ < new_rows) ? rows_ : new_rows;
        S21Matrix tmp(new_rows, new_cols);
        for (int i = 0; i < rows_iter; i++)
            for (int j = 0; j < cols_iter; j++)
                tmp.matrix_[i][j] = matrix_[i][j];
        remove_matrix_();
        matrix_ = tmp.matrix_;
        columns_ = new_cols;
        rows_ = new_rows;
        tmp.matrix_ = nullptr;
    }
}

// получение кол-ва колонок матрицы
int S21Matrix::get_cols() {
    if (is_null_(*this))
        throw std::out_of_range("Out of range");
    return this->columns_;
}

// получения кол-ва кол-ва строк матрицы
int S21Matrix::get_rows() {
    if (is_null_(*this))
        throw std::out_of_range("Out of range");
    return this->rows_;
}

// Приравнивает матрицы
void S21Matrix::set_equal_values_(const S21Matrix& other) {
    this->set_size(other.rows_, other.columns_);
    for (int i = 0; i < rows_; i++)
        std::copy(other.matrix_[i], other.matrix_[i] + columns_, matrix_[i]);
}

// Проверяет что матрица квадратная
bool S21Matrix::is_squared_() {
    return this->rows_ == this->columns_ ? true : false;
}

// Проверяет матрицы на равенство между собой
bool S21Matrix::eq_matrix(const S21Matrix& other) {
    bool eq_result = true;
    if (!is_null_(*this, other) && is_rows_and_cols_eq_(*this, other)) {
        for (int i = 0; i < this->rows_ && eq_result; i++)
            for (int j = 0; j < this->columns_ && eq_result; j++)
                if (this->matrix_[i][j] != other.matrix_[i][j])
                    eq_result = false;
    } else {
        eq_result = false;
    }
    return eq_result;
}

// Прибавляет вторую матрицу к текущей
void S21Matrix::sum_matrix(const S21Matrix& other) {
    if (is_null_(*this, other) || !is_rows_and_cols_eq_(*this, other))
        throw std::out_of_range("Out of range");
    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            this->matrix_[i][j] += other.matrix_[i][j];
}

// Вычитает из текущей матрицы другую
void S21Matrix::sub_matrix(const S21Matrix& other) {
    if (is_null_(*this, other) || !is_rows_and_cols_eq_(*this, other))
        throw std::out_of_range("Out of range");
    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            this->matrix_[i][j] -= other.matrix_[i][j];
}

// Умножает текущую матрицу на число
void S21Matrix::mul_number(const double num) {
    if (!is_null_(*this)) {
        for (int i = 0; i < this->rows_; i++)
                for (int j = 0; j < this->columns_; j++)
                    this->matrix_[i][j] *= num;
    }
}

// Умножает текущую матрицу на вторую
void S21Matrix::mul_matrix(const S21Matrix& other) {
    if (is_null_(*this, other) || this->columns_ != other.rows_)
        throw std::out_of_range("Out of range");
    S21Matrix res_matrix(this->rows_, other.columns_);
    if (!is_null_(res_matrix)) {
        for (int i = 0; i < this->rows_; i++)
            for (int j = 0; j < other.columns_; j++)
                for (int k = 0; k < this->columns_; k++)
                    res_matrix.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
        *this = res_matrix;
    }
}

// Создает новую транспонированную матрицу из текущей и возвращает ее
S21Matrix S21Matrix::transpose() {
    S21Matrix res_matrix(this->columns_, this->rows_);
    if (!is_null_(*this, res_matrix)) {
        for (int i = 0; i < this->rows_; i++)
                for (int j = 0; j < this->columns_; j++)
                    res_matrix.matrix_[j][i] = this->matrix_[i][j];
    }
    return res_matrix;
}

// Высчитывает определитель
double S21Matrix::determinant() {
    if (!is_squared_())
        throw std::out_of_range("Out of range");
    double determinant = 0;
    return find_determinant_(*this, &determinant);
}

double S21Matrix::find_determinant_(const S21Matrix& matrix, double *determinant) {
    *determinant = 0;
    if (matrix.rows_ == 1) {
        *determinant = matrix.matrix_[0][0];
    } else if (matrix.rows_ == 2) {
        *determinant = matrix.matrix_[0][0] * matrix.matrix_[1][1]
                    - matrix.matrix_[0][1] * matrix.matrix_[1][0];
    } else {
        S21Matrix minor_matrix(matrix.rows_ - 1, matrix.columns_ - 1);
        for (int i = 0; i < matrix.columns_; i++) {
            double tmp = 0;
            fill_minor_matrix(matrix, 0, i, &minor_matrix);
            find_determinant_(minor_matrix, &tmp);
            tmp *= pow(-1, i + 2);
            *determinant += (matrix.matrix_[0][i]) * tmp;
        }
    }
    return *determinant;
}

void S21Matrix::fill_minor_matrix(const S21Matrix& prev_matrix, int deleted_row,
                                  int deleted_col, S21Matrix* minor) {
    if ((*minor).matrix_ != nullptr) {
        for (int row = 0, row_small = 0; row < prev_matrix.rows_; row++) {
            if (row != deleted_row) {
                for (int col = 0, col_small = 0; col < prev_matrix.columns_;
                     col++) {
                    if (col != deleted_col) {
                        (*minor).matrix_[row_small][col_small++] =
                            prev_matrix.matrix_[row][col];
                    }
                }
                row_small++;
            }
        }
    }
}

// Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
S21Matrix S21Matrix::calc_complements() {
    S21Matrix result_mtrx(this->rows_, this->columns_);
    if (is_null_(*this, result_mtrx) && !(this->is_squared_()))
        throw std::out_of_range("Out of range");
    S21Matrix minor(this->rows_ - 1, this->columns_ - 1);
    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++) {
            fill_minor_matrix(*this, i, j, &minor);
            result_mtrx.matrix_[i][j] = pow(-1, i + j + 2) * minor.determinant();
        }
    return result_mtrx;
}

// Вычисляет и возвращает обратную матрицу
S21Matrix S21Matrix::inverse_matrix() {
    S21Matrix res_mtrx = *this;
    if (fabs(this->determinant()) < EPS)
        throw std::out_of_range("Out of range");
    res_mtrx = res_mtrx.transpose().calc_complements();
    res_mtrx.mul_number(1.0/ this->determinant());
    return res_mtrx;
}

// заполнение матрицы стандартными значениями 1 - ...
void S21Matrix::fill_matrix() {
    int k = 1;
    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            this->matrix_[i][j] = k++;
}

// заполнение матрицы данными из массива double
void S21Matrix::set_values(const double* num_array) {
    int k = 0;
    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            this->matrix_[i][j] = num_array[k++];
}
