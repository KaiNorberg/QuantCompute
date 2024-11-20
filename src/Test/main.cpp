#include <Quant/Quant.hpp>

void DeutschAlgorithm(bool isBalanced)
{
    Q::State state("01");
    state.Dump();

    Q::Circuit circuit(2);
    circuit.Hadamard(0);
    circuit.Hadamard(1);
    //circuit.Oracle(isBalanced);
    //circuit.Hadamard(0);

    state.Apply(circuit);
    state.Dump();

    state.Measure(0);
}

int main(char** argv, int argc)
{
    DeutschAlgorithm(true);


    return 0;
}