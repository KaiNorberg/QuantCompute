#pragma once

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

        void Normalize(); 

        void Apply(const Circuit& circuit);
        uint64_t Measure(uint64_t qubit);

        void Dump();

        State(const std::string& string);
    private:
        uint64_t qubitAmount;
        ComplexVector vector; 
    };
}