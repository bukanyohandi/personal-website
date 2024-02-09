#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000;

bool visited[MAXN + 5];
vector<int> edges[MAXN + 5];

int ans = 0;

void dfs(int u) {
  ans++;
  if (ans == 1000000)
    return;

  for (int i = 0; i < edges[u].size(); ++i) {
    int v = edges[u][i];
    if (visited[v])
      continue;

    visited[v] = true;
    dfs(v);
    visited[v] = false;

    if (ans == 1000000)
      return;
  }

  return;
}

int main() {
  int N, M;
  cin >> N >> M;

  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  visited[1] = true;
  dfs(1);
  cout << ans << endl;
}