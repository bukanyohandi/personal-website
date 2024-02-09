#include <bits/stdc++.h>
using namespace std;
int tc, N, K, V[1000], memo[1001][1000];
int dp(int W, int pos) {
  if (pos >= N)
    return W;
  int &ret = memo[W][pos];
  if (ret != -1)
    return ret;
  ret = dp(W, pos + 1);
  if (W >= V[pos])
    ret = min(ret, dp(W - V[pos], pos + 2));
  return ret;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> tc;
  for (int t = 1; t <= tc; ++t) {
    memset(memo, -1, sizeof(memo));
    cin >> N >> K;
    for (int i = 0; i < N; ++i)
      cin >> V[i];
    cout << "Scenario #" << t << ": " << K - dp(K, 0) << '\n';
  }
}