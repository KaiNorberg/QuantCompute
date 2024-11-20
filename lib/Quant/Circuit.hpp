#pragma once

#include "Gate.hpp"

#include <stdint.h>

namespace Quant
{
    class Circuit
    {
    public:
        void Hadamard(uint64_t targetQubit);

        Circuit(uint64_t qubitAmount);
    private:
        uint64_t qubitAmount;
        std::vector<std::vector<Complex>> matrix;
    };
}