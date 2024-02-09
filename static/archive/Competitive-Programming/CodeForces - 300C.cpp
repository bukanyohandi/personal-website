#include <iostream>
using namespace std;

const long long MOD = 1000000007;

int a, b, n;
long long ans;
static long long factorial[1048576];

long long power(long long a, long long b) {
  if (b == 0)
    return 1;
  long long tmp = power(a, b / 2);
  return (tmp * tmp % MOD) * (b % 2 == 0 ? 1 : a) % MOD;
}

long long combination(int n, int r) {
  if (r == 0 || n == r)
    return 1;
  return (factorial[n] * power(factorial[n - r], MOD - 2) % MOD) *
         power(factorial[r], MOD - 2) % MOD;
}

bool isGood(int number) {
  while (number > 0) {
    if ((number % 10 != a) && (number % 10 != b)) {
      return false;
    }
    number /= 10;
  }
  return true;
}

void precompute() {
  factorial[0] = 1;
  for (int i = 0; i < n; ++i) {
    factorial[i + 1] = factorial[i] * (i + 1) % MOD;
  }
}

int main() {
  cin >> a >> b >> n;

  precompute();

  for (int i = 0; i < (n + 1); ++i) {
    if (isGood(i * a + (n - i) * b)) {
      ans += combination(n, i);
      ans %= MOD;
    }
  }

  cout << ans << endl;
}