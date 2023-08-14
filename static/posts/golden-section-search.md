---
title: "Golden-section Search"
date: "2023-08-09"
author: "Yohandi"
tags: []
---

You might have heard about the Golden Ratio. It is this special number that often shows up in mathematics. The Golden Section Search uses this very ratio to solve a particular kind of problem, such as finding the minimum or maximum of a unimodal function.

### Motivational Problem

Suppose we have a unimodal function $f : [L, R] \rightarrow \mathbb{R}$, where the function increases on $[L, m]$ and decreases on $[m, R]$, with $m$ being the point where the function reaches its only local minimum/maximum (or it can be considered as global minimum/maximum in that particular function). We aim to find $f(m \pm \delta)$, where $\delta$ represents an acceptable error ranging in the interval $[0, 0.5]$, serving as the satisfaction threshold. We achieve this by only querying the value of the function at specific points, i.e., evaluating $f(x)$ for chosen values of $x$ in the interval $[L, R]$, as efficiently as possible.

### Ternary Search Method

One of the well-known algorithms, Ternary Search, uses a strategy of picking two pivot points $p_1$ and $p_2$ such that $L < p_1 < p_2 < R$, and then evaluating $f(p_1)$ and $f(p_2)$. This evaluation leads to one of three possible cases, which are listed below. For the sake of simplicity, let's assume that the unimodal function has a local maximum that we are seeking to find (if we were looking for a local minimum, we would simply invert each comparison).

- Case $f(p_1) < f(p_2)$:
    
    Considering that the function is increasing before the maximum point, we are faced with one of the following scenarios:

    - $m \leq p_1 < p_2$, which is a contradiction under the current assumption that $f(p_1) < f(p_2)$, since the function would be increasing from $L$ until $p_1$; hence, it is impossible to have a maximum point on $p_1$ and before $p_1$.
    - $p_1 < m \leq p_2$, which implies that the maximum must lie in $(p_1, p_2]$.
    - $p_1 < p_2 < m$, which implies that the function is still increasing until $p_2$, meaning that the maximum must lie in $(p_2, R]$.

    ![](/posts/figures/golden-section-search/ternary-search-case-1.png)
    ![Figure 1 & 2](/posts/figures/golden-section-search/ternary-search-case-2.png)
    
    This case describes the possibilities and illustrates why, in a case where $f(p_1) < f(p_2)$, we confidently narrow down our search space into $(p_1, p_2] \cup (p_2, R] = (p_1, R]$.

- Case $f(p_1) > f(p_2)$:
    
    We now deal with a similar situation to the previous case. We have either:

    - $m < p_1 < p_2$, which implies that the function is now in the state of decreasing after $p_1$, meaning that the maximum must lie in $[L, p_1)$.
    - $p_1 \leq m < p_2$, which implies that the maximum must lie in $[p_1, p_2)$.
    - $p_1 < p_2 \leq m$, which is a contradiction under the current assumption that $f(p_1) > f(p_2)$, since the function would be decreasing from $p_2$ onwards; hence, it is impossible to have a maximum point on $p_2$ and after $p_2$.

    ![](/posts/figures/golden-section-search/ternary-search-case-3.png)
    ![Figure 3 & 4](/posts/figures/golden-section-search/ternary-search-case-4.png)
    
    This case describes the possibilities and illustrates why, in a case where $f(p_1) > f(p_2)$, we confidently narrow down our search space into $[L, p_1) \cup [p_1, p_2) = [L, p_2)$.

- Case $f(p_1) = f(p_2)$:
    
    This case is quite simple as out of the possibilities below, only one is deemed valid:
    - $m \leq p_1 < p_2$, which is not a valid possibility, as this case implies that the function is now decreasing from $m$ onwards. Consequently, we have $f(p_1) > f(p_2)$, which is a contradiction under the current assumption that $f(p_1) = f(p_2)$.
    - $p_1 < m < p_2$, which is valid as the maximum lies in $(p_1, p_2)$.
    - $p_1 < p_2 \leq m$, which is not a valid possibility, as this case implies that the function must be increasing before $m$. Consequently, we have $f(p_1) < f(p_2)$, which is a contradiction under the current assumption that $f(p_1) = f(p_2)$.

    ![Figure 5](/posts/figures/golden-section-search/ternary-search-case-5.png)
    
    This allows us to narrow down the search space into $(p_1, p_2)$.

Ternary Search partitions the current search space into three equal-sized intervals. Denote $N$ as the length of the search space, i.e., $N = R - L$, then the size of the partitioned interval is $\frac{N}{3}$. This means that we want to choose $p_1 = L + \frac{N}{3}$ and $p_2 = R - \frac{N}{3}$. Denote $Q$ as the number of queries used to solve the motivational problem using the Ternary Search method.

$$
\begin{align*}
Q & = 2 \times \lceil \log_\frac{{R - L}}{{\max(R - p_1,\ p_2 - L,\ p_2 - p_1)}} (R - L)\rceil \\
& = 2 \times \lceil \log_\frac{{N}}{{\max(R - L - \frac{N}{3},\ R - \frac{N}{3} - L,\ R - \frac{N}{3} - L - \frac{N}{3})}} (N)\rceil \\
& = 2 \times \lceil \log_\frac{{N}}{{\max(\frac{2N}{3},\ \frac{2N}{3},\ \frac{N}{3})}} (N)\rceil \\
& = 2 \times \lceil \log_{\frac{3}{2}} (N)\rceil \\
\end{align*}
$$

### Adapting Ternary Search Method Towards Binary Search

Instead of dividing the interval into three equal parts, which typically lead to reducing the search space to either the first two-thirds, the last two-thirds, or the middle one-third, we could consider a variation where the pivots $p_1$ and $p_2$ are chosen closer to the center of the interval. This resembles the idea of Binary Search.

By choosing both $p_1$ and $p_2$ as close as possible to the middle of the interval, we want to set the limits as $k$ approaches just above $2$: $p_1 = L + \frac{N}{k}$ and $p_2 = R - \frac{N}{k}$. Then, the number of queries ($Q$) used can be calculated as follows:

$$
\begin{align*}
Q & = 2 \times \lceil \log_\frac{{R - L}}{{\max(R - p_1,\ p_2 - L,\ p_2 - p_1)}} (R - L)\rceil \\
& = 2 \times \lceil \lim_{k \to 2^+} \log_\frac{{N}}{{\max(R - L - \frac{N}{k},\ R - \frac{N}{k} - L,\ R - \frac{N}{k} - L - \frac{N}{k})}} (N)\rceil \\
& = 2 \times \lceil \lim_{k \to 2^+} \log_\frac{{N}}{{\max(N - \frac{N}{k},\ N - \frac{N}{k},\ N - 2 \frac{N}{k})}} (N)\rceil \\
& = 2 \times \lceil \lim_{k \to 2^-} \log_k(N) \rceil \\
& = 2 \times \lceil \log_2 (N)\rceil \\
\end{align*}
$$

### Golden-section Search Method

The approach of the Golden-section Search is quite similar to the Ternary Search, as the idea of maintaining two pivots is inherited. For the sake of simplicity, we will once again assume that the unimodal function has a local maximum that we are seeking to find. Let's denote the two pivots as $p_1$ and $p_2$, which satisfy $L < p_1 < p_2 < R$, and be certain that the point $m$ is located in the interval $[L, R]$. Assume that by using the previous queries, we already have the value of $f(L)$, $f(R)$, and one of the $f(p_1)$ and $f(p_2)$ such that $\max(f(L), f(R)) \leq f(p_1)$ or $f(p_2)$. Consider that we have $f(p_1)$ (in a case where we have $f(p_2)$, we only need to mirror the domain toward $\frac{L + R}{2}$, i.e., the middle point), our next step is to query the value of $f(p_2)$, and we will handle it based on the following similar cases in Ternary Search Method:

- Case $f(p_1) = f(p_2)$:
    
    As we agreed that in this case the point $m$ lies in $(p_1, p_2)$, we may include this case to either $f(p_1) < f(p_2)$ or $f(p_1) > f(p_2)$ as $(p_1, p_2) \subset (p_1, R]$ and $(p_1, p_2) \subset [L, p_2)$.

- Case $f(p_1) < f(p_2)$:
    
    As explained, this case indicates that the point $m$ lies in $(p_1, R]$. Then, we can set $L := p_1$, $p_1 := p_2$, and $R := R$, utilizing the value of $f(p_1)$ as the new value of $f(L)$ and the value of $f(p_2)$ as the new value of $f(p_1)$. The choice of pivot is made accordingly; the reason is shown later.

    ![Figure 6](/posts/figures/golden-section-search/golden-section-search-case-1.png)

- Case $f(p_1) > f(p_2)$:
    
    Similarly, as explained, this case indicates that the point $m$ lies in $[L, p_2)$. Then, we can set $R := p_2$, $p_2 := p_1$, and $L := L$, utilizing the value of $f(p_2)$ as the new value of $f(R)$ and the value of $f(p_1)$ as the new value of $f(p_2)$ in the new interval. Again, the choice of pivot is made accordingly; the reason is shown later.

    ![Figure 7](/posts/figures/golden-section-search/golden-section-search-case-2.png)

Notice that after the transition, the assumptions we made are all still satisfied. With that, we manage to remove either $[L, p_1]$ or $[p_2, R]$ from our search space with only $1$ additional query, whereas the Ternary Search uses $2$ additional queries. However, it is still quite tricky to choose the value of $p_1$ and $p_2$ as we want the values to be optimal when we inherit them for the next interval query. 

Suppose $p_1$ is located in $L + k(R - L)$ where $k \in (0, 0.5)$ and a constant, then, $p_2$ should also be located in $R - k(R - L)$. Assuming that we manage to remove the interval $[L, p_1]$ from our search space, then, we want $p_2$ to be located either in $p_1 + k(R - p_1)$ as the new $p_1$ or in $R - k(R - p_1)$ as the new $p_2$. Let's consider these two cases:

- Case $p_2$ is assigned as the new $p_1$:

$$
\begin{align*}
\frac{R - p_1}{R - L} &= \frac{R - p_2}{R - p_1} \\
(R - p_1)^2 &= (R - L)(R - p_2) \\
(R - L - k(R - L))^2 &= (R - L)(R - R + k(R - L)) \\
(R - L)^2(1 - k)^2 &= k(R - L)^2 \\
k^2 - 3k + 1 &= 0 \\
\Rightarrow k &= \{\frac{3 - \sqrt{5}}{2}, \frac{3 + \sqrt{5}}{2}\}
\end{align*}
$$

&emsp; Since $k \in (0, 0.5)$, we only consider $k = \frac{3 - \sqrt{5}}{2}$.

- Case $p_2$ is assigned as the new $p_2$:

$$
\begin{align*}
\frac{R - p_2}{R - L} &= \frac{R - p_2}{R - p_1} \\
R - L &= R - p_1 \\
L &= p_1 \\
\Rightarrow k &= 0 \\
\end{align*}
$$

&emsp; Since $k \notin (0, 0.5)$, this case is not considered. With this, we have shown the reason for the choice of the new pivot.

The only $k$ that satisfies our needs is in the case where $p_2$ is assigned as the new $p_1$. With that, we can calculate the number of queries used to solve the motivational problem using the Golden-section Search Method. Denote $Q$ as the number of queries and $N$ as the length of the search space, i.e., $N = R - L$.

$$
\begin{align*}
Q &= 3 + \lceil \log_\frac{R - L}{\max(R - p_1, p_2 - L)} (R - L) \rceil \\
&= 3 + \lceil \log_\frac{R - L}{\max(R - L - k(R - L), R - k(R - L) - L)} (R - L) \rceil \\
&= 3 + \lceil \log_\frac{N}{N(1 - k)} (N) \rceil \\
&= 3 + \lceil \log_\frac{2}{2 - 3 + \sqrt{5}} (N) \rceil \\
&= 3 + \lceil \log_\frac{\sqrt{5} - 1}{2} (N) \rceil \\
&= 3 + \lceil \log_\phi (N) \rceil \\
\end{align*}
$$

Notice that the additional $3$ queries in this method are used for the initial $L$, $R$, and one of $p_1$ and $p_2$. It is clear that $\log_\phi (N) < 2\log_2(N)$ as $\phi > \sqrt{2}$; hence, the Golden-section Search Method provides a better and more efficient way to solve the motivational problem.

And there we have it! By strategically positioning our pivots and leveraging the mathematics of the golden ratio, we have managed to achieve an even more efficient solution.

You may compare the number of queries used for all the explained methods side-by-side in the below neat little table.

| Method                 | Number of Queries Used                         |
|------------------------|------------------------------------------------|
| Ternary Search         | $2 \times \lceil \log_{\frac{3}{2}} (N)\rceil$ |
| Adapted Ternary Search | $2 \times \lceil \log_2 (N)\rceil$             |
| Golden-section Search  | $3 + \lceil \log_\phi (N) \rceil$              |

In the upcoming post, I am planning to write about the Variation of the Golden-section Search on a Density Function. Stay tuned!

&copy; 2023 Yohandi. All rights reserved.
