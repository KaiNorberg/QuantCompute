#include "Complex.hpp"

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
    return *this;
}

Quant::ComplexVector::ComplexVector()
{
    this->vector.clear();
}

Quant::ComplexVector::ComplexVector(std::initializer_list<Complex> initList)
{
    this->vector = initList;
}
