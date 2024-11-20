#include <Quant/Quant.hpp>

#include <iostream>

void DeutschAlgorithm()
{
    Q::State state("01");
    state.Dump();

    Q::Circuit circuit(2);
    circuit.Apply(Q::Gate::Hadamard);
    // Oracle matrix representing f(x) = 0
    circuit.Matrix({
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    });
    circuit.Apply(Q::Gate::Hadamard, 0);

    state.Apply(circuit);
    state.Dump();

    uint64_t result = state.Measure(0);
    if (result == 0)
    {
        std::cout << "Function is constant\n";
    }
    else if (result == 1)
    {
        std::cout << "Function is balanced\n";
    }
    else 
    {
        std::cout << "Measurement does not make sense\n";
    }
}

int main(char** argv, int argc)
{
    DeutschAlgorithm();

    return 0;
}