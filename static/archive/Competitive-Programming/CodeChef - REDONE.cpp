#include <bits/stdc++.h>
using namespace std;
long long tc, n, data[1000005];
int main() {
  data[1] = 1;
  for (long long i = 2; i <= 1000000; ++i) {
    data[i] =
        ((data[i - 1] % 1000000007 * (i + 1)) % 1000000007 + i % 1000000007) %
        1000000007;
  }
  cin >> tc;
  while (tc--) {
    cin >> n;
    cout << data[n] << endl;
  }
}