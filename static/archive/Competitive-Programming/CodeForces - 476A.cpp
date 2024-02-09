#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, m;
  cin >> n >> m;
  if (n == 0 && m == 0) {
    cout << 0 << endl;
    return 0;
  }
  if (m == 0) {
    cout << -1 << endl;
    return 0;
  }
  if (m > n) {
    cout << -1 << endl;
    return 0;
  }
  for (int i = (n + 1) / 2; i <= n; ++i) {
    if (i % m == 0) {
      cout << i << endl;
      return 0;
    }
  }
  cout << -1 << endl;
  return 0;
}