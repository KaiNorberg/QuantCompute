#pragma once

#include "Circuit.hpp"

#include <vector>
#include <stdint.h>

#include <blaze/Math.h>

namespace Quant
{
    using StateVector = blaze::DynamicVector<std::complex<double>>;

    struct Measurement
    {
        uint64_t qubit;
        uint8_t result;
        double probability;
    };

    class State
    {
    public:
        uint64_t qubit_amount();

        void normalize(); 
        void apply(const Circuit& circuit);
        Measurement measure(uint64_t qubit);

        void dump();

        State(const std::string& string);
    private:
        uint64_t m_qubitAmount;
        StateVector m_vector; 
    };
}