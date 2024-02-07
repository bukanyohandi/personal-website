#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> arr(2 * n, 0);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    arr[x - 1] = 1;
  }

  vector<int> a, b;
  for (int i = 0; i < 2 * n; ++i) {
    if (arr[i] == 1) {
      a.push_back(i);
    } else {
      b.push_back(i);
    }
  }

  int ans = 0, p = 0;
  for (int i = 0; i < n; ++i) {
    while (p < n && a[i] > b[p]) {
      p++;
    }
    if (p < n) {
      ans++;
      p++;
    }
  }

  cout << ans << endl;

  return 0;
}