#include <Quant/Quant.hpp>

#include <iostream>

void deutsch_algorithm()
{
    Q::State state("01");

    Q::Circuit circuit(2);
    circuit.apply(Q::Gate::Hadamard);
    // Oracle matrix representing f(x) = x
    circuit.apply({
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0}
    });
    circuit.apply(Q::Gate::Hadamard, 0);

    state.apply(circuit);

    Q::Measurement result = state.measure(0);
    if (result.result == 0)
    {
        std::cout << "Function is constant";
    }
    else if (result.result == 1)
    {
        std::cout << "Function is balanced";
    }
    std::cout << " with a " << result.probability * 100 << "% likelihood.\n";
}

int main(char** argv, int argc)
{
    deutsch_algorithm();

    return 0;
}