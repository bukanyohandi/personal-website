#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;

  vector<pair<int, int>> edges[N];
  for (int i = 0; i < M; ++i) {
    int a, b, c;
    cin >> a >> b >> c;

    --a;
    --b;
    edges[a].push_back({b, c});
    edges[b].push_back({a, c});
  }

  int ans = INT_MAX;
  vector<int> dist(N);
  function<void(int, int, int, int)> dfs = [&](int id, int u, int v,
                                               int current_length) {
    if (ans < current_length)
      return;
    if (dist[v] < current_length)
      return;
    if (u != v)
      dist[v] = current_length;
    if (id == v && ans > dist[v]) {
      ans = dist[v];
    }
    for (auto p : edges[v]) {
      if (p.first == u)
        continue;
      dfs(id, v, p.first, current_length + p.second);
    }
  };
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      dist[j] = INT_MAX;
    }
    dfs(i, i, i, 0);
  }

  cout << ans << endl;

  return 0;
}
