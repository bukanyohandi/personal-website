#include <bits/stdc++.h>
using namespace std;

int main() {
  long long N;
  cin >> N;
  if (N % 2 == 1) {
    cout << 0 << endl;
  } else {
    long long ans = 0;
    long long piv = 10;
    while (piv <= N) {
      ans += N / piv;
      piv *= 5;
    }
    cout << ans << endl;
  }
}