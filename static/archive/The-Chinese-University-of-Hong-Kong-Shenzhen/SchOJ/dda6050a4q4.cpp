#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;

class MaxFlow {
private:
  int residualGraph[MAXN][MAXN];
  bool visited[MAXN];
  int parent[MAXN];
  int V;

  bool dfs(int s, int t) {
    std::memset(visited, 0, sizeof(visited));
    std::vector<int> stack;
    stack.push_back(s);
    visited[s] = true;
    parent[s] = -1;

    while (!stack.empty()) {
      int u = stack.back();
      stack.pop_back();

      for (int v = 0; v < V; v++) {
        if (!visited[v] && residualGraph[u][v] > 0) {
          stack.push_back(v);
          parent[v] = u;
          visited[v] = true;
        }
      }
    }
    return visited[t];
  }

public:
  MaxFlow(int vertices) : V(vertices) {
    std::memset(residualGraph, 0, sizeof(residualGraph));
  }

  void addEdge(int u, int v, int w) { residualGraph[u][v] += w; }

  int fordFulkerson(int s, int t) {
    int max_flow = 0;

    while (dfs(s, t)) {
      int path_flow = INT_MAX;
      for (int v = t; v != s; v = parent[v]) {
        int u = parent[v];
        path_flow = std::min(path_flow, residualGraph[u][v]);
      }

      for (int v = t; v != s; v = parent[v]) {
        int u = parent[v];
        residualGraph[u][v] -= path_flow;
        residualGraph[v][u] += path_flow;
      }

      max_flow += path_flow;
    }

    return max_flow;
  }
};

int main() {
  int n, m, e;
  cin >> n >> m >> e;

  vector<int> u(m), v(m), w(m);
  for (int i = 0; i < m; ++i) {
    cin >> u[i] >> v[i] >> w[i];
  }

  MaxFlow mf(n);
  for (int i = 0; i < m; ++i) {
    if (i != e) {
      mf.addEdge(u[i], v[i], max(0, w[e] - w[i] + 1));
      mf.addEdge(v[i], u[i], max(0, w[e] - w[i] + 1));
    }
  }

  cout << mf.fordFulkerson(u[e], v[e]) << endl;

  return 0;
}