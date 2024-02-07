#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;

  struct edge {
    int u, v, w, id;
  } edges[m];

  for (int i = 0; i < m; ++i) {
    cin >> edges[i].u >> edges[i].v >> edges[i].w;
    --edges[i].u;
    --edges[i].v;
    edges[i].id = i;
  }

  int target_id;
  cin >> target_id;
  --target_id;

  int U, V;
  U = edges[target_id].u;
  V = edges[target_id].v;

  sort(edges.begin(), edges.end(),
       [](const edge &a, const edge &b) { return a.w < b.w; });

  vector<int> parent(n);
  iota(parent.begin(), parent.end());
  const auto find = [](int x) {
    if (parent[x] == x)
      return x;
    return parent[x] = find(parent[x]);
  };

  int ans = -1;
  for (int i = 0; i < m; ++i) {
    if (target_id == edges[i].id)
      continue;

    int u, v, w, id;
    u = edges[i].u;
    v = edges[i].v;
    w = edges[i].w;
    id = edges[i].id;

    u = find(u);
    v = find(v);
    if (u == v)
      continue;

    parent[u] = v;
    if (find(U))
  }
}