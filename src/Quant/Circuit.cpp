#include "Circuit.hpp"

#include <iostream>

void Quant::Circuit::Hadamard(uint64_t targetQubit)
{
    static double inverseSqrt2 = 1.0/(sqrt(2));
    static ComplexMatrix hadamard = {{inverseSqrt2, inverseSqrt2}, {inverseSqrt2, -inverseSqrt2}};
    static ComplexMatrix identity = {{1,0}, {0,1}};

    ComplexMatrix result;
    if (0 == targetQubit)
    {
        result = hadamard;
    }
    else
    {
        result = identity;
    }

    for (uint64_t i = 1; i < this->qubitAmount; i++)
    {
        if (i == targetQubit)
        {
            result.KroneckerMultiply(hadamard);
        }
        else
        {
            result.KroneckerMultiply(identity);
        }
    }

    //result.Dump();
    this->matrix *= result;
}

void Quant::Circuit::Dump()
{    
    this->matrix.Dump();
}

Quant::Circuit::Circuit(uint64_t qubitAmount)
{
    this->qubitAmount = qubitAmount;
    
    uint64_t n = 1 << this->qubitAmount;
    this->matrix = ComplexMatrix::Identity(n);
}
