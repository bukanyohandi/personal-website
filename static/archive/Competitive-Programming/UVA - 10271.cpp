#include <bits/stdc++.h>
using namespace std;
int T, N, K, we[5005], co[5005], dp[5005];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> K >> N;
    K += 8;
    for (int i = N; i >= 1; --i)
      cin >> we[i];
    for (int i = 2; i <= N; ++i)
      co[i] = (we[i] - we[i - 1]) * (we[i] - we[i - 1]);
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= K; ++i) {
      for (int j = N; j >= i * 3; --j)
        dp[j] = dp[j - 2] + co[j];
      for (int j = i * 3 + 1; j <= N; ++j)
        dp[j] = min(dp[j], dp[j - 1]);
    }
    cout << dp[N] << '\n';
  }
}
