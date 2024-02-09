/*
** The holy #include <bits/stdc++.h>
*/
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

#define endl '\n'
const double PI = 3.14159265358979323846;
using namespace std;
inline void boost() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}
int r1, r2, x3, y3, r3, n, ans = 0;
int main() {
  boost();
  cin >> r1 >> r2;
  r2 = r1 - r2;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> x3 >> y3 >> r3;
    if (((x3 * x3 + y3 * y3) >= (r2 + r3) * (r2 + r3)) &&
        ((x3 * x3 + y3 * y3) <= (r1 - r3) * (r1 - r3)))
      ans++;
  }
  cout << ans << endl;
}