#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int B, E, P, N, M;
  cin >> B >> E >> P >> N >> M;

  vector<int> edges[N];
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  map<int, vector<int>> distances;
  for (int u : vector<int>{0, 1, N - 1}) {
    queue<int> bfs;
    vector<int> dist(N, INT_MAX);

    bfs.push(u);
    dist[u] = 0;
    while (!bfs.empty()) {
      int u = bfs.front();
      bfs.pop();

      for (int v : edges[u]) {
        if (dist[v] == INT_MAX) {
          dist[v] = dist[u] + 1;
          bfs.push(v);
        }
      }
    }

    distances[u] = dist;
  }

  int ans = INT_MAX;
  for (int i = 0; i < N; ++i) {
    ans = min(ans, distances[0][i] * B + distances[1][i] * E +
                       distances[N - 1][i] * P);
  }

  cout << ans << endl;

  return 0;
}