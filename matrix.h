#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <initializer_list>
#include <vector>

template <typename T>
struct Matrix
{
private:
    int rows{}, cols{};
    std::vector<std::vector<T>> matrix{};

public:
    Matrix(std::initializer_list<std::initializer_list<T>>&& m)
    {
        this->rows = m.size();
        this->cols = (*m.begin()).size();
        for (const auto& row : m)
            this->matrix.push_back(row);
    }

    Matrix(std::initializer_list<std::initializer_list<T>>& m)
    {
        this->rows = m.size();
        this->cols = (*m.begin()).size();
        for (const auto& row : m)
            this->matrix.push_back(row);
    }

    const T& GetValue(int row, int col)
    {
        return this->matrix[row][col];
    }

    void InitZero(int rows, int cols)
    {
        this->matrix.clear();

        this->rows = rows;
        this->cols = cols;

        std::vector<T> elems{};
        for (auto c = 0; c < cols; c++)
            elems.push_back(0);

        for (auto r = 0; r < rows; r++)
            this->matrix.push_back(elems);
    }

    std::vector<std::vector<T>>& GetMatrix()
    {
        return this->matrix;
    }

    const int& GetRows()
    {
        return this->rows;
    }

    const int& GetCols()
    {
        return this->cols;
    }

    Matrix& operator+(const Matrix& matrix)
    {
        if (this->rows == matrix.rows && this->cols == matrix.cols)
        {
            for (auto row = 0; row < this->rows; row++)
            {
                for (auto col = 0; col < this->cols; col++)
                    this->matrix[row][col] += matrix.matrix[row][col]; 
            }

            return *this;
        }
    }

    Matrix& operator+=(const Matrix& matrix)
    {
        this->operator+(matrix);
        return *this;
    }

    Matrix& operator-(const Matrix& matrix)
    {
        if (this->rows == matrix.rows && this->cols == matrix.cols)
        {
            for (auto row = 0; row < this->rows; row++)
            {
                for (auto col = 0; col < this->cols; col++)
                    this->matrix[row][col] -= matrix.matrix[row][col]; 
            }

            return *this;
        }
    }

    Matrix& operator-=(const Matrix& matrix)
    {
        this->operator-(matrix);
        return *this;
    }

    Matrix& operator*(const T& value)
    {
        for (auto& row : this->matrix)
            for (auto& colValue : row)
                colValue *= value;

        return *this;
    }

    Matrix& operator*=(const T& value)
    {
        this->operator*(value);
        return *this;
    }

    Matrix& operator*(const Matrix& matrix)
    {
        if (this->cols == matrix.rows)
        {
            Matrix* mtx = new Matrix{};
            mtx->InitZero(this->rows, matrix.cols);

            for (auto r = 0; r < this->rows; r++)
                for (auto c = 0; c < matrix.cols; c++)
                    for (auto k = 0; k < this->cols; k++)
                        mtx->matrix[r][c] += this->matrix[r][k] * matrix.matrix[k][c];

            return *mtx;
        }
    }

    void AddRow(std::initializer_list<T> row)
    {
        if (this->cols == row.size() || this->cols == 0)
        {
            this->rows++;
            this->cols = row.size();
            this->matrix.push_back(row);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
    {
        matrix.Print();
        return os;
    }

    Matrix()
    {
        this->cols = 0;
        this->rows = 0;
    }

    void Print() const
    {
        for (const auto& row : this->matrix)
        {
            for (const auto& value : row)
                std::cout << value << " ";

            std::cout << std::endl;
        }
    }
};

#endif