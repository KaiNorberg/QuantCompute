#include "State.hpp"

#include <stdexcept>

uint64_t Quant::State::QubitAmount()
{
    return this->qubitAmount;
}

uint64_t Quant::State::VectorLength()
{
    return this->vector.size();
}

Quant::State::State(const std::string& dirac)
{
    
}