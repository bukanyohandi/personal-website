#include <bits/stdc++.h>
#define ll long long
#define fs first
#define sc second
using namespace std;
struct x {
  ll x1, x2, y1, y2;
} Point[4];
set<pair<ll, ll>> Count;
map<ll, int> x_, y_;
ll piv, piv2;
vector<double> vec;
map<pair<ll, ll>, int> c;
double x;
int main() {
  for (int i = 0; i < 4; ++i) {
    cin >> Point[i].x1 >> Point[i].y1 >> Point[i].x2 >> Point[i].y2;
    Count.insert({Point[i].x1, Point[i].y1});
    Count.insert({Point[i].x2, Point[i].y2});
  }
  if (Count.size() != 4) {
    cout << "NO\n";
    return 0;
  }
  for (auto i : Count) {
    x_[i.fs]++;
    y_[i.sc]++;
  }
  for (auto i : x_)
    if (i.sc > 2) {
      cout << "NO\n";
      return 0;
    }
  for (auto i : y_)
    if (i.sc > 2) {
      cout << "NO\n";
      return 0;
    }
  for (auto i : Count) {
    for (auto j : Count) {
      if (i == j)
        continue;
      if (i.fs == j.fs || i.sc == j.sc)
        piv++;
    }
  }
  if (piv == 8) {
    for (int i = 0; i < 4; ++i) {
      if (Point[i].x1 == Point[i].x2 && Point[i].y1 == Point[i].y2) {
        cout << "NO\n";
        return 0;
      }
      for (int j = 0; j < 4; ++j) {
        if (i == j)
          continue;
        if (Point[i].x1 == Point[j].x1 && Point[i].y1 == Point[j].y1 &&
            Point[i].x2 == Point[j].x2 && Point[i].y2 == Point[j].y2) {
          cout << "NO\n";
          return 0;
        }
        if (Point[i].x1 == Point[j].x2 && Point[i].y1 == Point[j].y2 &&
            Point[i].x2 == Point[j].x1 && Point[i].y2 == Point[j].y1) {
          cout << "NO\n";
          return 0;
        }
      }
    }
    for (int i = 0; i < 4; ++i) {
      c[{Point[i].x1, Point[i].y1}]++;
      c[{Point[i].x2, Point[i].y2}]++;
    }
    for (auto i : c) {
      if (i.sc != 2) {
        cout << "NO\n";
        return 0;
      }
    }
    cout << "YES\n";
    return 0;
  }
  if (piv != 0) {
    cout << "NO\n";
    return 0;
  }
  for (int i = 0; i < 4; ++i)
    vec.push_back(
        (double)((Point[i].y2 - Point[i].y1) / (Point[i].x2 - Point[i].x1)));
  piv = 0;
  piv2 = 0;
  x = vec[0];
  for (int i = 1; i < 4; ++i) {
    if (x == vec[i])
      piv++;
    else if (x * vec[i] == -1)
      piv2++;
  }
  if (piv == 1 && piv2 == 2) {
    cout << "YES\n";
    return 0;
  } else {
    cout << "NO\n";
    return 0;
  }
}