---
title: "DP Optimization: Convex Hull Trick"
date: "2023-08-21"
author: "Yohandi"
tags: [algorithm, dynamic-programming, optimization, tutorial]
---

"Geometry being useful", I copied that down from [this blog](https://codeforces.com/blog/entry/63823). And yes, in any subject, geometry often steps in to offer a fresh perspective. The Convex Hull Trick is a testament to this, seamlessly blending algorithmic efficiency with geometric intuition. In this post, I will discuss pretty much about this method.

### Motivational Problem

Suppose there are $n$ rectangles in a 2D Cartesian Plane, each defined by vertices $(0,0)$ and $(x_i,y_i)$, along with a number $a_i$. We want to select some of these rectangles such that the area of their union minus the sum of the $a_i$ values of the chosen rectangles is maximized.

Constraints given:
- $1 \leq n \leq 10^6$
- $1 \leq x_i, y_i \leq 10^9$ (for each $i$ such that $0 \leq i < n$)
- $0 \leq a_i \leq x_i \cdot y_i$ (for each $i$ such that $0 \leq i < n$)
- No nested rectangles exist

This problem comes straight from [Codeforces Round 526 (Div. 1E)](https://codeforces.com/problemset/problem/1083/E).

### Dynamic Programming Solution

Let's consider these $(x_i, y_i, a_i)$ tuples: $[(6, 2, 4), (1, 6, 2), (2, 4, 3), (5, 3, 8)]]$.

![](/posts/figures/convex-hull-trick/sample-case.gif)

Because no nested rectangles exist in all cases, we can sort these tuples by $x$ without losing their essences. Note that sorting by $x$ in ascending order also sorts the tuples by $y$ in descending order.

Denote $\texttt{dp}_i$ as the maximum value that can be achieved by selecting the $i$-th rectangle (from the sorted version) and some of the previous rectangles. Then, our answer will be

$$
\begin{align*}
    \texttt{ans} = \max_{0 \leq i < n} \texttt{dp}_i
\end{align*}
$$

, where

$$
\begin{align*}
    \texttt{dp}_i =  (x_i \cdot y_i - A_i) + \max(\max_{0 \leq j < i} \texttt{dp}_j - x_j \cdot y_i,\ 0)
\end{align*}
$$

.

Parts explanation:
- The $(x_i \cdot y_i - A_i)$ part is obtained as the reward for selecting the $i$-th rectangle.
- The $\texttt{dp}_j$ part acts as an additional reward for selecting the $j$-th rectangle.
- The $-x_j \cdot y_i$ part, which is derived from $-\min(x_i, x_j) \cdot \min(y_i, y_j)$,  is obtained as the consequence of selecting the $i$-th rectangle with $j$-th rectangle (and presumably any rectangle that maximizes the $\texttt{dp}_j$ value). Note that $x_j \cdot y_i$ is the intersection for the $i$-th rectangle and the $j$-rectangle. This part is important as the union area of the $i$-th rectangle and the $j$-th rectangle is $(x_i \cdot y_i)\ \cup\ (x_j \cdot y_j) = (x_i \cdot y_i) + (x_j \cdot y_j) - (x_i \cdot y_i)\ \cap\ (x_j \cdot y_j)$.

This dynamic programming solution works in $O(n^2)$; however, it is still not suffice as $n$ might be $10^6$. We need an optimization towards it.

### Convex Hull Trick

This is where our main optimization technique, the Convex Hull Trick, comes in handy. The Convex Hull Trick is a computational geometry used to manage a set of affine functions, constructing a lower / upper hull. To illustrate, suppose we are going to insert the following affine functions: $-x + 4$, $-2x + 5$, $-5x + 8$, and $-6x + 10$, into our lower hull.

![](/posts/figures/convex-hull-trick/convex-hull-sample-case.gif)

Notice that in our lower hull, we always want to have the intersection points of every two lines that are side by side sorted. Formally, if we have a set of affine functions in our lower hull, say $f_0(x)$, $f_1(x)$, $\ldots$, and $f_{n - 1}(x)$, with $p_i$ representing the x-coordinate of the intersection point of $f_i(x)$ and $f_{i + 1}(x)$, i.e., $f_i(p_i) = f_{i + 1}(p_i)$, for $0 \leq i < n - 2$; then, it is essential that $p_0 > p_1 > \ldots > p_{n - 2}$ (or sorted in the other way).

If there is a scenario where $p_i = p_{i + 1}$, we can discard either $f_i(x)$ or $f_{i + 1}(x)$. The choice depends on the gradient, considering whether it is lower / higher and negative / positive.

The implementation is as follows:

```c++
struct Line {
  long long m, c;
  Line(long long m, long long c) : m(m), c(c) {}

  long long y(long long x) { return m * x + c; }
  double intersect(Line other) const {
    return (double)(c - other.c) / (double)(other.m - m);
  }
};

vector<Line> ch;

void addLine(Line line) {
  auto comp = [&](const Line &a, const Line &b, const Line &c) -> bool {
    return a.intersect(b) > b.intersect(c); // p_0 > p_1 > ... > p_{n - 2}
  };

  while (ch.size() >= 2 && !comp(ch[ch.size() - 2], ch.back(), line)) {
    ch.pop_back();
  }

  ch.push_back(line);
}
```

The implementation above operates efficiently when the inserted gradient is in descending order. The reason will be explained later.

In our set of affine functions, it can be observed that:
- $f_0(x)$ maximizes the value of $x$ for $x \in [p_0, \infty)$;
- $f_1(x)$ maximizes the value of $x$ for $x \in [p_1, p_0]$;
- $\ldots$
- $f_{n - 2}(x)$ maximizes the value of $x$ for $x \in [p_{n - 2}, p_{n - 3}]$;
- $f_{n - 1}(x)$ maximizes the value of $x$ for $x \in (-\infty, p_{n - 2}]$.

Using this observation, whenever we want to look up for $i$ that maximizes $f_i(x)$ for an $x$, we can perform a binary search on the intersection points to determine the domain where $x$ lies.

```c++
int optimalLine(long long x) {
  auto p = [&](const int i) -> double { return ch[i].intersect(ch[i + 1]); };

  return lower_bound(ch.begin(), ch.end() - 1, x,
                     [&](const Line &line, long long val) {
                       int idx = &line - &ch[0];
                       return p(idx) > val;
                     }) -
         ch.begin();
}
```

Reverting to our primary dynamic programming solution, where we had:

$$
\begin{align*}
    \texttt{dp}_i &= (x_i \cdot y_i - A_i) + \max(\max_{0 \leq j < i} \texttt{dp}_j - x_j \cdot y_i,\ 0)
\end{align*}
$$

Regardless of the value of $j$, we consistently add $x_i \cdot y_i - A_i$ to $\texttt{dp}_i$; thus, this can be omitted from our optimization process. An affine function $f_i(x) = m_i \cdot x + c_i$ is formed by assigning $m_i$ as $-x_i$ and $c_i$ as $\texttt{dp}_i$. If $C$ represents a constant in $\texttt{dp}_i$, then $C = x_i \cdot y_i - A_i$. Our $\texttt{dp}$ equation can then be expressed as:

$$
\begin{align*}
    \texttt{dp}_i &= \max(\max_{0 \leq j < i} (m_j \cdot y_i + c_j),\ 0) + C
\end{align*}
$$

To further simplify our dynamic programming, we may also add a line $f_{-1}(x) = 0$ to handle the $\max(\ldots, 0)$ component.

$$
\begin{align*}
    \texttt{dp}_i &= \max_{-1 \leq j < i} (m_j \cdot y_i + c_j) + C
\end{align*}
$$

The solution's flow is as follows:
```c++
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  struct InputFormat {
    long long x, y, A;
    bool operator<(const InputFormat &other) const {
      return tie(x, y, A) < tie(other.x, other.y, other.A);
    }
  };

  long long N, ans = 0;
  cin >> N;

  vector<InputFormat> arr(N);
  vector<long long> x(N), y(N), A(N), dp(N);

  for (auto &a : arr)
    cin >> a.x >> a.y >> a.A;
  sort(arr.begin(), arr.end());

  for (int i = 0; i < N; ++i)
    tie(x[i], y[i], A[i]) = make_tuple(arr[i].x, arr[i].y, arr[i].A);

  addLine(Line(0, 0));
  for (int i = 0; i < N; ++i) {
    dp[i] = ch[optimalLine(y[i])].y(y[i]) + (x[i] * y[i] - A[i]);
    addLine(Line(-x[i], dp[i]));

    ans = max(ans, dp[i]);
  }

  cout << ans << endl;
  return 0;
}
```

The gradient of the inserted line is guaranteed to be in descending order as the gradient is $-x_i$ and $x_i$ is in ascending order. This explains the previous $\texttt{addLine}$ implementation. Querying the $\texttt{optimalLine}$ only performs binary search from $0$ to $n - 1$, resulting in a complexity of $O(\log n)$ per query. The armortized total operations in $\texttt{addLine}$ function is $O(n)$. The overall solution operates in $O(n \log n)$. My full solution is accessible [here](https://codeforces.com/contest/1083/submission/219676253).

### Variation

#### Upper Hull

In a case where we have a minimization problem, we want to look up for the upper hull. Some comparisons in the code, especially in $\texttt{comp}$ within $\texttt{addLine}$ and the binary search in $\texttt{optimalLine}$, need to be inverted.

#### Dynamic Convex Hull Trick

In this particular case, we do not have the guarantee of having the gradient insertion sorted, whether it is in ascending order or in descending order; consequently, we no longer can use $\texttt{stl::vector}$ for our data structure. We may use $\texttt{stl::set}$ to maintain the dynamic gradients. Or... we may use Li Chao Tree, which I will discuss in the upcoming post.

And there we have it! I have always found the Convex Hull Trick fascinating, especially when it comes to refine a naive $O(n^2)$ dynamic programming approach down to $O(n \log n)$. Of course, it still requires an additional property, which is to have the dynamic programming rewritable as an affine function. Some other DP optimizations, such as Divide and Conquer, Knuth, and more will probably discussed in the future posts as well! Stay tuned! 

&copy; 2023 Yohandi. All rights reserved.
