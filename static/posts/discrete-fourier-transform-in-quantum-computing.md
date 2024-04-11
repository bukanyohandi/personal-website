---
title: "[Tutorial] Discrete Fourier Transform in Quantum Computing"
date: "2024-03-09"
author: "Yohandi"
tags: [algorithm, polynomial, quantum-computing, tutorial]
---

Discrete Fourier Transform (DFT) is a specific kind of Fourier Transform usually used in signal processing and data analysis, though it is also used to compute polynomial multiplication in computer science. DFT is applied to discrete, sampled data, rather than a continuous signal. The discrete part of its name reflects that the algorithm is designed for sequences of values at discrete intervals.

Before proceeding to read this post, the followings are few basic variables and operations in quantum computing that will be used for this post:
- A qubit is represented by vectors.
  - Basic states cover $| 0 \rangle = \begin{pmatrix} 1 \\ 0 \end{pmatrix}$ and $| 1 \rangle = \begin{pmatrix} 0 \\ 1 \end{pmatrix}$, which classically are considered as 0 and 1, respectively.
  - Superposition state, $| \psi \rangle$, represents a general quantum state, which is a superposition of the basis states. In a linear combination, $| \psi \rangle = \alpha | 0 \rangle + \beta | 1 \rangle$, where $\alpha$ and $\beta$ are complex numbers that satisfy $| \alpha |^2 + | \beta |^2 = 1$.
- The quantum bit operations that are used include Pauli-X gate, Hadamard gate, and Controlled phase gate.
  - Pauli-X gate, which is represented as $X = \begin{pmatrix} 0 & 1 \\ 1 & 0 \end{pmatrix}$, corresponds to a NOT gate in a classical bit inversion. The gate operates as follows: $X | 0 \rangle = | 1 \rangle$ and $X | 1 \rangle = | 0 \rangle$.
  - Hadamard gate, which is represented as $H = \frac{1}{\sqrt{2}} \begin{pmatrix} 1 & 1 \\ 1 & -1 \end{pmatrix}$. It creates superposition states from the basic states: $H | 0 \rangle = \frac{| 0 \rangle + | 1 \rangle}{2}$ and $H | 1 \rangle = \frac{| 0 \rangle - | 1 \rangle}{2}$. If we apply hadamard to $| \psi \rangle$, we get $H | \psi \rangle = \frac{\alpha + \beta}{\sqrt{2}} | 0 \rangle + \frac{\alpha - \beta}{\sqrt{2}} | 1 \rangle$.
  - Controlled phase gate, which controls the phase rotation, is represented as $CR_z(\theta) = \begin{pmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & e^{i \theta} \end{pmatrix}$. The first three diagonal elements are 1, implying that when the control qubit is in the $| 0 \rangle$ state, or $| 1 \rangle$ state but targeting $| 0 \rangle$, the gate does not change the state of the system. The last element implies a phase shift of $\theta$ when the control qubit is in the $| 1 \rangle$ state. 

### Discrete Fourier Transform

Discrete Fourier Transform transforms a sequence of complex numbers, say $a_0, a_1, \ldots, a_{N - 1}$, into another sequence of complex numbers, say $A_0, A_1, \ldots, A_{N - 1}$, where $A$ is defined as:

$$
\begin{align*}
A &= \begin{pmatrix} A_0 \\ A_1 \\ A_2 \\ \vdots \\ A_{N - 1} \end{pmatrix} \\ &= \begin{pmatrix} \omega^{0} & \omega^{0} & \omega^{0} & \cdots & \omega^{0} \\ \omega^{0} & \omega^{1} & \omega^{2} & \cdots & \omega^{(N - 1)} \\ \omega^{0} & \omega^{2} & \omega^{4} & \cdots & \omega^{2(N - 1)} \\ \vdots & \vdots & \vdots & \ddots & \vdots \\ \omega^{0} & \omega^{(N - 1)} & \omega^{2(N - 1)} & \cdots & \omega^{\ (N - 1)(N - 1)} \\ \end{pmatrix} \begin{pmatrix} a_0 \\ a_1 \\ a_2 \\ \vdots \\ a_{N - 1} \end{pmatrix}
\end{align*}
$$

, where $\omega = e^{-\frac{2 \pi}{N} i}$. This implies that the $j$-th element of $A$ is:

$$
\begin{align*}
A_j = \sum_{k = 0}^{N - 1} e^{-\frac{2 \pi}{N} i (j \cdot k)} a_k, \forall j \in \{0, 1, \ldots, N - 1\}
\end{align*}
$$

By computing the matrix multiplication, $A$ can be simply obtained through an $\mathcal{O}(N^2)$ näive implementation.

### Fast Fourier Transform

Currently, Fast Fourier Transform stands as the quickest classical algorithm that converts the same sequence of $a$ into $A$ in $\mathcal{O}(N \log N)$ performance. Let $P(x)$ be a polynomial function, the algorithm exploits the fact that:
- $P(x) = P_1(x^2) + x P_2(x^2)$
- $P(-x) = P_1(x^2) - x P_2(x^2)$

, where $P_1(x)$ is the polynomial containing all the terms of $P(x)$ with even powers, and $P_2(x)$ contains all the terms of $P(x)$ with odd powers. As it is possible to reconstruct $P(x)$ given $x_0, x_1, \ldots, x_{N - 1}$ such that $x_i \neq x_j, \forall i \neq j$ and $i, j \in \{0, 1, \ldots, N - 1\}$, the objective of the algorithm is simply to find $P(x_0), P(x_1), \ldots, P(x_{N - 1})$ for any configuration of $x$. Setting up $x$ as $\{1, \omega, \omega^2, \ldots, \omega^{(N - 1)}\}$ allows divide-and-conquer approach to be used (due to symmetry) for efficient evaluation of $P(x)$ by $P_1(x^2)$ and $P_2(x^2)$. This method yields the FFT's hallmark performance:

$$
\begin{align*}
T(N) &= 2T(\frac{N}{2}) + \mathcal{O}(N) \\
&= \mathcal{O}(N \log N) \text{ \ \ (by Master's Theorem)} \\
\end{align*}
$$ 

is obtained.

### Discrete Fourier Transform in Quantum Computing

With the same objective, the Quantum Fourier Transform (QFT) converts $| a \rangle = \sum_{j = 0}^{n - 1} a_j | j \rangle$ into $| A \rangle = \sum_{j = 0}^{n - 1} A_j | j \rangle$, where:

$$
\begin{align*}
A_j = \frac{1}{\sqrt{n}} \sum_{k = 0}^{n - 1} e^{\frac{2 \pi}{n} i(j \cdot k)} a_k, \forall j = \{0, 1, \ldots, n - 1\}
\end{align*}
$$

Notice that the $| A \rangle$ is expressed and rewrittable as:

$$
\begin{align*}
| A \rangle &= \frac{1}{\sqrt{n}} \sum_{k = 0}^{n - 1} e^{\frac{2 \pi}{n} i k \sum_{j=0}^{n-1}2^j a_j} | k \rangle \\
&= \frac{1}{\sqrt{n}} \left( | 0 \rangle + e^{\frac{2 \pi i}{n} a} | 1 \rangle + e^{\frac{4 \pi i}{n} a} | 2 \rangle + \cdots + e^{\frac{2 (n - 1) \pi i}{n} a} | (n - 1) \rangle \right) \\
&= \frac{1}{\sqrt{n}} \bigotimes_{k = 0}^{n - 1} (| 0 \rangle + e^{\frac{2 \pi}{n} i(a 2^{n - k - 1})} | 1 \rangle) \\
&= \frac{1}{\sqrt{n}} \bigotimes_{k = 0}^{n - 1} (| 0 \rangle + e^{2 \pi i[0.a_{n - k - 1} \ldots a_{n - 1}]} | 1 \rangle) \\
\end{align*}
$$

, where $[0.a_{n - k - 1} \ldots a_{n - 1}]$ is a binary fraction representation. This expression showcases the algorithm's potential to encode phase information across a superposition of all computational basis states.

The action of the Hadamard gate produces superpositions necessity for the algorithm's operation:

$$
H | a_j \rangle = \frac{1}{\sqrt{2}} (| 0 \rangle + e^{2 \pi i a_j} | 1 \rangle),
$$

. Each step in the algorithm, reliant on superposition and entanglement, achieves the quantum analogue of the classical Discrete Fourier Transform efficiently.


```py
from qiskit import QuantumCircuit, Aer, execute, transpile
from qiskit.visualization import plot_histogram

import math
import matplotlib.pyplot as plt
import numpy as np

def dft(N, arr):
    n = math.ceil(math.log2(N))

    qc = QuantumCircuit(n, n)
    
    norm_arr = np.array(arr) / np.linalg.norm(arr)
    for i, amp in enumerate(norm_arr):
        if amp > 0:
            qc.x(i % n)

    def apply_qft(circuit, n):
        for j in range(n):
            circuit.h(j)
            
            for k in range(j + 1, n):
                circuit.cp(np.pi / 2 ** (k - j), j, k)

        for k in range(n // 2):
            circuit.swap(j, n - k - 1)

    apply_qft(qc, n)

    for i in range(n):
        qc.measure(i, i)

    simulator = Aer.get_backend('aer_simulator')
    counts = simulator.run(transpile(qc, simulator)).result().get_counts()

    print("Quantum Circuit:")
    print(qc.draw())

    print("Measurement Results:")
    plot_histogram(counts)
    plt.show()
```

The `apply_qft` function runs in $\mathcal{O}(n^2)$, where $n$ is the number of qubits. To represent an array of $N$ elements in a quantum computer, $\log_2(N)$ number of qubits are needed. As a result, the overall performance of `apply_qft` is $\mathcal{O}(\log^2(N))$. This highlights a significant reduction in computational resources compared to classical methods. Currently, the fastest known quantum algorithm for Discrete Fourier Transform achieves about $\mathcal{O}(\log(N) \log(\log(N)))$ performance.

### Importance of Discrete Fourier Transform in Quantum Computing

The QFT algorithm exemplifies the leap between classical computing to quantum computing. One of the most notable applications of QFT include Shor's algorithm, which is an algorithm that finds the prime factors of an integer. Compared to the most efficient classical factoring algorithm that runs in $\mathcal{O}(e^{1.9 \log^{1/3}(N) \log^{2/3}(\log(N))})$, Shor's algorithm runs in $\mathcal{O}(\log^2(N) \log(\log(N)) \log(\log(\log(N))))$. That is significantly faster!

Beyond the acceleration, QFT highlights the unique capabilities of quantum systems to encode and manipulate information in ways that classical systems cannot replicate. This opens up avenues for complex system optimizations!

### References

1. **Nielsen, M.**, "Quantum Computation and Quantum Information," Cambridge University Press. https://www.worldcat.org/oclc/174527496.
