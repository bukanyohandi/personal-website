#include <bits/stdc++.h>
using namespace std;
bool negatip[155][155];
long long A, B, C, n, m, q, dis[155][155];
int main() {
  while (cin >> n >> m >> q) {
    if (n == 0LL && m == 0LL && q == 0LL)
      return 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        dis[i][j] = 150001;
        negatip[i][j] = false;
      }
      dis[i][i] = 0;
    }
    for (int i = 0; i < m; ++i) {
      cin >> A >> B >> C;
      dis[A][B] = min(dis[A][B], C);
    }
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
          if (dis[i][k] == 150001 || dis[k][j] == 150001)
            continue;
          if (negatip[i][j])
            continue;
          dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
          if (dis[i][j] <= -150001)
            negatip[i][j] = true;
        }
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
          if (dis[i][k] == 150001 || dis[k][j] == 150001)
            continue;
          int tmp = min(dis[i][j], dis[i][k] + dis[k][j]);
          if (tmp != dis[i][j])
            negatip[i][j] = true;
        }
    for (int i = 0; i < q; ++i) {
      cin >> A >> B;
      if (dis[A][B] == 150001) {
        cout << "Impossible" << endl;
      } else if (negatip[A][B]) {
        cout << "-Infinity" << endl;
      } else {
        cout << dis[A][B] << endl;
      }
    }
  }
}