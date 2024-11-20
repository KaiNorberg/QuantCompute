#include "State.hpp"

#include <stdexcept>

uint64_t Quant::State::QubitAmount()
{
    return this->qubitAmount;
}

uint64_t Quant::State::VectorLength()
{
    return this->vector.Length();
}

void Quant::State::Apply(const Circuit& circuit)
{
    if (circuit.matrix.Columns() != circuit.matrix.Rows()) 
    {
        throw std::invalid_argument("Matrix and vector dimensions do not match.");
    }
    uint64_t n = circuit.matrix.Columns();

    ComplexVector result(n, Complex(0.0, 0.0));
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            result[i] += circuit.matrix[i][j] * this->vector[j];
        }
    }

    this->vector = result;
}

void Quant::State::Measure(uint64_t targetQubit)
{
    
}

void Quant::State::Dump()
{
    this->vector.Dump();
}

Quant::State::State(const std::string& string)
{
    // |0> = [1, 0], |1> = [0, 1]
    static std::vector<ComplexVector> basisStates = {{1, 0}, {0, 1}};

    if (string.empty() || (string[0] != '0' && string[0] != '1'))
    {
        throw std::invalid_argument("Invalid state string");
    }

    this->qubitAmount = string.length();
    this->vector = basisStates[string[0] - '0'];
    for (uint64_t i = 1; i < string.length(); i++)
    {
        if (string[i] != '0' && string[i] != '1')
        {
            throw std::invalid_argument("Invalid state string");
        }

        this->vector.TensorMultiply(basisStates[string[i] - '0']);
    }
}