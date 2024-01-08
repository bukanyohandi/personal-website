---
title: "[Tutorial] Li Chao Tree"
date: "2023-09-11"
author: "Yohandi"
tags: [data-structure, geometry, tutorial]
---

Li Chao Tree is a data structure that offers a method to insert specific functions and query the minimum (or maximum) value at a point in logarithmic time. It was first introduced by Li Chao during a lecture in 2013.

For any pair of inserted functions, $f_i(x)$ and $f_j(x)$ (where $1 \leq i < j \leq n$), there exists a point $p$ such that:
-  $f_i(x) \leq f_j(x)$ when $x \leq p$, and
-  $f_i(x) \geq f_j(x)$ when $x \geq p$

(or the conditions could be in reverse order) for all $x$ in the possible query range. The concept behind the Li Chao Tree bears some resemblance to the Segment Tree, but what distinguishes it is the unique way it stores function information in each node.

### Motivational Problem

You are given $n$ functions $f_i(x) = a_ix^3 + b_ix^2 + c_ix + d_i$ (where $1 \leq i \leq n$). For each of the $q$ queries, determine $\min_{1 \leq i \leq n} f_i(x_j)$ for a given $x_j$.

Constraints given:
- $1 \leq n, q \leq 10^5$
- $0 \leq a_i \leq 10^3$ (for each $i$ such that $1 \leq i \leq n$)
- $0 \leq b_i, c_i, d_i \leq 10^5$ (for each $i$ such that $1 \leq i \leq n$)
- $0 \leq x_j \leq 10^5$ (for each $j$ such that $1 \leq j \leq q$)

This problem comes straight from [CodeChef - Polynomials](https://www.codechef.com/problems/POLY).

### Li Chao Tree

Much like the Segment Tree, we want to perform a traversal of nodes from root to leaf. Each node is expected to store a function information such that when we traverse from root to leaf, it is guaranteed that one of the functions met in the path gives the minimum (or maximum) value. For the sake of simplicity, let's assume that our problem queries for minimum value.

Suppose we want to insert a function $f_j(x)$. Denote $g(x)$ as a function that were saved in the current node resulting from previous insertions. Define $\texttt{mid}$ as the middle-point of the range, e.g. a segment $[L, R)$, in the current node. Then, we may perform two comparisons: $f_j(L)$ with $g(L)$ and $f_j(\texttt{mid})$ with $g(\texttt{mid})$.

- Case $f_j(L) \geq g(L)$ and $f_j(\texttt{mid}) \geq g(\texttt{mid})$:

    This implies that there are three possibilities: there is no $p$ or $p < L$ or $p \geq \texttt{mid}$.
    - there is no $p$ that meets our criteria; hence, no action is required.
    - $p < L$, and again, no action is needed as it is outside our considered interval.
    - $p \geq \texttt{mid}$, which means $p$ may affect the second half of the current segment, i.e. $[\texttt{mid}, R)$. Thus, we need to recurse to the right child of the current node to handle that case.

    We also don't need to update the current node as $g(x) \leq f_j(x)$ when $L \leq x \leq \texttt{mid}$. Whenever a query of $L \leq x \leq \texttt{mid}$ is performed, the traversal from root to leaf is guaranteed to pass through this node.

- Case $f_j(L) < g(L)$ and $f_j(\texttt{mid}) < g(\texttt{mid})$:

    This mirrors the first case with identical potential scenarios. However, since root-to-leaf traversal will definitely traverse this node for any query in the range $[L, \texttt{mid})$, the current node should be updated to $g(x) := f_j(x)$ to ensure the minimum value can be obtained.

- Case $f_j(L) < g(L)$ and $f_j(\texttt{mid}) \geq g(\texttt{mid})$:

    This implies that $p$ is located somewhere in $[L, \texttt{mid})$, and we need to recurse to the left child of the current node to handle that case. We don't need to update the current node as $g(x) \leq f_j(x)$ when $x \geq \texttt{mid}$. Whenever a query of $\texttt{mid} \leq x < R$ is performed, the traversal from root to leaf is guaranteed to pass through this node.

- Case $f_j(L) \geq g(L)$ and $f_j(\texttt{mid}) < g(\texttt{mid})$:

    This implies that $p$ is located somewhere in $[L, \texttt{mid})$, and we need to recurse to the left child of the current node to handle that case. As the traversal from root to leaf is guaranteed to pass through this node whenever a query of $\texttt{mid} \leq x < R$ is performed, we need to update the current node $g(x) := f_j(x)$ so that we can retrieve the minimum value.

Below, the implementation for inserting the function is showcased. Bear in mind that the `struct Node` in this code is tailored to the problem described. Adjustments may be necessary based on specific needs.

```c++
using ll = long long;

struct Function {
  ll a, b, c, d;
  Function(ll a = 0, ll b = 0, ll c = 0, ll d = 0) : a(a), b(b), c(c), d(d) {}
  ll f(ll x) const { return a * x * x * x + b * x * x + c * x + d; }
};

const ll INF = 1e18;

struct Node {
  Function function{0, 0, 0, INF};
  Node *left = nullptr, *right = nullptr;
};

Node *root;
const int S = 350, L = S + 1, R = 1e5 + 1;

void insertFunction(Function newFunction, Node *node = root, int l = L,
                    int r = R) {
  if (!node)
    return;
  int m = (l + r) >> 1;
  bool left = newFunction.f(l) < node->function.f(l);
  bool mid = newFunction.f(m) < node->function.f(m);
  if (mid)
    swap(newFunction, node->function);
  if (l == r - 1)
    return;
  Node *&child = left != mid ? node->left : node->right;
  if (!child)
    child = new Node();
  insertFunction(newFunction, child, left != mid ? l : m, left != mid ? m : r);
}
```

Notice that the implementation is similar to Dynamic Segment Tree as it is using pointer and it allows a quite wide range interval of query. It is possible to deploy Li Chao Tree using the common array-based to store the node value. However, this comes at the expense of being restricted to a narrower index range.

Then, to determine which child node to traverse to, we simply follow the node that contains the range of the point of query. The implementation is as follows:

```c++
ll query(int x, Node *node = root, int l = L, int r = R) {
  if (!node || l > x || r <= x)
    return INF;
  int m = (l + r) >> 1;
  ll res = node->function.f(x);
  return x < m ? min(res, query(x, node->left, l, m))
               : min(res, query(x, node->right, m, r));
}
```

### Solution

If we try to naively apply the polynomial function, we won't be able to meet the criteria of Li Chao Tree; consequently, this definitely results in *Wrong Answer* verdict. As **melfice** stated in his tutorial post, "a polynomial $y = x^3 + a x^2 + bx + c$ has at most one root greater than $k = \sqrt{\max(|b|, |c|)} + 2$". Proof can be found [here](https://discuss.codechef.com/t/poly-editorial/17335).

This implies that if we only consider $[\sqrt{10^5} + 2, 10^5]$ (instead of $[0, 10^5]$) as our main range, then, we can effectively integrate the polynomial function into the Li Chao Tree. Then, for range $[0, \sqrt{10^5} + 2)$, we can simply update it by iterating it over as $\sqrt{10^5} + 2 \approx 319$.

```c++
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  while (T--) {
    int N, Q;
    cin >> N;
    vector<Function> functions(N);
    for (auto &f : functions)
      cin >> f.d >> f.c >> f.b >> f.a;
    cin >> Q;
    vector<int> t(Q);
    for (auto &x : t)
      cin >> x;

    root = new Node();
    vector<ll> ans(S + 1, INF);

    for (const auto &func : functions) {
      for (int x = 0; x <= S; ++x)
        ans[x] = min(ans[x], func.f(x));
      insertFunction(func);
    }

    for (const auto &x : t)
      cout << (x <= S ? ans[x] : query(x)) << "\n";
  }
  return 0;
}
```

Denote $C$ as $\max(b_{\max}, c_{\max})$. Then, the overall time complexity for the implementation is:

$$
O(N \sqrt{C} + (N + Q) \log (x_{\max} - \sqrt{C}))
$$

My full solution is accessible [here](https://www.codechef.com/viewsolution/1019856771).

### Li Chao Tree on Convex Hull Trick

While it is potent, the traditional Convex Hull Trick comes with a limitation: it requires the gradients to be strictly monotonous. One might adopt a dynamic approach by using $\texttt{std::set}$ instead of $\texttt{std::vector}$; however, this alternative introduces complexities, making it far from straightforward. Li Chao Tree is able to address those problems. If you are not familiar with the Convex Hull Trick yet, I suggest you to read my previous blog first. You can find it [here](https://www.yohandi.me/blog/convex-hull-trick/).

In Convex Hull Trick, we may notice that for all pairs of functions, the number of intersection point is at most once. For affine functions $f_i(x) = m_i x + c_i$ and $f_j(x) = m_j x + c_j$ ($1 \leq i < j \leq n$), the x-coordinate of the intersection point is located at $-\frac{m_j - m_i}{c_j - c_i}$. We may assign $p$ with it and have the required condition of Li Chao Tree satisfied. Thus, the Convex Hull Trick can be implemented using the Li Chao Tree (although with a potential of having extra memory space). If you're curious about the practical application of this concept, you can check out my implementation for the problem discussed in the Convex Hull Trick post [here](https://codeforces.com/contest/1083/submission/222871636).

### References

1. **melfice**, "POLY - Editorial," CodeChef Discussion. https://discuss.codechef.com/t/poly-editorial/17335.

2. **rama_pang**, "[Tutorial] Li Chao Tree Extended," Codeforces. https://codeforces.com/blog/entry/86731.
   

&copy; 2023 Yohandi. All rights reserved.
