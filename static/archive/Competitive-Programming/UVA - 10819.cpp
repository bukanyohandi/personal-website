#include <bits/stdc++.h>
using namespace std;
int N, M, w[104], v[105], memo[10505][135];
pair<int, int> wv[105];
int solve(int wmax, int idx, bool kebebasan) {
  if (idx > M)
    return 0;
  if (memo[wmax][idx] != -1)
    return memo[wmax][idx];
  if (kebebasan) {
    if (wmax <= N - w[idx] + 200) {
      return memo[wmax][idx] =
                 max(solve(wmax + w[idx], idx + 1, kebebasan) + v[idx],
                     solve(wmax, idx + 1, kebebasan));
    } else {
      return memo[wmax][idx] = solve(wmax, idx + 1, kebebasan);
    }
  } else {
    if (wmax <= N - w[idx]) {
      return memo[wmax][idx] =
                 max(solve(wmax + w[idx], idx + 1, kebebasan) + v[idx],
                     solve(wmax, idx + 1, kebebasan));
    } else if (wmax + w[idx] > 2000 && wmax + w[idx] <= N + 200) {
      kebebasan = true;
      return memo[wmax][idx] =
                 max(solve(wmax + w[idx], idx + 1, kebebasan) + v[idx],
                     solve(wmax, idx + 1, kebebasan));
    } else {
      return memo[wmax][idx] = solve(wmax, idx + 1, kebebasan);
    }
  }
}
int main() {
  while (cin >> N >> M) {
    for (int i = 0; i <= 101; ++i) {
      w[i] = 10001;
      v[i] = 0;
    }
    for (int i = 0; i <= 10401; ++i) {
      for (int j = 0; j <= 101; ++j) {
        memo[i][j] = -1;
      }
    }
    for (int i = 1; i <= M; ++i) {
      cin >> wv[i].first >> wv[i].second;
    }
    sort(wv + 1, wv + 1 + M);
    for (int i = 1; i <= M; ++i) {
      w[i] = wv[i].first;
      v[i] = wv[i].second;
    }
    cout << solve(0, 1, false) << endl;
  }
}
