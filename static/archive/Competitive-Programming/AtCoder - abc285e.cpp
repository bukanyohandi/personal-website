#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<long long> a(n + 1), b(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    b[i] = b[i - 1] + a[(i + 1) / 2];
  }
  vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, -4e18));
  dp[1][0] = 0;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= n; j++) {
      if (dp[i][j] < 0) {
        continue;
      }
      dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j]);
      dp[i + 1][0] = max(dp[i + 1][0], dp[i][j] + b[j]);
    }
  }
  long long res = 0;
  for (int i = 0; i < n; i++) {
    res = max(res, dp[n][i] + b[i]);
  }
  cout << res << "\n";
  return 0;
}