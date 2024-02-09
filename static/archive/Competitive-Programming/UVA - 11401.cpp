#include <bits/stdc++.h>
using namespace std;
long long f[1000005];
int main() {
  f[0] = 0;
  for (long long i = 1; i <= 1000000; ++i) {
    f[i] = (i * (i + 1)) / 2;
    if (i > 2)
      f[i] += f[i - 2];
  }
  long long n;
  while (cin >> n) {
    if (n < 3)
      return 0;
    n -= 3;
    cout << f[n] << endl;
  }
}