#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  int ans = arr[0], current_max = arr[0], len = 1;
  for (int i = 1; i < n; ++i) {
    if (len == m) {
      current_max -= arr[i - m];
      len = len - 1;
    }
    current_max = max(arr[i], arr[i] + current_max);
    ans = max(ans, current_max);

    if (current_max == arr[i]) {
      len = 1;
    } else {
      len = len + 1;
    }
  }

  cout << ans << endl;

  return 0;
}
