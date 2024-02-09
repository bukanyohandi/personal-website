#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> edges[N];

  for (int i = 0; i < N; ++i) {
    int sz;
    cin >> sz;
    for (int j = 0; j < sz; ++j) {
      int v;
      cin >> v;

      edges[i].push_back(v);
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int source;
    cin >> source;

    bool visited[N];
    memset(visited, false, sizeof(visited));

    queue<int> bfs;
    int sz;

    bfs.push(source);
    visited[source] = true;

    int ans = -1;
    int ans2 = -1;
    int day = 0;

    while (!bfs.empty()) {
      sz = (int)bfs.size();

      if (bfs.front() != source && ans < sz) {
        ans = sz;
        ans2 = day;
      }

      for (int i = 0; i < sz; ++i) {
        int u = bfs.front();
        bfs.pop();

        for (auto v : edges[u]) {
          if (!visited[v]) {
            bfs.push(v);
            visited[v] = true;
          }
        }
      }

      day++;
    }

    if (ans == -1) {
      cout << 0 << endl;
    } else {
      cout << ans << " " << ans2 << endl;
    }
  }
}