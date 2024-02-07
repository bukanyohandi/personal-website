#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;

  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  long long ans = 20 * 1e9;
  for (int j = 0; j < (1 << n); ++j) {
    long long result = 0;
    for (int i = 0; i < n; ++i) {
      if ((j >> i) & 1) {
        result += arr[i];
      } else {
        result -= arr[i];
      }
    }
    ans = min(ans, abs(result));
  }

  cout << ans << endl;

  return 0;
}
