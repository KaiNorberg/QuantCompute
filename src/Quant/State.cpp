#include "State.hpp"

#include <stdexcept>
#include <complex>
#include <random>

uint64_t Quant::State::QubitAmount()
{
    return this->qubitAmount;
}

uint64_t Quant::State::VectorLength()
{
    return this->vector.Length();
}

void Quant::State::Normalize() 
{
    double norm = 0.0;
    for (uint64_t i = 0; i < this->vector.Length(); i++) 
    {
        norm += std::norm(this->vector[i]);
    }
    
    norm = std::sqrt(norm);
    for (uint64_t i = 0; i < this->vector.Length(); i++) 
    {
        this->vector[i] /= norm;
    }
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

uint64_t Quant::State::Measure(uint64_t qubit)
{
    uint64_t mask = 1 << qubit;
    double probZero = 0.0;

    for (uint64_t i = 0; i < this->vector.Length(); ++i) 
    {
        if ((i & mask) == 0) 
        {
            probZero += std::norm(this->vector[i]);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    double randomValue = dis(gen);

    bool result = randomValue > probZero;

    for (uint64_t i = 0; i < this->vector.Length(); ++i) 
    {
        if (((i & mask) == 0) != result) 
        {
            this->vector[i] = {0.0, 0.0};
        }
    }
    this->Normalize();

    return result;
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