#include <iostream>
using namespace std;

const int MOD = 1000000007;

int queries, x, k;
static int f[64];

int precompute() {
  f[0] = 1;
  f[1] = 2;

  int index = 2;
  while (f[index - 1] <= 1e9) {
    f[index] = f[index - 1] + f[index - 2];
    index += 1;
  }

  return index - 1;
}

long long solve(int x, int k, int index) {
  if (x == 0 && k == 0)
    return 1;
  if (x == 0 && k != 0)
    return 0;
  if (x < 0)
    return 0;
  if (x > 0 && k == 0)
    return 0;
  if ((long long)x > (long long)f[index] * k)
    return 0;
  return (solve(x - f[index], k - 1, index) + solve(x, k, index - 1)) % MOD;
}

int main() {
  int start = precompute();

  cin >> queries;
  for (int q = 0; q < queries; ++q) {
    cin >> x >> k;
    cout << solve(x, k, start) << endl;
  }
}