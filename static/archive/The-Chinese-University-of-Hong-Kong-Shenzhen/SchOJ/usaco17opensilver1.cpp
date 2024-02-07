#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<pair<int, int>> p(N);
  for (auto &e : p) {
    cin >> e.first >> e.second;
  }
  sort(p.begin(), p.end(),
       [&](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });

  int l = 0;
  int r = N - 1;
  int ans = -1;
  while (l < r) {
    ans = max(ans, p[l].second + p[r].second);
    int mn = min(p[l].first, p[r].first);
    p[l].first -= mn;
    p[r].first -= mn;
    if (p[l].first == 0)
      ++l;
    if (p[r].first == 0)
      --r;
  }
  if (l == r && p[l].first != 0) {
    ans = max(ans, p[l].second + p[r].second);
  }

  cout << ans << endl;

  return 0;
}
