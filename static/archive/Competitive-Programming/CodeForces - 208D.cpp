#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
  int n;
  cin >> n;

  vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }

  vector<int> p(5);
  for (int i = 0; i < 5; ++i) {
    cin >> p[i];
  }
  sort(p.begin(), p.end());

  int cur = 0;
  vector<int> ans(5, 0);
  for (int i = 0; i < n; ++i) {
    cur += b[i];

    bool valid = true;
    while (valid) {
      valid = false;
      if (cur >= p[0]) {
        valid = true;
        for (int k = 4; k >= 0; --k) {
          int take = cur / p[k];
          ans[k] += take;
          cur -= take * p[k];
        }
      }
    }
  }

  for (int i = 0; i < 5; ++i) {
    if (i != 0)
      cout << " ";
    cout << ans[i];
  }
  cout << endl;
  cout << cur << endl;
}