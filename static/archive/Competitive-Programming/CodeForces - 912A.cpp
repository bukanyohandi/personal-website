#include <bits/stdc++.h>
using namespace std;
int main() {
  long long a, b, c, d, e;
  cin >> a >> b;
  cin >> c >> d >> e;
  long long butuh = 0, ans = 0;
  a -= (c * 2);
  b -= (e * 3);
  a -= d;
  b -= d;
  if (a < 0) {
    ans = ans + abs(a);
  }
  if (b < 0) {
    ans = ans + abs(b);
  }
  cout << ans << endl;
}