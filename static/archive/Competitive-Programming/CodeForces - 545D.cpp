#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
  int n;
  cin >> n;

  vector<int> t(n);
  for (int i = 0; i < n; ++i) {
    cin >> t[i];
  }

  sort(t.begin(), t.end());
  int cur = 0;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (cur <= t[i]) {
      ans += 1;
    } else {
      continue;
    }
    cur += t[i];
  }

  cout << ans << endl;
}