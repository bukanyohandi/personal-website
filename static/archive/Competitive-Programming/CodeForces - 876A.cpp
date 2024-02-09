#include <bits/stdc++.h>
using namespace std;
bool udah[3] = {};
int main() {
  int ans = 0, n, a, b, c, lastpick;
  cin >> n;
  cin >> a >> b >> c;
  n -= 1;
  if (n == 0) {
    cout << 0 << endl;
    return 0;
  }
  if (c < min(a, b)) {
    if (a == min(a, b)) {
      ans += a;
      n--;
      while (n != 0) {
        ans += c;
        n--;
      }
    } else {
      ans += b;
      n--;
      while (n != 0) {
        ans += c;
        n--;
      }
    }
  } else {
    if (a == min(a, b)) {
      while (n != 0) {
        ans += a;
        n--;
      }
    } else {
      while (n != 0) {
        ans += b;
        n--;
      }
    }
  }
  cout << ans << endl;
}