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
pair<int, int> koord[1005];
double ans;
int main() {
  int n, x1, x2, y1, y2;
  boost();
  while (cin >> n) {
    if (n == 0)
      return 0;
    ans = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> koord[i].first >> koord[i].second;
    }
    x1 = koord[2].first - koord[1].first;
    y1 = koord[2].second - koord[1].second;
    x2 = koord[2].first - koord[2].first;
    y2 = koord[2].second - koord[1].second;
    koord[n + 1].first = koord[1].first;
    koord[n + 1].second = koord[1].second;
    for (int i = 1; i <= n; ++i) {
      ans = ans + koord[i].first * koord[i + 1].second -
            koord[i].second * koord[i + 1].first;
    }
    if (ans < 0) {
      cout << "CW ";
    } else {
      cout << "CCW ";
    }
    cout << fixed << setprecision(1) << abs(ans) / 2 << endl;
  }
}