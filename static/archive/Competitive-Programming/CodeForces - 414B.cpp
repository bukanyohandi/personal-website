#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1000000007;

int dp[2005][2005];

signed main() {
  int n, k;
  cin >> k >> n;

  for (int j = 1; j <= 2000; ++j) {
    dp[1][j] = 1;
  }

  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j <= k; ++j) {
      for (int l = j; l <= k; l = l + j) {
        dp[i][l] += dp[i - 1][j];
        dp[i][l] %= MOD;
      }
    }
  }

  int ans = 0;
  for (int j = 1; j <= k; ++j) {
    ans += dp[n][j];
    ans %= MOD;
  }

  cout << ans << endl;
}