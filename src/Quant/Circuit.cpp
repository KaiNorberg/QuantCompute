#include "Circuit.hpp"

#include <iostream>
#include <algorithm>
#include <stdexcept>

static Quant::ComplexMatrix identity2x2 = {{1,0}, {0,1}};

void Quant::Circuit::Apply(Gate gate)
{
    ComplexMatrix gateMatrix = GetIndividualGate(gate);
    ComplexMatrix result = ComplexMatrix::Identity(1);

    for (uint64_t i = 0; i < this->qubitAmount; i++)
    {
        result.KroneckerMultiply(gateMatrix);
    }

    this->matrix *= result;
}

void Quant::Circuit::Apply(Gate gate, uint64_t qubit)
{
    ComplexMatrix gateMatrix = GetIndividualGate(gate);
    ComplexMatrix result = ComplexMatrix::Identity(1);
    
    for (uint64_t i = 0; i < this->qubitAmount; i++)
    {
        if (i == qubit)
        {
            result.KroneckerMultiply(gateMatrix);
        }
        else
        {
            result.KroneckerMultiply(identity2x2);
        }
    }

    this->matrix *= result;
}

void Quant::Circuit::Apply(Gate gate, uint64_t begin, uint64_t end)
{
    ComplexMatrix gateMatrix = GetIndividualGate(gate);
    ComplexMatrix result = ComplexMatrix::Identity(1);
    
    for (uint64_t i = 0; i < this->qubitAmount; i++)
    {
        if (begin <= i && i < end)
        {
            result.KroneckerMultiply(gateMatrix);
        }
        else
        {
            result.KroneckerMultiply(identity2x2);
        }
    }

    this->matrix *= result;
}

void Quant::Circuit::Apply(Gate gate, const std::vector<uint64_t>& qubits)
{
    ComplexMatrix gateMatrix = GetIndividualGate(gate);
    ComplexMatrix result = ComplexMatrix::Identity(1);
    
    for (uint64_t i = 0; i < this->qubitAmount; i++)
    {
        if (std::find(qubits.begin(), qubits.end(), i) != qubits.end())
        {
            result.KroneckerMultiply(gateMatrix);
        }
        else
        {
            result.KroneckerMultiply(identity2x2);
        }
    }

    this->matrix *= result;
}

void Quant::Circuit::Matrix(const ComplexMatrix &matrix)
{
    this->matrix *= matrix;
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

const Quant::ComplexMatrix& Quant::Circuit::GetIndividualGate(Gate gate)
{
    switch (Gate::Hadamard)
    {
    case Gate::Hadamard:
    {
        static ComplexMatrix hadamard =
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