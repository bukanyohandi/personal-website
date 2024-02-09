#include <bits/stdc++.h>
using namespace std;
int tmp, T, B, X, Dp[1000005], Arr[1000005];
int main() {
  cin >> T;
  for (int i = 0; i < T; ++i) {
    cin >> tmp;
    Arr[tmp]++;
    B = max(B, tmp);
  }
  for (int i = 1; i < 1000005 && !X; ++i)
    if (Arr[i] != i * 4)
      X = i;
  for (int n = 1; n <= T; ++n) {
    if (T % n)
      continue;
    int m = T / n, Y = n + m - X - B;
    if (abs(n - X) + abs(m - Y) != B)
      continue;
    memset(Dp, 0, sizeof(Dp));
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        Dp[abs(X - i) + abs(Y - j)]++;
    int Test;
    for (Test = 0; Test <= n + m; ++Test)
      if (Dp[Test] != Arr[Test])
        break;
    if (Test > n + m) {
      cout << n << " " << m << endl;
      cout << X << " " << Y << endl;
      return 0;
    }
  }
  cout << -1 << endl;
}