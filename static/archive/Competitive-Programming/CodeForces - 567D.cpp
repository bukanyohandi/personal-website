#include <bits/stdc++.h>
using namespace std;
int n, k, a, m, ships, l, r;
int x[200000];
set<int> points;
int numberOfShips(int length) { return (length + 1) / (a + 1); }
int main() {
  cin >> n >> k >> a;
  cin >> m;
  for (int i = 0; i < m; ++i)
    cin >> x[i];
  points.insert(0);
  points.insert(n + 1);
  ships += numberOfShips(n);
  for (int i = 0; i < m; ++i) {
    auto it = points.lower_bound(x[i]);
    r = *it;
    l = *--it;
    ships -= numberOfShips(r - l - 1);
    ships += numberOfShips(x[i] - l - 1);
    ships += numberOfShips(r - x[i] - 1);
    if (ships < k) {
      cout << i + 1 << endl;
      return 0;
    }
    points.insert(x[i]);
  }
  cout << -1 << endl;
  return 0;
}