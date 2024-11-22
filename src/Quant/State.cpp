#include "State.hpp"

#include <stdexcept>
#include <complex>
#include <iostream>
#include <random>

uint64_t Quant::State::qubit_amount()
{
    return this->m_qubitAmount;
}

void Quant::State::normalize() 
{
    this->m_vector = blaze::normalize(this->m_vector);
}

void Quant::State::apply(const Circuit& circuit)
{    
    uint64_t n = circuit.rows();
    if (n != circuit.columns() || n != this->m_vector.size()) 
    {
        throw std::invalid_argument("Matrix and vector dimensions do not match.");
    }

    this->m_vector *= circuit.matrix();
}

Quant::Measurement Quant::State::measure(uint64_t qubit)
{
    std::vector<double> probabilities(1 << this->m_qubitAmount, 0.0);

    for (uint64_t i = 0; i < this->m_vector.size(); ++i) 
    {
        int qubitValue = (i >> (this->m_qubitAmount - qubit - 1)) & 1;
        probabilities[qubitValue] += std::norm(this->m_vector[i]);
    }

    uint8_t result = 0;
    double maxProbability = probabilities[0];
    for (uint64_t i = 1; i < probabilities.size(); ++i) 
    {
        if (probabilities[i] > maxProbability) 
        {
            result = i;
            maxProbability = probabilities[i];
        }
    }

    return {qubit, result, maxProbability};
}

void Quant::State::dump()
{
    std::cout << "[";
    for (uint64_t i = 0; i < this->m_vector.size(); ++i) 
    {
        std::cout << this->m_vector[i];
        if (i != this->m_vector.size() - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

Quant::State::State(const std::string& string)
{
    // |0> = [1, 0], |1> = [0, 1]
    static std::vector<StateVector> basisStates = {{1, 0}, {0, 1}};

    if (string.empty() || (string[0] != '0' && string[0] != '1'))
    {
        throw std::invalid_argument("Invalid state string");
    }

    this->m_qubitAmount = string.length();
    this->m_vector = basisStates[string[0] - '0'];
    for (uint64_t i = 1; i < string.length(); i++)
    {
        if (string[i] != '0' && string[i] != '1')
        {
            throw std::invalid_argument("Invalid state string");
        }

        this->m_vector = blaze::kron(this->m_vector, basisStates[string[i] - '0']);
    }
}