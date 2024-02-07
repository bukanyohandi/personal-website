#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> interval(m);
  for (int i = 0; i < m; ++i) {
    cin >> interval[i].first >> interval[i].second;
  }
  sort(interval.begin(), interval.end());

  long long ans = 0;
  long long le = 1, ri = 1e18;
  while (le <= ri) {
    long long D = (le + ri) / 2;

    int i = 0, cnt = n;
    long long last = interval[i].first - D;
    while (i < m && cnt > 0) {
      while (last + D <= interval[i].second) {
        last += D;
        cnt--;
      }
      i++;
      if (i < m) {
        last = max(last, interval[i].first - D);
      }
    }

    if (cnt <= 0) {
      ans = D;
      le = D + 1;
    } else {
      ri = D - 1;
    }
  }

  cout << ans << endl;

  return 0;
}