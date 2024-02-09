#include <bits/stdc++.h>
using namespace std;
long long ans, c0, c1, pow2[55], n, m, data[55][55];
int main() {
  pow2[0] = 1;
  for (int i = 1; i <= 50; ++i) {
    pow2[i] = pow2[i - 1] * 2;
  }
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    c0 = c1 = 0;
    for (int j = 1; j <= m; ++j) {
      cin >> data[i][j];
      if (data[i][j])
        c1++;
      else
        c0++;
    }
    ans += pow2[c1] + pow2[c0] - 2;
  }
  for (int i = 1; i <= m; ++i) {
    c0 = c1 = 0;
    for (int j = 1; j <= n; ++j) {
      if (data[j][i])
        c1++;
      else
        c0++;
    }
    ans += pow2[c1] + pow2[c0] - 2;
  }
  cout << ans - n * m << endl;
}