---
title: "Karp's Classics Challenge 1: Knapsack to Partition"
date: "2023-10-20"
author: "Yohandi"
tags: [algorithm, challenge]
---

In 1972, Richard Karp published a paper titled "Reducibility Among Combinatorial Problems," in which he demonstrated that 21 decision problems were NP-complete. What is fascinating is that, until this date, no one has conclusively proven whether these problems can be solved using a polynomial-time algorithm. In layman's terms: if one can find a polynomial-time solution to any of these problems, like the Boolean Satisfiability Problem (SAT), then a domino effect ensues, and all NP problems would collapse to being polynomial-time solvable. Conversely, disproving the polynomial-time solvability for one inherently disproves it for all.

*Post Script* - pretty much, this blog series is my proving exercises before my final exam for the postgraduate course that I took, DDA6050: Analysis of Algorithms, draws near. Through this series, I attempt to prove the NP-completeness of Karp's problems from the ground up without relying much on established proofs.

### Challenge Progress

![](/posts/figures/karps-challenge-knapsack-to-partition/progress.png)

### Knapsack (simplified)

Given:
- an integer $n$
- a set of non-negative integers $S = \{a_1, \ldots, a_n\}$
- an integer $K$

Task:
- Decide whether there is a subset $P \subseteq S$ such that $\sum_{a_i \in P} = K$

### Partition

Given:
- an integer $n$
- a set of non-negative integers $\{a_1, \ldots, a_n\}$

Task:
- Decide whether there is a subset $P \subseteq [1, n]$ such that $\sum_{i \in P} a_i = \sum_{i \notin P} a_i$

### Partition is NP

The question of whether the Partition problem lies within NP can be addressed by examining the verification process for a potential solution, which we'll call a certificate. For the Partition problem, this certificate is a subset $P$ drawn from the indices $[1, n]$ of the given set of integers.

To verify the certificate's correctness, we start by computing the sum of the integers that are indexed by $P$, which we denote as $\sum_{i \in P} a_i$. In parallel, we also determine the sum of the integers that aren't indexed by $P$, represented by $\sum_{i \notin P} a_i$. Our main criterion for correctness then hinges on a straightforward comparison: are these two sums equal? If they are, our algorithm acknowledges the validity of the Partition and returns `yes`. If not, it simply returns `no`.

In terms of computational efficiency, this verification process is quite tractable. Calculating both summations takes linear time, specifically $\mathcal{O}(n)$, and comparing them is a constant-time operation. Because the entire verification process is polynomial in $n$, we can confidently state that the Partition problem is NP.

### Partition is NP-hard by Knapsack

Let's consider a known NP-hard problem, Knapsack.

Given an instance of the simplified version of Knapsack problem with items $S = \{a_1, \ldots, a_n\}$ and an integer $K$, we then construct an instance of the Partition problem as follows:
- Compute $H$, which is half of the sum of the items in $S$, i.e., $H = \frac{1}{2} \sum_{a_i \in S} a_i$.
- Form a new set $\~S = S \cup \{2H + 2K, 4H\}$.

The result of this transformation is $\~S$, the goal is to find a subset of $\~S$ that sums to $\frac{(2H + (2H + 2K) + 4H)}{2} = 4H + K$.

($\Rightarrow$) Suppose there is a solution to the Knapsack problem where a subset $P \subseteq S$ that sums up to $K$. Then, a solution to the Partition problem must also exist, as we can assign $4H$ into $P$ and $2H + 2K$ to the other subset $S \setminus P$. This is confirmed as $\sum_{a_i \in P} + 4H = 4H + K = (2H - K) + (2H + 2K) = \sum_{a_i \in S \setminus P} + (2H + 2K)$.

($\Leftarrow$) Conversely, if there is a subset of $\~S$ that sums up to $4H + K$, say $Q$, we may conclude that both $2H + 2K$ and $4H$ elements are not in the same subset as $6H + 2K > 4H + K$. If the element $4H \in Q$; then, $\sum_{a_i \in Q \setminus {4H}} = K$, we found $Q \setminus {4H}$ as our answer to the Knapsack problem. Otherwise, the element $2H + 2K \in Q$; then, $\sum_{a_i \in Q \setminus {2H + 2K}} = 2H - K$, which is the complement subset of the answer to the Knapsack problem.

This proves that $x \in \texttt{Knapsack}$ iff $f(x) \in \texttt{Partition}, \forall x \in \{0, 1\}^*$.

The transformation involves adding two numbers to $S$, which can be done in a constant time. Additionally, calculating $H$ requires summing over $S$, which is done in $\mathcal{O}(n)$. Hence, $f$ is a polynomial time transformation, which proves that the Partition problem is NP-hard.

### Partition is NP-complete

Since the Partition problem is both in NP and NP-hard, we conclude that the Partition problem is NP-complete; hence, shown.
