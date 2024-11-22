#pragma once

#include <stdint.h>

#include <blaze/Math.h>

namespace Quant
{
    enum Gate
    {
        Hadamard,
        MAX
    };

    using CircuitMatrix = blaze::DynamicMatrix<std::complex<double>>;

    class Circuit
    {
    public:
        // Apply gates that effect qubits individually
        void apply(Gate gate);
        void apply(Gate gate, uint64_t qubit);
        void apply(Gate gate, uint64_t begin, uint64_t end);
        void apply(Gate gate, const std::vector<uint64_t>& qubits);

        // Takes in custom gate matrix
        void apply(const CircuitMatrix& matrix);

        uint64_t rows() const { return this->m_matrix.rows(); }
        uint64_t columns() const { return this->m_matrix.columns(); }
        const CircuitMatrix& matrix() const { return this->m_matrix; }

        void dump();

        Circuit(uint64_t qubitAmount);
    private:
        static const CircuitMatrix& getIndividualGate(Gate gate);

        uint64_t m_qubitAmount;
        CircuitMatrix m_matrix;
    };
}