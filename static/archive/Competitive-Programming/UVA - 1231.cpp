#include <bits/stdc++.h>
using namespace std;
int tc, t, h, f, x, y, data[2005][2005], dp[2005];
int main() {
  cin >> tc;
  while (tc--) {
    cin >> t >> h >> f;
    for (int i = 0; i < t; ++i) {
      cin >> x;
      for (int j = 0; j < x; ++j) {
        cin >> y;
        data[i][y]++;
      }
    }
    for (int i = h; i >= 0; --i) {
      for (int j = 0; j < t; ++j) {
        if ((i + f) <= h)
          data[j][i] += max(data[j][i + 1], dp[i + f]);
        else
          data[j][i] += data[j][i + 1];
        dp[i] = max(dp[i], data[j][i]);
      }
    }
    cout << dp[0] << endl;
    for (int i = 0; i <= t; ++i) {
      for (int j = 0; j <= h; ++j) {
        dp[j] = data[i][j] = 0;
      }
    }
  }
}