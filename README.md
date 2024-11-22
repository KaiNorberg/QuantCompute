
# QuantCompute ![](https://img.shields.io/badge/license-MIT-blue)

A quantum computer simulation written in C++ programmable using quantum circuit diagrams.

## Setup

<ins>**1. Cloning (downloading)**</ins>

To clone (download) this repository, you can use the ```Code``` button at the top left of the screen, or use the following command if you have git installed ```git clone --recursive https://github.com/KaiNorberg/QuantCompute```.

<ins>**2. Building**</ins>

You will need to have xmake installed on your machine, if you do not have xmake installed you can install it from [here](https://xmake.io/#/).

With xmake installed, run the ```xmake``` command. You can then use ```xmake run```.

## How does it work? (WIP)

Note that I currently lack a formal education in quantum physics, so please take everything with a grain of salt.

In a quantum computer information is stored using qubits which are usually represented using Dirac notation, for example $|0\rangle$ or $|1\rangle$ however when programming this notation is not particularly useful. So instead, I will use a more traditional vector notation. 

### One qubit

You may know that a normal bit can be either 0 or 1, in the same way a qubit can be one of the following complex vectors either
```math 
\begin{pmatrix} 1 \\ 0 \end{pmatrix} \text{or} \begin{pmatrix} 0 \\ 1 \end{pmatrix}.
```
These particular qubits are what's called the basis states, however most of the time qubits will exist as a superposition of these two basis states, which can be represented as a linear combination of the two basis states. Note however that those qubits aren't "real" when measured the qubit will collapse into one of the two basis states, instead the linear combination merely represents the probability for the qubit to be in one state or the other.

### Many qubits

Usually, we want to have multiple qubits, the most convenient way of doing that is by combining the qubits into a single complex vector. We can do that by taking the tensor product of all the qubits, for example if we took the tensor product of the two basis states from previously, we would get 
```math 
\begin{pmatrix} 1 \\ 0 \end{pmatrix} \otimes \begin{pmatrix} 0 \\ 1 \end{pmatrix}= \begin{pmatrix} 0 \\ 1 \\ 0 \\ 0 \end{pmatrix}.
```
If we wanted to add more qubits we would just keep taking the tensor product of the result and some other qubit. If you kept doing that you would find that  the length of this vector grows exponentially with the amount of qubits, specifically the length of the vector is $2^n$ where n is the amount of qubits.

This vector made up of all the qubits can be thought of as the state of the quantum computer. The Quant::State class works by storing the qubits as described as a single complex vector. When you create an instance of the Quant::State class you provide a string for example "01", which means you want two qubit system, the first represented by 0 which is
```math 
\begin{pmatrix} 1 \\ 0 \end{pmatrix}
```
and another represented by 1 which is
```math 
\begin{pmatrix} 0 \\ 1 \end{pmatrix}.
```
If you know Dirac notation you may be able to notice that this string system is a highly simplified Dirac notation with the symbols removed. You may also note that system "01" is the system used in the tensor product example.

### Doing stuff

Quantum computers usually work via what's called a quantum circuit, these circuits can be thought of as the programs being executed by the quantum computer, and just like a normal program they modify the state of the computer which as mentioned previously is the qubits. In our case, a circuit can be represented by a complex matrix with dimensions $2^n \times 2^n$, and executing a circuit is as simple as multiplying the state with the circuit. This results in a new state which can later be measured. Creating a circuit is done by multiplying together what's called gates, which are also complex matrices. Gates can be thought of as the actually instructions of a quantum computer, just like if statements or addition in a normal computer. A list of these gates can be found [here](https://en.wikipedia.org/wiki/Quantum_logic_gate).


