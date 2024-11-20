#pragma once

#include "Complex.hpp"

#include <stdint.h>

namespace Quant
{
    class State;

    enum Gate
    {
        Hadamard,
        MAX
    };

    class Circuit
    {
    public:

        // Apply gates that effect qubits individually
        void Apply(Gate gate);
        void Apply(Gate gate, uint64_t qubit);
        void Apply(Gate gate, uint64_t begin, uint64_t end);
        void Apply(Gate gate, const std::vector<uint64_t>& qubits);

        // Takes in custom gate matrix
        void Matrix(const ComplexMatrix& matrix);

        void Dump();

        Circuit(uint64_t qubitAmount);
    private:
        friend class State;

        static const ComplexMatrix& GetIndividualGate(Gate gate);

        uint64_t qubitAmount;
        ComplexMatrix matrix;
    };
}