#include <bits/stdc++.h>
using namespace std;
int main() {
  int ans = -1, n, prev = 0, now;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> now;
    if (now >= prev) {
      ans = ans + 1 + now - prev;
    } else {
      ans = ans + 1 + abs(now - prev);
    }
    prev = now;
    ans++;
  }
  cout << ans << endl;
}