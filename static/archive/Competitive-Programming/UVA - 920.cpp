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
int n, tc;
pair<double, double> koord[1005];
double ans, pivx = 0, pivy = 0;
double jarak(double x1, double x2, double y1, double y2) {
  return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}
int main() {
  cin >> tc;
  while (tc--) {
    ans = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> koord[i].first >> koord[i].second;
    }
    sort(koord + 1, koord + 1 + n);
    pivy = koord[n].second;
    for (int i = n; i > 1; --i) {
      if (pivy < koord[i - 1].second) {
        pivx = koord[i].first - ((koord[i].second - pivy) /
                                 (koord[i].second - koord[i - 1].second)) *
                                    (koord[i].first - koord[i - 1].first);
        ans += jarak(pivx, koord[i - 1].first, pivy, koord[i - 1].second);
        pivy = koord[i - 1].second;
      }
    }
    cout << fixed << setprecision(2) << ans << endl;
  }
}