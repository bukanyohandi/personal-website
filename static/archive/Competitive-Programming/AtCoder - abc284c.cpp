#include <bits/stdc++.h>
using namespace std;

int P[105];

int find(int U) {
  if (P[U] == U)
    return U;
  return P[U] = find(P[U]);
}

int main() {
  int N, M;
  cin >> N >> M;

  for (int i = 1; i <= N; ++i) {
    P[i] = i;
  }

  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    u = find(u);
    v = find(v);
    P[u] = v;
  }

  int ans = 0;
  map<int, bool> visited;
  for (int i = 1; i <= N; ++i) {
    if (visited[find(i)])
      continue;
    visited[find(i)] = true;
    ans++;
  }

  cout << ans << endl;
}