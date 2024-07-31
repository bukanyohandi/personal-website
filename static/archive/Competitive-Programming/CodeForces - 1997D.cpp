#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a, p, depth;
vector<vector<int>> edges, ord, info;

void dfs(int p, int u) {
  if (u != 0)
    depth[u] = depth[p] + 1;
  for (auto v : edges[u])
    dfs(u, v);
}

int main() {
  int tc;
  cin >> tc;

  for (int t = 0; t < tc; ++t) {
    cin >> n;

    a.clear();
    p.clear();
    depth.clear();
    edges.clear();
    ord.clear();
    info.clear();

    a.resize(n);
    for (auto &e : a) {
      cin >> e;
    }

    edges.resize(n);

    p.resize(n);
    for (int i = 1; i < n; ++i) {
      cin >> p[i];
      p[i]--;
      edges[p[i]].push_back(i);
    }

    depth.resize(n);
    depth[0] = 0;

    dfs(-1, 0);

    ord.resize(n);
    info.resize(n);

    int mx = -1;
    for (int i = 0; i < n; ++i) {
      ord[depth[i]].push_back(i);
      mx = max(mx, depth[i]);
    }

    for (int i = mx; i >= 0; --i) {
      //   cout << "depth " << i << endl;
      for (auto v : ord[i]) {
        if (i == mx) {
          info[p[v]].push_back(a[v]);
        } else if (i != 0) {
          int mn = INT_MAX;
          for (auto vv : info[v]) {
            mn = min(mn, vv);
          }
          if (mn == INT_MAX)
            mn = a[v];
          //   cout << "for " << v << " consider " << mn << " and " << a[v] <<
          //   endl;
          if (a[v] >= mn) {
            a[v] = mn;
          } else {
            a[v] += (mn - a[v]) / 2;
          }
          //   a[v] += mn;
          //   cout << "we set " << a[v] << endl;
          // cout << p[v] << " " << a[v] << "<<" << endl;
          info[p[v]].push_back(a[v]);
        } else {
          int mn = INT_MAX;
          for (auto vv : info[v]) {
            mn = min(mn, vv);
          }
          a[0] += mn;
        }
      }
    }

    // cout << "final:\n";
    cout << a[0] << endl;
  }

  return 0;
}