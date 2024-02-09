#include <bits/stdc++.h>
using namespace std;
long long tc, n, dp[2000005], data[1000005];
int main() {
  for (int i = 1; i <= 2000005; ++i) {
    int tmp = i, ganjil = 0, genap = 0;
    while (tmp > 0) {
      if (tmp % 2 == 0)
        genap += tmp % 10;
      else
        ganjil += tmp % 10;
      tmp /= 10;
    }
    dp[i] = dp[i - 1] + abs(ganjil - genap);
  }
  for (int i = 1; i <= 1000000; ++i) {
    data[i] = data[i - 1] + dp[i * 2] + dp[i * 2 - 1] - 2 * dp[i];
  }
  cin >> tc;
  while (tc--) {
    cin >> n;
    cout << data[n] << endl;
  }
}

// hi