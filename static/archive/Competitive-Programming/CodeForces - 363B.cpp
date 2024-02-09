#include <bits/stdc++.h>
using namespace std;
long long data[150005];
int main() {
  long long ans = 0, x, n, k, worst = 999999999;
  cin >> n >> k;
  for (long long i = 1; i <= n; i++) {
    cin >> x;
    data[i] = data[i - 1] + x;
  }
  for (long long i = 0; i <= n - k; i++) {
    if (worst > data[k + i] - data[i]) {
      worst = data[k + i] - data[i];
      ans = i;
    }
  }
  cout << ans + 1 << endl;
}