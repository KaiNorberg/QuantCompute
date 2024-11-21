#include "Circuit.hpp"

#include <iostream>
#include <algorithm>
#include <stdexcept>

static Quant::CircuitMatrix identity2x2 = {{1,0}, {0,1}};

void Quant::Circuit::apply(Gate gate)
{
    const CircuitMatrix& gateMatrix = getIndividualGate(gate);
    CircuitMatrix result = {{1}};

    for (uint64_t i = 0; i < this->m_qubitAmount; i++)
    {
        result = blaze::kron(result, gateMatrix);
    }

    this->m_matrix *= result;
}

void Quant::Circuit::apply(Gate gate, uint64_t qubit)
{
    const CircuitMatrix& gateMatrix = getIndividualGate(gate);
    CircuitMatrix result = {{1}};
    
    for (uint64_t i = 0; i < this->m_qubitAmount; i++)
    {
        if (i == qubit)
        {
            result = blaze::kron(result, gateMatrix);
        }
        else
        {
            result = blaze::kron(result, identity2x2);
        }
    }

    this->m_matrix *= result;
}

void Quant::Circuit::apply(Gate gate, uint64_t begin, uint64_t end)
{
    const CircuitMatrix& gateMatrix = getIndividualGate(gate);
    CircuitMatrix result = {{1}};
    
    for (uint64_t i = 0; i < this->m_qubitAmount; i++)
    {
        if (begin <= i && i < end)
        {
            result = blaze::kron(result, gateMatrix);
        }
        else
        {
            result = blaze::kron(result, identity2x2);
        }
    }

    this->m_matrix *= result;
}

void Quant::Circuit::apply(Gate gate, const std::vector<uint64_t>& qubits)
{
    const CircuitMatrix& gateMatrix = getIndividualGate(gate);
    CircuitMatrix result = {{1}};
    
    for (uint64_t i = 0; i < this->m_qubitAmount; i++)
    {
        if (std::find(qubits.begin(), qubits.end(), i) != qubits.end())
        {
            result = blaze::kron(result, gateMatrix);
        }
        else
        {
            result = blaze::kron(result, identity2x2);
        }
    }

    this->m_matrix *= result;
}

void Quant::Circuit::apply(const CircuitMatrix& matrix)
{
    this->m_matrix *= matrix;
}

void Quant::Circuit::dump()
{    
    for (uint64_t i = 0; i < this->m_matrix.rows(); ++i) 
    {
        std::cout << "|";
        for (uint64_t j = 0; j < this->m_matrix.columns(); ++j) 
        {
            std::cout << this->m_matrix(i, j) << " ";
        }
        std::cout << "|\n";
    }
    std::cout << std::endl;
}

Quant::Circuit::Circuit(uint64_t m_qubitAmount)
{
    this->m_qubitAmount = m_qubitAmount;
    
    uint64_t n = 1 << this->m_qubitAmount;
    this->m_matrix = blaze::IdentityMatrix<std::complex<double>>(n);
}

const Quant::CircuitMatrix& Quant::Circuit::getIndividualGate(Gate gate)
{
    switch (Gate::Hadamard)
    {
    case Gate::Hadamard:
    {
        static CircuitMatrix hadamard =
        {
            {1.0/(sqrt(2)), 1.0/(sqrt(2))}, 
            {1.0/(sqrt(2)), -1.0/(sqrt(2))}
        };
        return hadamard;
    }
    break;
    }

    throw std::invalid_argument("Gate out of range");
}