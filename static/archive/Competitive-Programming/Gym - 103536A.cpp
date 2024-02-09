#include <bits/stdc++.h>
using namespace std;

int N, G;
vector<long long> S;
vector<vector<long long>> dp;

long long cost(int i, int j) { return (j - i + 1) * (S[j] - S[i - 1]); }

void solve(int g, int l, int r, int optl, int optr) {
  if (l > r)
    return;

  int mid = (l + r) / 2;
  long long optVal = LONG_LONG_MAX;
  int optIdx = -1;

  for (int i = optl; i <= min(mid, optr); ++i) {
    long long curVal = dp[g - 1][i - 1] + cost(i, mid);
    if (curVal < optVal) {
      optVal = curVal;
      optIdx = i;
    }
  }

  dp[g][mid] = optVal;

  solve(g, l, mid - 1, optl, optIdx);
  solve(g, mid + 1, r, optIdx, optr);

  return;
}

int main() {
  cin >> N >> G;
  S.resize(N + 1, 0);
  dp.resize(G + 1, vector<long long>(N + 1));

  for (int i = 1; i <= N; ++i) {
    cin >> S[i];
    S[i] += S[i - 1];
  }

  for (int i = 1; i <= G; ++i) {
    dp[i][0] = 0;
  }
  for (int i = 1; i <= N; ++i) {
    dp[1][i] = cost(1, i);
  }

  for (int g = 2; g <= G; ++g) {
    solve(g, 1, N, 1, N);
  }

  cout << dp[G][N] << endl;
}
