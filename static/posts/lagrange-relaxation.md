---
title: "Lagrange Relaxation"
date: "2023-09-17"
author: "Yohandi"
tags: [geometry, optimization, tutorial]
---

In solving a problem, it is often difficult to obtain the optimal solution due to strict constraints, making it computationally expensive. Lagrange Relaxation is a method that loosens some particular constraints of the problem with the objective to optimize the findings. This is done by introducing Lagrange multipliers for those relaxed constraints. The solution to the problem with the relaxed constraints is then used as the boundary (both upper and lower) for the original problem.

The [Aliens](https://tlx.toki.id/problems/ioi-2016/D2-3) problem from IOI 2016 brought significant attention for this method, making it also known as Aliens' Trick. Ever since, this method has started to gain popularity among competitive programmers. In this blog, we will delve deeper into this method; especially in solving the Aliens problem. If you are not familiar with the Convex Hull Trick yet, I suggest you to read my blog [here](https://www.yohandi.me/blog/convex-hull-trick/).

### Motivational Problem: IOI 2016 - Aliens

We have a low-resolution photo of a remote planet's area, which is divided into an $m \times m$ grid consisting of $n$ points that we are interested in. Our satellite, passing over the main diagonal of the grid, can take high-resolution photos of square areas. Each square's opposite corners must be on the grid's main diagonal. The satellite can take at most $k$ high-resolution photos. Our task is to choose up to $k$ square areas to photograph ensuring:

1. Every cell with a point of interest is captured.
2. The total number of photographed cells is minimized.

We want to find the smallest possible total number of photographed cells.

#### Constraints
- $1 \leq k \leq n \leq 10^5$
- $1 \leq m \leq 10^6$

#### Subtasks

|  no.  | points |       $n$       |         $m$        |     $k$    |
|:-----:|:-------:|:---------------:|:------------------:|:----------:|
| 1 - 3 |  $25$  |    $\leq 500$   |    $\leq 1\ 000$   |            |
|   4   |  $16$  |  $\leq 4\ 000$  |                    |            |
|   5   |  $19$  |  $\leq 50\ 000$ |                    | $\leq 100$ |
|   6   |  $40$  |                 |                    |            |

#### On contest score distribution

![](/posts/figures/lagrange-relaxation/aliens-score-distribution.png)

### Naive Dynamic Programming (25 points)

Notice that due to constraint of "each square's opposite corners must be on the grid's main diagonal", we can always interchange the value of $r_i$ and $c_i$ as the new point is a reflection point across the main diagonal. As a result, the order of $r_i$ and $c_i$ is irrelevant. For each point $i$, visualize it as a segment that spans the range $[l_i, r_i] = [\min(r_i, c_i), \max(r_i, c_i)]$. Consequently, a photo that covers a point $(a, a)$ to $(b, b)$ will capture point $i$ if and only if $a \leq l_i \leq r_i \leq b$.

Further, this observation indicates that capturing a point $j$ ($i < j$) will also encompass point $i$ if $l_j \leq l_i \leq r_i \leq c_j$. With that, we may simply discard point $i$. After such eliminations, all remaining points will have the property: for points $i$ and $j$ ($i < j$), $r_i < r_j$ and $c_i < c_j$.

Let $\texttt{dp}_{i, j}$ denotes the minimum cost to cover first $i$ points with at most $j$ photos. Then,

$$
\begin{align*}
\texttt{dp}_{0, j} &= 0 \\
\texttt{dp}_{i, j} &= \min_{t < i} \texttt{dp}_{t, j - 1} + (r_i - l_{t + 1} + 1)^2 - \max(r_t - l_{t + 1} + 1, 0)^2
\end{align*}
$$

Here is a breakdown of the components:
- The $\texttt{dp}_{t, j - 1}$ represents the cost of capturing the first $t$ points using $j - 1$ photos. Then, we aim to cover the point $t + 1$ up to point $i$ using $1$ photo.
- The expression $(r_i - l_{t + 1} + 1)^2$ calculates the cost of capturing the point $t + 1$ up to point $i$ using $1$ photo.
- The $\max(r_t - l_{t + 1} + 1, 0)^2$ part is accounted to an overcharging cost due to the overlap between point $t$ and point $t + 1$. Hence, it is substracted to correct the cost.

This dynamic programming solution works in $\mathcal{O}(n^2 k)$.

### Convex Hull Trick (60 points)

We had:

$$
\begin{align*}
\texttt{dp}_{0, j} &= 0 \\
\texttt{dp}_{i, j} &= \min_{t < i} \texttt{dp}_{t, j - 1} + (r_i - l_{t + 1} + 1)^2 - \max(r_t - l_{t + 1} + 1, 0)^2
\end{align*}
$$

Our dynamic programming can be expressed as:

$$
\begin{align*}
\texttt{dp}_{0, j} &= 0 \\
\texttt{dp}_{i, j} &= \min_{t < i} (m_{t, j - 1} \cdot x_{i, j} + c_{t, j - 1}) + C_{i, j}
\end{align*}
$$

where:

- $m_{t, j - 1} = -2(l_{t + 1} - 1)$
- $x_{i, j} = r_i$
- $c_{t, j - 1} = \texttt{dp}_{t, j - 1} + (l_{t + 1} - 1)^2 - \max(r_t - l_{t + 1} + 1, 0)^2$
- $C_{i, j} = r_i^2$

This Convex Hull Trick approach runs about an $\mathcal{O}(kn)$ armortized time. Note that it is not $\mathcal{O}(kn \log n)$ as we can use a $\texttt{std::deque}$ instead of a $\texttt{std::vector}$ here, given that the point queries are in increasing order.

### Lagrange Relaxation (100 points)

> _The following solution idea is inspired by and adapted from the official solution._

Denote $f(i, j)$ to be a function that represents our dynamic programming solution, i.e. $f(i, j) = \texttt{dp}_{i, j}$. We want to relax the constraints on the number of photos taken. Let's assume we don't have the $k$ constraint and we want to apply a cost on each photo taken to make up for it. Define $\mathcal{L}(i, j, \lambda)$ to be $f(i, j) + \lambda j$, implying an additional cost of $\lambda$ for each photo taken.

For a $\lambda$, we may define $g(i)$ to represent as another optimization problem that satisfies the following:
$$
\begin{align*}
g(i) &= \min_{k = 1}^n \mathcal{L}(i, k, \lambda) \\
&= \min_{k = 1}^n f(i, k) + \lambda k \\
&= \min_{t < i} g(t) + (r_i - l_{t + 1} + 1)^2 - \max(r_t - l_{t + 1} + 1, 0)^2 + \lambda\\
\end{align*}
$$
By solving $g(n)$ for a given $\lambda$ allows us to obtain the minimum number of photos required to capture all $n$ points and achieve the minimum cost when each photo is charged $\lambda$ cost, let's define it as $p(\lambda)$. 

A function $f(i, j)$ is said to be convex if it satisfies: $f(i, j - 1) - f(i, j) \geq f(i, j) - f(i, j + 1)$. Given that $f(i, j)$ is convex, so is $\mathcal{L}(i, j, \lambda)$. This implies:

$$
\begin{align*}
p(\lambda) &= \min x\ \ \texttt{s.t.} \mathcal{L}(n, x, \lambda) \leq \mathcal{L}(n, x + 1, \lambda) \\
&= \min x\ \ \texttt{s.t.} f(n, x) - f(n, x + 1) \leq \lambda\\
\end{align*} \\
$$

With that we may find $\lambda_k \in [0, m^2]$ that satisfies $k \leq p(\lambda_k)$ and $p(\lambda_k + 1) \leq k$. This can be done using binary search with $\mathcal{O}(n \log m)$ time complexity (the linear $n$ is obtained from computing $g(n)$ using Convex Hull Trick).

Last, we only need to find the exact value of $f(n, k)$, which is our original objective. The interval $[p(\lambda_k + 1), p(\lambda_k)]$ signifies the range we are interested in. Considering that $\forall i \in [p(\lambda_k + 1), p(\lambda_k) - 1]: f(n, i) - f(n, i + 1)$ remains constant (slope is constant), we may use linear interpolation to calculate our answer to the original problem. Let $\Delta = f(n, p(\lambda_k)) - f(n, p(\lambda_k + 1))$; then,

$$
f(n, k) = f(n, p(\lambda_k)) - (k - p(\lambda_k)) \frac{\Delta}{p(\lambda_k + 1) - p(\lambda_k)}
$$

The overall solution operates in $\mathcal{O}(n \log n + n \log m)$.

### Lagrange Relaxation in General

#### Basic Idea

1. Decomposition of the Original Problem: Decompose the original problem into a blend of a simpler optimization problem and an added term to penalize constraint violations.
   
2. Lagrange Function Formulation: In the equation below, $f(x)$ represents the objective function, $g(x)$ denotes the constraint equations, $b$ stands for their boundaries, and $\lambda$ acts as the Lagrange multiplier:

   $$
   \mathcal{L}(x, \lambda) = f(x) + \lambda (g(x) - b)
   $$

3. Bounds Identification: Establish both the lower and upper bounds wherein the solution to the original problem lies within the defined interval.

#### Importance of Convexity

1. Guaranteed Global Optima: Convexity ensures that the solution obtained from the relaxed problem, supported by Lagrange multipliers, offers a valid and global optimum bound. 

2. Optimization Simplification: A convex optimization landscape simplifies the process, reducing potential local minima or maxima that can complicate the search for an optimal solution.

3. Efficient Solutions: When the Lagrange function is convex, it facilitates the efficient determination of the solution for the relaxed problem. This is important since Lagrange relaxation primarily aims to transform intricate problems into manageable sub-problems.

### References

1. **Chethiya Abeysinghe**, "IOI 2016 - Solutions," International Olympiad in Informatics.

2. **Mamnoon Siam**, "Attack on Aliens," Siam's Blog. https://mamnoonsiam.github.io/posts/attack-on-aliens.html.
