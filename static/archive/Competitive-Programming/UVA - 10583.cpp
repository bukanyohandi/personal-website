#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50000;

int P[MAXN + 5];

int find(int u) {
  if (P[u] == u)
    return u;
  return P[u] = find(P[u]);
}

int main() {
  int N, M;
  int tc = 1;

  while (cin >> N >> M) {
    if (N == 0 && M == 0)
      break;

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
    set<int> st;

    for (int i = 1; i <= N; ++i) {
      st.insert(find(i));
    }

    cout << "Case " << tc++ << ": " << (int)st.size() << endl;
  }

  return 0;
}