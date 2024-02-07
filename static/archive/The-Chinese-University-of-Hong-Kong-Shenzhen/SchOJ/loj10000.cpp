#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;
  vector<pair<int, int>> activities(n);
  for (int i = 0; i < n; ++i) {
    cin >> activities[i].first >> activities[i].second;
  }

  sort(activities.begin(), activities.end(),
       [&](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });

  int ans = 0, last = 0;
  for (int i = 0; i < activities.size(); ++i) {
    if (activities[i].first >= last) {
      ans++;
      last = activities[i].second;
    }
  }

  cout << ans << endl;

  return 0;
}
