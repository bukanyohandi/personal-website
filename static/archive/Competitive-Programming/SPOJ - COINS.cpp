#include <bits/stdc++.h>
using namespace std;
unordered_map<long long, long long> memo;
long long solve(long long x) {
  if (x <= 4)
    return x;
  if (memo[x] != 0)
    return memo[x];
  return memo[x] = max(x, solve(x / 2) + solve(x / 3) + solve(x / 4));
}
int main() {
  long long n;
  while (cin >> n) {
    cout << solve(n) << endl;
  }
}