#include <bits/stdc++.h>
using namespace std;
long long wmax, n, w[2005], v[2005], memo[2005][2005];
long long solve(long long wm, long long posisi) {
  if (posisi > n)
    return 0;
  if (memo[wm][posisi] != -1)
    return memo[wm][posisi];
  if (wm >= w[posisi]) {
    return memo[wm][posisi] = max(solve(wm - w[posisi], posisi + 1) + v[posisi],
                                  solve(wm, posisi + 1));
  } else {
    return memo[wm][posisi] = solve(wm, posisi + 1);
  }
}
int main() {
  cin >> wmax >> n;
  for (long long i = 1LL; i <= n; ++i) {
    cin >> w[i] >> v[i];
    for (long long j = 1; j <= 2000; ++j) {
      memo[j][i] = -1;
    }
  }
  cout << solve(wmax, 1) << endl;
}