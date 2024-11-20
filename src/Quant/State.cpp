#include "State.hpp"

#include <stdexcept>
#include <iostream>

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

}

void Quant::State::Measure(uint64_t targetQubit)
{
    
}

void Quant::State::Dump()
{
    std::cout << "[";
    for (uint64_t i = 0; i < this->vector.Length(); i++)
    {
        std::cout << this->vector[i];
        if (i != this->vector.Length() - 1)
        {
            std::cout << " ";
        }
    }

    std::cout << "]\n";
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