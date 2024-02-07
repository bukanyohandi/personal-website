#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int N;
  cin >> N;

  vector<int> IDs(N);
  for (int i = 0; i < N; ++i) {
    cin >> IDs[i];
  }

  struct edge {
    int u, v, w;
  };
  auto compare = [&](const edge &a, const edge &b) { return a.w < b.w; };

  priority_queue<edge, vector<edge>, decltype(compare)> edges(compare);
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      edge current_edge;
      current_edge.u = i;
      current_edge.v = j;
      current_edge.w = IDs[i] ^ IDs[j];

      edges.push(current_edge);
    }
  }

  vector<int> parent(N), rank(N, 0);
  iota(parent.begin(), parent.end(), 0);

  function<int(int)> find = [&](int u) -> int {
    if (parent[u] == u)
      return u;
    return parent[u] = find(parent[u]);
  };
  auto connect = [&](int u, int v) {
    u = find(u);
    v = find(v);

    if (rank[u] > rank[v])
      swap(u, v);

    parent[u] = v;
    rank[v] += rank[u];
    rank[u] = 0;
    return;
  };

  long long ans = 0;
  while (!edges.empty()) {
    edge current_edge = edges.top();
    edges.pop();

    int u = current_edge.u;
    int v = current_edge.v;
    int w = current_edge.w;

    if (find(u) == find(v))
      continue;

    ans += (long long)w;
    connect(u, v);
  }

  cout << ans << endl;

  return 0;
}