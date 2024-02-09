#include <bits/stdc++.h>
using namespace std;

int cnt = 1;
map<int, string> inv_hashh;
map<string, int> hashh;

bool ans = true;

bool visited[200005];
vector<int> edges[200005];

void dfs(int u) {
  for (int i = 0; i < edges[u].size(); ++i) {
    int v = edges[u][i];
    if (visited[v]) {
      ans = false;
      return;
    }
    visited[v] = true;
    dfs(v);
  }

  return;
}

int main() {
  int N;
  cin >> N;

  vector<string> S(N), T(N);
  vector<int> in_deg(200005, 0);
  for (int i = 0; i < N; ++i) {
    cin >> S[i] >> T[i];
    if (hashh[S[i]] == 0) {
      hashh[S[i]] = cnt;
      cnt++;
    }
    if (hashh[T[i]] == 0) {
      hashh[T[i]] = cnt;
      cnt++;
    }

    edges[hashh[S[i]]].push_back(hashh[T[i]]);
    in_deg[hashh[T[i]]]++;
  }

  for (int i = 1; i < cnt; ++i) {
    if (in_deg[i] == 0) {
      visited[i] = true;
      dfs(i);
    }
  }

  for (int i = 1; i < cnt; ++i) {
    if (visited[i] == false && in_deg[i] > 0) {
      ans = false;
    }
  }

  if (ans) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}