#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;

  vector<pair<int, int>> points(n);
  for (int i = 0; i < n; ++i) {
    cin >> points[i].first >> points[i].second;
  }

  sort(points.begin(), points.end(), [&](pair<int, int> a, pair<int, int> b) {
    if (a.first - a.second != b.first - b.second)
      return a.first - a.second < b.first - b.second;
    return a.first + a.second > b.first + b.second;
  });

  int ans = 0, m = -1;
  for (int i = 0; i < n; ++i) {
    ans += points[i].first + points[i].second > m;
    m = max(m, points[i].first + points[i].second);
  }

  cout << ans << endl;

  return 0;
}