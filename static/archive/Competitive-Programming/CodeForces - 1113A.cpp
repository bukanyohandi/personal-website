#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b;
  cin >> a >> b;
  if (a <= b) {
    cout << a - 1 << endl;
  } else {
    int ans = 0;
    ans += b;
    for (int i = 2; i <= a - b; i++) {
      ans += i;
    }
    cout << ans << endl;
  }
}