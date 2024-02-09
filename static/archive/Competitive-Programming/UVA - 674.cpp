#include <bits/stdc++.h>
using namespace std;
int memo[7500][10], koin[5] = {1, 5, 10, 25, 50};
int solve(int coin, int idx) {
  if (idx >= 5 || coin < 0)
    return 0;
  if (coin == 0)
    return 1;
  if (memo[coin][idx] != -1)
    return memo[coin][idx];
  return memo[coin][idx] = solve(coin - koin[idx], idx) + solve(coin, idx + 1);
}
int main() {
  int n;
  for (int i = 1; i <= 7500; ++i) {
    for (int j = 0; j <= 4; ++j) {
      memo[i][j] = -1;
    }
  }
  while (cin >> n) {
    cout << solve(n, 0) << endl;
  }
}