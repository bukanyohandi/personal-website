#include <bits/stdc++.h>
using namespace std;

bool visited[200005];
vector<int> edges[200005];

int dfs(int u) {
  visited[u] = true;

  for (int i = 0; i < edges[u].size(); ++i) {
    if (visited[edges[u][i]])
      continue;
    return dfs(edges[u][i]);
  }

  return u;
}

int main() {
  int N, M;
  vector<int> deg_in, u, v;

  cin >> N >> M;
  deg_in.resize(N);
  u.resize(M);
  v.resize(M);

  for (int i = 0; i < N; ++i) {
    deg_in[i] = 0;
  }

  for (int i = 0; i < M; ++i) {
    cin >> u[i] >> v[i];
    u[i]--;
    v[i]--;
    edges[u[i]].push_back(v[i]);
    edges[v[i]].push_back(u[i]);
    deg_in[u[i]]++;
    deg_in[v[i]]++;
  }

  int deg_one = 0;
  int deg_two = 0;
  vector<int> vv;

  for (int i = 0; i < N; ++i) {
    if (deg_in[i] == 1) {
      deg_one++;
      vv.push_back(i);
    } else if (deg_in[i] == 2) {
      deg_two++;
    }
  }

  bool connected = true;

  if (deg_one == 2 && deg_two == N - 2 && dfs(vv[0]) == vv[1]) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }

  //   cerr << deg_one << " " << deg_two << endl;
}