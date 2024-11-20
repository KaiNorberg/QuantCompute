#include <Quant/Quant.hpp>

uint64_t DeutschAlgorithm(bool isBalanced)
{
    Q::State state("|0>|1>");

    Q::Circuit circuit(
        Q::HadamardGate(2),
        Q::Oracle(),
        Q::HadamardGate(2)
    );

    state.Apply(circuit);

    state.Measure();
}

int main(char** argv, int argc)
{
    Q::State state("|0>|1>");


    return 0;
}