#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }

  int le = 0;
  int ri = 2e9;
  int ans = -1;
  while (le <= ri) {
    int mid = (le + ri) / 2;

    int req = 0;
    for (int i = 0; i < n; ++i) {
      if (a[i] * mid > b[i]) {
        req += a[i] * mid - b[i];
      }
      if (req > k) {
        break;
      }
    }

    if (req <= k) {
      le = mid + 1;
      ans = mid;
    } else {
      ri = mid - 1;
    }
  }

  cout << ans << endl;
}