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

    StateVector result(n, std::complex<double>(0.0, 0.0));
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            result[i] += circuit.element(i, j) * this->m_vector[j];
        }
    }

    this->m_vector = result;
}

uint64_t Quant::State::measure(uint64_t qubit)
{
    uint64_t mask = 1 << qubit;
    double probZero = 0.0;

    for (uint64_t i = 0; i < this->m_vector.size(); ++i) 
    {
        if ((i & mask) == 0) 
        {
            probZero += std::norm(this->m_vector[i]);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    double randomValue = dis(gen);

    bool result = randomValue > probZero;

    for (uint64_t i = 0; i < this->m_vector.size(); ++i) 
    {
        if (((i & mask) == 0) != result) 
        {
            this->m_vector[i] = {0.0, 0.0};
        }
    }
    this->normalize();

    return result;
}

void Quant::State::dump()
{
    std::cout << "[";
    for (size_t i = 0; i < this->m_vector.size(); ++i) 
    {
        std::cout << this->m_vector[i] << " ";
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