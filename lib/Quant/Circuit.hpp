#pragma once

#include "Gate.hpp"
#include "Complex.hpp"

#include <stdint.h>

namespace Quant
{
    class State;

    class Circuit
    {
    public:
        void Hadamard(uint64_t targetQubit);

        void Dump();

        Circuit(uint64_t qubitAmount);
    private:
        friend class State;

        uint64_t qubitAmount;
        ComplexMatrix matrix;
    };
}