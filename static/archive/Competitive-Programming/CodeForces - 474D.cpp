#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1000000007;

int dp[2][100005];
int pref[100005];

signed main() {
  int t, k;
  cin >> t >> k;

  dp[0][1] = 1;
  dp[1][k] = 1;
  for (int i = 2; i <= 100000; ++i) {
    dp[0][i] = (dp[0][i - 1] + dp[1][i - 1]) % MOD;
    if (i - k >= 1)
      dp[1][i] = (dp[0][i - k] + dp[1][i - k]) % MOD;
  }

  for (int i = 1; i <= 100000; ++i) {
    pref[i] += pref[i - 1];
    pref[i] += dp[0][i];
    pref[i] += dp[1][i];
    pref[i] %= MOD;
  }

  for (int i = 0; i < t; ++i) {
    int a, b;
    cin >> a >> b;
    cout << (pref[b] - pref[a - 1] + MOD) % MOD << endl;
  }

  //   for (int i = 1; i <= 10; ++i) {
  //     cerr << i << ": " << dp[0][i] << endl;
  //   }
  //   for (int i = 1; i <= 10; ++i) {
  //     cerr << i << ": " << dp[1][i] << endl;
  //   }
}