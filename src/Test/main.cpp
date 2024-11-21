#include <Quant/Quant.hpp>

#include <iostream>

void deutsch_algorithm()
{
    Q::State state("01");
    state.dump();

    Q::Circuit circuit(2);
    circuit.apply(Q::Gate::Hadamard);
    // Oracle matrix representing f(x) = 0
    circuit.apply({
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    });
    circuit.apply(Q::Gate::Hadamard, 0);

    state.apply(circuit);
    state.dump();

    uint64_t result = state.measure(0);
    if (result == 0)
    {
        std::cout << "Function is constant.\n";
    }
    else if (result == 1)
    {
        std::cout << "Function is balanced.\n";
    }
    else 
    {
        std::cout << "Measurement does not make sense.\n";
    }
}

int main(char** argv, int argc)
{
    deutsch_algorithm();

    return 0;
}