---
title: "Variations of Golden-section Search on a Density Function"
date: "2023-08-14"
author: "Yohandi"
tags: []
---

Taking a further step from my previous post, in this one, we are going to see the application of the Golden-section Search to a density function. If you are not quite familiar with the method yet, you might want to refer first [here](https://www.yohandi.me/blog/golden-section-search/).

### Motivational Problem

Suppose we have a function $f : [L, R] \rightarrow [0, \infty)$ satisfying 

$$
\begin{align*}
    \int_{L}^R f(x) \:dx = 1
\end{align*}
$$

, which shows the spread of local minimum/maximum of a function $g : [L, R] \rightarrow \mathbb{R}$ that is unimodal. Denote $m$ as the minimum/maximum peak point of $g$, we aim to find a point $p$ such that

$$
\begin{align*}
    \int_{p - \delta}^{p + \delta} f(x) \:dx \leq \epsilon \texttt{  s.t.  } |m - p| \leq \delta
\end{align*}
$$
    
, where $\epsilon$ represents an acceptable error and $\epsilon < 1$. We achieve this by only querying the value of the function at specific points, i.e., evaluating $f(x)$ for chosen values of $x$ in the interval $[L, R]$, as efficiently as possible.

### Golden-section Search Method

#### Performing search based on the unimodal function

In the previous post, we have shown that in the Golden-section Search method, we usually want to have our pivot points to be located in both $L + (1 - \frac{1}{\phi})(R - L)$ and $R - (1 - \frac{1}{\phi})(R - L)$. However, we notice that the number of queries depends on the value of $L$ and $R$; consequently, when the range between $L$ and $R$ is big enough (say they are approaching $-\infty$ and $\infty$), the number of queries used will also become bigger. That being said, performing a search based on function $g$ will not be reliable.

#### Performing search based on the density function

To make up for this, we need to make an adjustment for which interval we are going to query as our base. By using prior knowledge about the statistical method, we can focus our search on where the minimum / maximum is more likely to be found. Hence, we want to perform our search based on function $f$. For the pivots that we needed, we want to set $p_1$ and $p_2$ as values that satisfy 

$$
\begin{align*}
    \int_{L}^{p_1} f(x) \:dx &= \int_{L}^{L} f(x) \:dx + (1 - \frac{1}{\phi}) \int_{L}^R f(x) \:dx \\
    &= (1 - \frac{1}{\phi})\int_{L}^{R} f(x) \:dx
\end{align*}
$$

and

$$
\begin{align*}
    \int_{L}^{p_2} f(x) \:dx &= \int_{L}^{R} f(x) \:dx - (1 - \frac{1}{\phi}) \int_{L}^R f(x) \:dx \\
    &= \frac{1}{\phi}\int_{L}^{R} f(x) \:dx
\end{align*}
$$

![Figure 1](/posts/figures/golden-section-search-on-density-function/0th-transition.png)
![Figure 2](/posts/figures/golden-section-search-on-density-function/1st-transition.png)

This works well as after each transition; we manage to remove either $[L, p_1]$ or $[p_2, R]$ from our search space. Although, in a sense, it is quite hard to calculate the number of queries needed as $p_1$ and $p_2$ do not entirely depends on both $L$ and $R$, but also $f$. However, notice that we can always choose $p = \frac{L + R}{2}$ and $\delta = \frac{R - L}{2}$ in any valid interval that subject to $|m - p| \leq \delta$. Denote $k$ as $\int_{p - \delta}^{p + \delta} f(x) \:dx$, let's analyze the two cases:

- Case $[L, p_1]$ is removed from the interval $[L, R]$:
    $$
    \begin{alignat*}{2}
    p &:= \frac{p_1 + R}{2} \\
    \delta &:= \frac{R - p_1}{2} \\
    k &:= \int_{p_1}^{R} f(x) \:dx &&= \int_{L}^{R} f(x) \:dx - \int_{L}^{p_1} f(x) \:dx \\
    &&&= \frac{1}{\phi} \int_{L}^{R} f(x) \:dx
    \end{alignat*}
    $$

- Case $[p_2, R]$ is removed from the interval $[L, R]$:
    $$
    \begin{align*}
        p &:= \frac{L + p_2}{2} \\
        \delta &:= \frac{p_2 - L}{2} \\
        k &:= \int_{L}^{p_2} f(x) \:dx = \frac{1}{\phi} \int_{L}^{R} f(x) \:dx
    \end{align*}
    $$

Each query allows us to reduce $k$ to $\frac{1}{\phi} k$; denote $Q$ as the number of queries needed, then:

$$
\begin{align*}
    Q = 3 + \lceil \log_\phi(\frac{1}{\epsilon}) \rceil&
\end{align*}
$$

### Additional Variation: Density Function

When encountering a similar function, say $f$, that does not satisfy the $\int_{-\infty}^{\infty} f(x) \:dx = 1$ condition, but still represents the spread of the peak point in a unimodal function, we can make a transformation to accommodate this scenario. We will transform the function $f(x)$ into $f^\prime(x)$ and $\epsilon$ into $\epsilon^\prime$, where: 

$$
\begin{align*}
    f^\prime(x) = \frac{1}{\int_{-\infty}^\infty f(x) \:dx}\ f(x)
\end{align*}
$$

and

$$
\begin{align*}
    \epsilon^\prime = \frac{1}{\int_{-\infty}^\infty f(x) \:dx} \epsilon, \epsilon < \int_{-\infty}^\infty f(x) \:dx
\end{align*}
$$

. And there we have it! If prior knowledge about the function's behavior or specific features of the local minima/maxima is known, we can always customize the search strategy accordingly. This could involve using different weighting schemes or adapting the pivots. 

&copy; 2023 Yohandi. All rights reserved.
