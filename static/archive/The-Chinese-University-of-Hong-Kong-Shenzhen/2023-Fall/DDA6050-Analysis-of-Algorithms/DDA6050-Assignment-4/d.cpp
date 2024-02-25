/*
    Author: Yohandi
    Problem Title: Art Gallery Rearrangement
    Problem Link: http://oj.cuhk.edu.cn/problem/dda6050a4q42023fall
*/

#include <bits/stdc++.h>
using namespace std;

/*
    Maxflow Template: https://github.com/ekzhang/library/blob/master/maxflow.cpp
*/
template <int V, class T = long long> class max_flow {
  static const T INF = numeric_limits<T>::max();

  unordered_map<int, T> cap[V];
  int dist[V];
  bool blocked[V];

  void bfs(int s) {
    memset(dist, -1, sizeof dist);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int n = q.front();
      q.pop();
      for (auto p : cap[n]) {
        if (p.second && dist[p.first] == -1) {
          dist[p.first] = dist[n] + 1;
          q.push(p.first);
        }
      }
    }
  }

  T augment(int n, T amt, int t) {
    if (n == t)
      return amt;
    if (blocked[n])
      return 0;
    T remaining = amt;
    for (auto p : cap[n]) {
      if (dist[p.first] != dist[n] + 1)
        continue;
      T flowpart = min(remaining, cap[n][p.first]);
      if (flowpart) {
        T cur = augment(p.first, flowpart, t);
        remaining -= cur;
        cap[n][p.first] -= cur;
        cap[p.first][n] += cur;
      }
    }
    if (remaining)
      blocked[n] = true;
    return amt - remaining;
  }

public:
  void add(int u, int v, T f = 1) { cap[u][v] += f; }

  T calc(int s, int t) {
    T ans = 0;
    while (true) {
      bfs(s);
      memset(blocked, false, sizeof blocked);
      T aug = augment(s, INF, t);
      if (!aug)
        break;
      ans += aug;
    }
    return ans;
  }

  void clear() {
    for (int i = 0; i < V; i++) {
      cap[i].clear();
    }
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  const int MAX_N = 200;

  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    int n;
    cin >> n;

    max_flow<MAX_N + 2> network;

    int source = 0, sink = 2 * n + 1;

    for (int i = 1; i <= n; ++i) {
      network.add(source, i);
      network.add(n + i, sink);
    }

    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        int cell;
        cin >> cell;
        if (cell == 1) {
          network.add(i, n + j);
        }
      }
    }

    cout << (vector<string>{"No", "Yes"})[network.calc(source, sink) == n]
         << "\n";
  }

  return 0;
}
