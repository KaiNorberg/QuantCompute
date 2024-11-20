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

        uint64_t Length() { return this->vector.size(); }

        void TensorMultiply(const ComplexVector& other);

        Complex& operator[](uint64_t index) { return this->vector[index]; }

        ComplexVector();
        ComplexVector(std::initializer_list<Complex> initList);

    private:
        std::vector<Complex> vector;
    };
}