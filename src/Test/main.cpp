#include <Quant/Quant.hpp>

void DeutschAlgorithm()
{
    Q::State state("01");
    state.Dump();

    Q::Circuit circuit(2);
    circuit.Apply(Q::Gate::Hadamard);
    circuit.Dump();

    // Oracle matrix representing f(x) = 1
    circuit.Matrix({
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0}
    });

    circuit.Apply(Q::Gate::Hadamard);

    state.Apply(circuit);
    state.Dump();

    //Q::Result result = state.Measure(0);
}

int main(char** argv, int argc)
{
    DeutschAlgorithm();


    return 0;
}