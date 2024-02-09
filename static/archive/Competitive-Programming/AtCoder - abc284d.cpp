#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
  int T;
  cin >> T;

  vector<bool> isPrime(100001, 1);
  isPrime[1] = false;
  for (int i = 2; i <= 100000; ++i) {
    if (!isPrime[i])
      continue;
    for (int j = i + i; j <= 100000; j += i) {
      isPrime[j] = false;
    }
  }

  for (int tc = 0; tc < T; ++tc) {
    long long N;
    cin >> N;

    bool found = false;

    for (int i = 2; i <= 100000; ++i) {
      if (isPrime[i]) {
        if ((N % i == 0) && (N % (i * i) == 0)) {
          cout << i << " " << N / (i * i) << endl;
          found = true;
          break;
        } else if ((N % i == 0)) {
          cout << sqrt(N / i) << " " << i << endl;
          found = true;
          break;
        }
      }
    }

    if (found)
      continue;

    long long p;
    for (p = 2; p * p <= (N / 100000); p += (p % 2) + 1) {
      if ((N % p == 0) && (N % (p * p) == 0)) {
        found = true;
        break;
      }
    }

    assert(found == true);

    cout << p << " " << N / (p * p) << endl;
  }
}