#include <bits/stdc++.h>
using namespace std;
int K, N, V[505], W[505];
map<pair<int, int>, int> memo;
int dp(int We, int pos) {
  if (pos == N)
    return 0;
  int &ret = memo[{We, pos}];
  if (ret != 0)
    return ret;
  ret = 0;
  if (We >= W[pos])
    ret = max(ret, V[pos] + dp(We - W[pos], pos + 1));
  return ret = max(ret, dp(We, pos + 1));
}
int main() {
  cin >> K >> N;
  for (int i = 0; i < N; ++i)
    cin >> V[i] >> W[i];
  cout << dp(K, 0) << '\n';
}