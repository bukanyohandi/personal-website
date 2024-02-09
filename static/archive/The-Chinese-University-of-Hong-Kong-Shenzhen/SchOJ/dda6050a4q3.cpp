#include <bits/stdc++.h>
using namespace std;

#define MAX_NODES 100005
#define MAX_EDGES 200005
#define INF 0x3f3f3f3f

using namespace std;

struct Edge {
  int to, cap, rev;
};
vector<Edge> G[MAX_NODES];
int level[MAX_NODES];
int iter[MAX_NODES];

int n, m, s, t;

void add_edge(int from, int to, int cap) {
  G[from].push_back((Edge){to, cap, (int)G[to].size()});
  G[to].push_back((Edge){from, 0, (int)G[from].size() - 1});
}

void bfs(int s) {
  memset(level, -1, sizeof(level));
  queue<int> que;
  level[s] = 0;
  que.push(s);
  while (!que.empty()) {
    int v = que.front();
    que.pop();
    for (int i = 0; i < G[v].size(); i++) {
      Edge &e = G[v][i];
      if (e.cap > 0 && level[e.to] < 0) {
        level[e.to] = level[v] + 1;
        que.push(e.to);
      }
    }
  }
}

int dfs(int v, int t, int f) {
  if (v == t) {
    return f;
  }
  for (int &i = iter[v]; i < G[v].size(); i++) {
    Edge &e = G[v][i];
    if (e.cap > 0 && level[v] < level[e.to]) {
      int d = dfs(e.to, t, min(f, e.cap));
      if (d > 0) {
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow(int s, int t) {
  int flow = 0;
  for (;;) {
    bfs(s);
    if (level[t] < 0) {
      return flow;
    }
    memset(iter, 0, sizeof(iter));
    int f;
    while ((f = dfs(s, t, INF)) > 0) {
      flow += f;
    }
  }

  return flow;
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    add_edge(a, n + 1 + b, 1);
  }

  for (int i = 1; i <= n; ++i) {
    add_edge(0, i, 1);
    add_edge(n + 1 + i, n + 1, 1);
  }

  s = 0;
  t = n + 1;
  cout << n - max_flow(s, t) << endl;

  return 0;
}
