#include <assert.h>

#include <iostream>
#include <vector>
using namespace std;

class DSU {
public:
  DSU() { __n = 0; }
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

    if (u == v)
      return -1;
    if (sz[u] < sz[v])
      swap(u, v);

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

  int size() { return __n; }

  int size(int x) {
    assert(0 <= x && x < __n);

    return sz[find(x)];
  }

private:
  int __n;
  vector<int> par, sz;
};

struct query {
  int l, r, c;
} queries[200000];

int main() {
  int n, q;
  int ans[200000];

  DSU graph(200001);

  cin >> n >> q;
  for (int i = 0; i < q; ++i) {
    cin >> queries[i].l >> queries[i].r >> queries[i].c;
  }

  for (int i = q - 1; i >= 0; --i) {
    int start = graph.find(queries[i].l - 1) + 1;
    int end = queries[i].r;
    int color = queries[i].c;

    while (start <= end) {
      ans[start - 1] = color;
      graph.setParent(start, start - 1);
      start = graph.find(start - 1) + 1;
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << ans[i] << endl;
  }
}