#include <bits/stdc++.h>
using namespace std;
long long solve(long long x) {
  long long tmp = 1;
  if (x % 2 == 0) {
    tmp *= 2;
    while (x % 2 == 0)
      x /= 2;
  }
  for (long long i = 3; i * i <= x; ++i) {
    if (x % i == 0) {
      tmp *= i;
      while (x % i == 0)
        x /= i;
    }
  }
  if (x > 1)
    tmp *= x;
  return tmp;
}
int main() {
  long long n;
  cin >> n;
  cout << solve(n) << endl;
}