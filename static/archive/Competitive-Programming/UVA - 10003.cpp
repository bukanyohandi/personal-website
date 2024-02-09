#include <bits/stdc++.h>
using namespace std;
int memo[55][55], data[55], n, m;
int cutting(int le, int ri) {
  if (le + 1 == ri)
    return 0;
  if (memo[le][ri] != -1)
    return memo[le][ri];
  int ret = 1e9;
  for (int i = le + 1; i <= ri - 1; ++i) {
    ret = min(ret, cutting(le, i) + cutting(i, ri));
  }
  return memo[le][ri] = ret + data[ri] - data[le];
}
int main() {
  while (cin >> n) {
    if (n == 0)
      return 0;
    cin >> m;
    memset(memo, -1, sizeof memo);
    for (int i = 1; i <= m; ++i) {
      cin >> data[i];
    }
    data[m + 1] = n;
    cout << "The minimum cutting is " << cutting(0, m + 1) << "." << endl;
  }
}