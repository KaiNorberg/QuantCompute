#pragma once

#include "Gate.hpp"
#include "Complex.hpp"
#include "Circuit.hpp"

#include <vector>
#include <stdint.h>

namespace Quant
{
    class State
    {
    public:
        uint64_t QubitAmount();
        uint64_t VectorLength();

        void Apply(const Circuit& circuit);
        void Measure(uint64_t targetQubit);

        void Dump();

        State(const std::string& string);
    private:
        uint64_t qubitAmount;
        ComplexVector vector; 
    };
}