#pragma once

#include "Gate.hpp"
#include "Complex.hpp"

#include <vector>
#include <stdint.h>

namespace Quant
{
    typedef std::complex<double> Complex;

    class State
    {
    public:
        uint64_t QubitAmount();
        uint64_t VectorLength();

        void Apply(const Gate& gate);

        // Takes in dirac notation for example |0>|1>.
        State(const std::string& dirac);
    private:
        uint64_t qubitAmount;

        // A 2^(qubitAmount) dimensional vector of complex numbers.
        std::vector<Complex> vector; 
    };
}