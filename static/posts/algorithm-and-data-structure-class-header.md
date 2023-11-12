---
title: "Algorithm and Data Structure Class Header Collection"
date: "2023-11-12"
author: "Yohandi"
tags: [algorithm, data-structure, notes, project]
---

Unlike the previous blogs, this space is dedicated purely to my algorithm amd data structure class headers. This ongoing project is an extension of my old archive, which can be found [here](https://github.com/bukanyohandi/Algorithm-Class-Header). Pretty much I will keep updating both the old archive and this showcase every time I make a new class header.

## Dijkstra

An implemented Dijkstra's algorithm in the form of a class. This class is designed with the intention of simplicity for its user when constructing a Dijkstra's algorithm
    
The class is recommended for C++11 or later.

#### Constructor
| Syntax        | Complexity | Description                               |
| ------------- | ---------- | ----------------------------------------- |
| $\texttt{Dijkstra}()$    | $\mathcal{O}(1)$     | Initializes a new empty graph of size $0$.  |
| $\texttt{Dijkstra}(n)$ | $\mathcal{O}(n)$     | Initializes a new empty graph of size $n$.|
    
#### Methods
| Syntax                 | Complexity      | Description                                                    |
| ---------------------- | --------------- | -------------------------------------------------------------- |
| $\texttt{addEdge}(u, v, w)$ | $\mathcal{O}(1)$          | Adds an edge between node $u$ and $v$ with a weight $w$.       |
| $\texttt{distance}(\texttt{source})$     | $\mathcal{O}(V + E \log V)$| Returns a vector of distances between the $\texttt{source}$ and all nodes.|
| $\texttt{getInfinite}()$          | $\mathcal{O}(1)$          | Returns the infinite value.                                    |
| $\texttt{getZero}()$              | $\mathcal{O}(1)$          | Returns the zero value.                                        |
| $\texttt{resize}(n)$            | $\mathcal{O}(n)$          | Resizes the current graph size to $n$.                         |
| $\texttt{setInfinite}(\texttt{val})$     | $\mathcal{O}(1)$          | Sets an infinite value.                                        |
| $\texttt{setZero}(\texttt{val})$         | $\mathcal{O}(1)$          | Sets a zero value.                                             |
| $\texttt{size}()$                 | $\mathcal{O}(1)$          | Returns the number of nodes in class.                          |

## Disjoint-Set Data Structure

An implemented Disjoint-set data structure in the form of a class. This class is designed with the intention of simplicity for its user when constructing the data structure.
    
The class is recommended for C++11 or later.

#### Constructor
| Syntax           | Complexity | Description                                               |
| ---------------- | ---------- | --------------------------------------------------------- |
| $\texttt{DSU()}$            | $\mathcal{O}(1)$     | Initializes a new disjoint-set data structure of size $0$.  |
| $\texttt{DSU(n)}$         | $\mathcal{O}(n)$     | Initializes a new disjoint-set data structure of size $n$.|
    
#### Methods
| Syntax                 | Complexity | Description                                                                                 |
| ---------------------- | ---------- | ------------------------------------------------------------------------------------------- |
| $\texttt{connectedNodes(x)}$    | $\mathcal{O}(n)$     | Returns a vector of nodes that are connected to node $x$ (excluding the node $x$ itself).   |
| $\texttt{find(x)}$              | $\mathcal{O}(\log n)$ | Returns the representation of the group where node $x$ belongs.                             |
| $\texttt{isConnected(u, v)}$  | $\mathcal{O}(\log n)$ | Returns a boolean value indicating the connectivity between node $u$ and $v$.               |
| $\texttt{merge(u, v)}$        | $\mathcal{O}(\log n)$ | Merges groups where node $u$ and $v$ respectively belong and returns the representation.    |
| $\texttt{resize(n)}$            | $\mathcal{O}(n)$     | Resizes the current data structure size to $n$ ($n$ should be larger than the current size).|
| $\texttt{setParent(u, v)}$    | $\mathcal{O}(1)$     | Sets node $u$ as the parent of node $v$.                                                    |
| $\texttt{size()}$                 | $\mathcal{O}(1)$     | Returns the size of the data structure.                                                     |
| $\texttt{size(x)}$              | $\mathcal{O}(\log n)$ | Returns the number of nodes that are connected to node $x$ (including the node $x$ itself). |

`dsu.hpp`:

```c++[collapsible]
#ifndef DSU_HPP
#define DSU_HPP

#include <assert.h>

#include <vector>
using namespace std;

class DSU {
 public:
  DSU() {
    __n = 0;
  }
  DSU(int n) {
    assert(n >= 0);

    __n = n;
    par.resize(n, -1);
    sz.resize(n, 1);
  }

  vector<int> connectedNodes(int x) {
    assert(0 <= x && x < __n);

    vector<int> ret;

    for (int i = 0; i < __n; ++i) {
      if (i != x && isConnected(i, find(x))) {
        ret.push_back(i);
      }
    }

    return ret;
  }

  int find(int x) {
    assert(0 <= x && x < __n);

    if (par[x] == -1) {
      return x;
    }
    par[x] = find(par[x]);
    return par[x];
  }

  bool isConnected(int u, int v) {
    assert(0 <= u && u < __n);
    assert(0 <= v && v < __n);

    return find(u) == find(v);
  }

  int merge(int u, int v) {
    assert(0 <= u && u < __n);
    assert(0 <= v && v < __n);

    u = find(u);
    v = find(v);

    if (u == v) return -1;
    if (sz[u] < sz[v]) swap(u, v);

    setParent(u, v);

    return u;
  }

  void resize(int n) {
    assert(n > __n);

    __n = n;
    par.resize(n, -1);
    sz.resize(n, 1);

    return;
  }

  void setParent(int u, int v) {
    assert(0 <= u && u < __n);
    assert(0 <= v && v < __n);

    sz[u] += sz[v];
    sz[v] = 0;
    par[v] = u;

    return;
  }

  int size() {
    return __n;
  }

  int size(int x) {
    assert(0 <= x && x < __n);

    return sz[find(x)];
  }

 private:
  int __n;
  vector<int> par, sz;
};

#endif  // DSU_HPP
```

`demo.cpp`:

```c++[collapsible]
#include <iostream>

#include "dsu.hpp"

using namespace std;

int main() {
  DSU graph(10);
  graph.merge(0, 2);
  graph.merge(1, 3);
  graph.merge(2, 4);
  cout << graph.isConnected(0, 4) << endl;
  cout << graph.isConnected(0, 3) << endl;
}
```

## Fenwick Tree

An implemented Fenwick tree data structure in the form of a class. This class is designed with the intention of simplicity for its user when constructing the data structure.

The class is recommended for C++11 or later.

#### Constructor
| Syntax           | Complexity | Description                                               |
| ---------------- | ---------- | --------------------------------------------------------- |
| $\texttt{FenwickTree()}$    | $\mathcal{O}(1)$     | Initializes a new fenwick tree data structure of size $0$.  |
| $\texttt{FenwickTree(n)}$ | $\mathcal{O}(n)$     | Initializes a new fenwick tree data structure of size $n$.|
    
#### Methods
| Syntax                 | Complexity | Description                                                    |
| ---------------------- | ---------- | -------------------------------------------------------------- |
| $\texttt{add}(\texttt{index}, \texttt{val})$    | $\mathcal{O}(\log n)$ | Adds $\texttt{val}$ to $\texttt{arr}_{index}$.       |
| $\texttt{clear}()$                | $\mathcal{O}(n)$     | Clears the current data structure.|
| $\texttt{getZero}()$              | $\mathcal{O}(1)$     | Returns the zero value.                                        |
| $\texttt{resize}(n)$            | $\mathcal{O}(n)$     | Resizes the current data structure size to $n$.                         |
| $\texttt{setZero}(\texttt{val})$         | $\mathcal{O}(1)$     | Sets a zero value.                                             |
| $\texttt{size}()$                 | $\mathcal{O}(1)$     | Returns the size of data structure.                          |
| $\texttt{sum}(\texttt{left}, \texttt{right})$   | $\mathcal{O}(\log n)$ | Returns a sum of $\texttt{arr}_{\texttt{left}} + \texttt{arr}_{\texttt{left}+1} + \ldots + \texttt{arr}_{\texttt{right}-1}$|

`fenwick_tree.hpp`:

```c++[collapsible]
#ifndef FENWICK_TREE_HPP
#define FENWICK_TREE_HPP

#include <assert.h>

#include <vector>
using namespace std;

template <class T>
class FenwickTree {
 public:
  FenwickTree() {
    __n = 0;
  }
  FenwickTree(int n) {
    assert(n >= 0);

    __n = n;
    BIT.resize(__n);
  }

  void add(int index, T val) {
    assert(0 <= index && index < __n);
    assert(zeroIsSet == true);

    for (++index; index <= __n; index += index & -index) {
      BIT[index - 1] += val;
    }

    return;
  }

  void clear() {
    fill(BIT.begin(), BIT.end(), zero);

    return;
  }

  T getZero() {
    return zero;
  }

  void resize(int n) {
    assert(n >= 0);

    __n = n;
    BIT.resize(n, zero);

    return;
  }

  void setZero(T val) {
    zero = val;
    zeroIsSet = true;

    return;
  }

  int size() {
    return __n;
  }

  T sum(int left, int right) {
    assert(0 <= left && left < right && right <= __n);
    assert(zeroIsSet == true);

    return sum(right) - sum(left);
  }

 private:
  bool zeroIsSet;
  int __n;
  T zero;
  vector<T> BIT;

  T sum(int right) {
    T ret = zero;
    for (int index = right; index > 0; index -= index & -index) {
      ret += BIT[index - 1];
    }

    return ret;
  }
};

#endif  // FENWICK_TREE_HPP
```

`demo.cpp`:

```c++[collapsible]
#include <iostream>

#include "fenwick_tree.hpp"
using namespace std;

int main() {
  FenwickTree<int> tree(10);
  tree.setZero(0);
  tree.add(5, 2);
  tree.add(6, 3);
  tree.add(7, 4);
  tree.add(9, 10);
  cout << tree.sum(0, 10) << endl;
}
```

## Sparse Table

An implemented sparse table data structure in the form of a class. This class is designed with the intention of simplicity for its user when constructing the data structure.
    
The class is recommended for C++11 or later.

#### Constructor
| Syntax           | Complexity   | Description                                                           |
| ---------------- | ------------ | --------------------------------------------------------------------- |
| $\texttt{SparseTable}(v)$ | $\mathcal{O}(n \log n)$ | Initializes a new sparse table data structure from the given vector $v$.|
    
#### Methods
| Syntax                 | Complexity | Description                                                    |
| ---------------------- | ---------- | -------------------------------------------------------------- |
| $\texttt{query}(\texttt{left}, \texttt{right})$ | $\mathcal{O}(1)$     | Returns $\texttt{func}(v_{\texttt{left}}, v_{\texttt{left} + 1}, \ldots, v_{\texttt{right} - 1}$) |

`sparse_table.hpp`:

```c++[collapsible]
#ifndef SPARSE_TABLE_HPP
#define SPARSE_TABLE_HPP

#include <assert.h>
#include <math.h>

#include <vector>
using namespace std;

template <class T, T (*op)(T, T)>
class SparseTable {
 public:
  SparseTable(vector<T> v) {
    __n = (int)v.size();

    table.push_back(v);
    for (int j = 1; (1 << j) <= __n; ++j) {
      vector<T> tmp(__n);

      for (int i = 0; (i + (1 << j) - 1) < __n; ++i) {
        tmp[i] = op(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
      }
      table.push_back(tmp);
    }
  }

  T query(int left, int right) {
    assert(0 <= left && left < right && right <= __n);

    int lg = (int)log2(right - left);
    return op(table[lg][left], table[lg][right - (1 << lg)]);
  }

 private:
  int __n;
  vector<vector<T>> table;
};

#endif  // SPARSE_TABLE_HPP
```

`demo.cpp`:

```c++[collapsible]
#include <iostream>

#include "sparse_table.hpp"

using namespace std;

int min(int a, int b) {
  return a < b ? a : b;
}

int main() {
  SparseTable<int, min> table({1, 3, 4, 2, 5});
  cout << table.query(0, 5) << endl;
  cout << table.query(1, 3) << endl;
  cout << table.query(3, 5) << endl;
}
```


