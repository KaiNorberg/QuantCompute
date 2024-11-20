#pragma once

#include <complex>
#include <vector>
#include <stdint.h>

namespace Quant
{
    // Implement own complex implementation?
    typedef std::complex<double> Complex;

    class ComplexVector
    {
    public:
    
        uint64_t Length() const { return this->vector.size(); }

        void TensorMultiply(const ComplexVector& other);

        Complex& operator[](uint64_t index) { return this->vector[index]; }

        void Dump();

        ComplexVector();
        ComplexVector(uint64_t length, Complex value);
        ComplexVector(std::initializer_list<Complex> initList);
    private:
        std::vector<Complex> vector;
    };

    class ComplexMatrix
    {
    public:
    
        static ComplexMatrix Identity(uint64_t n);

        uint64_t Rows() const { return this->matrix.size(); }
        uint64_t Columns() const { return this->matrix[0].size(); }

        void KroneckerMultiply(const ComplexMatrix& other);

        ComplexMatrix& operator*=(const ComplexMatrix& other);
        std::vector<Complex>& operator[](uint64_t index) { return this->matrix[index]; }
        const std::vector<Complex>& operator[](uint64_t index) const { return this->matrix[index]; }

        void Dump();

        ComplexMatrix();
        ComplexMatrix(std::initializer_list<std::initializer_list<Complex>> initList);
    private:
        std::vector<std::vector<Complex>> matrix;
    };
}