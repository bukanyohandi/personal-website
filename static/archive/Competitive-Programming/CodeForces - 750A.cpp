#include <bits/stdc++.h>
using namespace std;
int main() {
  int ans = 0, n, k, jam = 240;
  cin >> n >> k;
  jam -= k;
  for (int i = 1; i <= n; ++i) {
    if (5 * i <= jam) {
      ans++;
      jam -= 5 * i;
    } else {
      break;
    }
  }
  cout << ans << endl;
}