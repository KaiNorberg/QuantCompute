#include "Complex.hpp"

#include <iostream>

void Quant::ComplexVector::TensorMultiply(const ComplexVector& other)
{
    std::vector<Complex> result;
    for (const Complex& elemA : this->vector) 
    {
        for (const Complex& elemB : other.vector) 
        {
            result.push_back(elemA * elemB);
        }
    }
    this->vector = result;
}

void Quant::ComplexVector::Dump()
{
    std::cout << "[";
    for (uint64_t i = 0; i < this->vector.size(); i++)
    {
        std::cout << this->vector[i];
        if (i != this->vector.size() - 1)
        {
            std::cout << " ";
        }
    }

    std::cout << "]\n";
}

Quant::ComplexVector::ComplexVector()
{
    this->vector.clear();
}

Quant::ComplexVector::ComplexVector(uint64_t length, Complex value)
{
    this->vector = std::vector<Complex>(length, value);
}

Quant::ComplexVector::ComplexVector(std::initializer_list<Complex> initList)
{
    this->vector = initList;
}

/////////////////////////////////////////////////////////////////////////////////

Quant::ComplexMatrix Quant::ComplexMatrix::Identity(uint64_t n)
{
    // Initialize an n x n matrix with zeros
    ComplexMatrix matrix;
    matrix.matrix = std::vector<std::vector<Complex>>(n, std::vector<Complex>(n, 0.0));

    for (uint64_t i = 0; i < n; i++) 
    {
        matrix.matrix[i][i] = 1.0;
    }

    return matrix;
}

void Quant::ComplexMatrix::KroneckerMultiply(const ComplexMatrix& other) 
{
    uint64_t m = this->matrix.size();
    uint64_t n = this->matrix[0].size();
    uint64_t p = other.matrix.size();
    uint64_t q = other.matrix[0].size();
    
    std::vector<std::vector<Complex>> result(m * p, std::vector<Complex>(n * q, 0));

    for (uint64_t i = 0; i < m; ++i) 
    {
        for (uint64_t j = 0; j < n; ++j) 
        {
            for (uint64_t k = 0; k < p; ++k) 
            {
                for (uint64_t l = 0; l < q; ++l) 
                {
                    result[i * p + k][j * q + l] = this->matrix[i][j] * other.matrix[k][l];
                }
            }
        }
    }
    
    this->matrix = result;
}

Quant::ComplexMatrix& Quant::ComplexMatrix::operator*=(const ComplexMatrix& other)
{
    int rowsA = this->matrix.size();
    int colsA = this->matrix[0].size();
    int rowsB = other.matrix.size();
    int colsB = other.matrix[0].size();

    if (colsA != rowsB) 
    {
        throw std::invalid_argument("Matrix dimensions do not allow multiplication");
    }

    std::vector<std::vector<Complex>> result(rowsA, std::vector<Complex>(colsB, 0.0));

    for (int i = 0; i < rowsA; i++) 
    {
        for (int j = 0; j < colsB; j++) 
        {
            for (int k = 0; k < colsA; k++) 
            {
                result[i][j] += this->matrix[i][k] * other.matrix[k][j];
            }
        }
    }

    this->matrix = result;
    return *this;
}

void Quant::ComplexMatrix::Dump()
{    
    for (uint64_t i = 0; i < this->matrix.size(); i++)
    {
        std::cout << "|";
        for (uint64_t j = 0; j < this->matrix[0].size(); j++)
        {
            std::cout << this->matrix[i][j];
            if (j != this->matrix[0].size() - 1)
            {
                std::cout << " ";
            }
        }

        std::cout << "|\n";
    }
}

Quant::ComplexMatrix::ComplexMatrix()
{
    this->matrix.clear();
}

Quant::ComplexMatrix::ComplexMatrix(std::initializer_list<std::initializer_list<Complex>> initList)
{
    this->matrix.clear();
    for (const auto& row : initList) 
    {
        this->matrix.push_back(row);
    }
}
