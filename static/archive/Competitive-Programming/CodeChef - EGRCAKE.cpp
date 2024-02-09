#include <bits/stdc++.h>
using namespace std;
int fpb(int a, int b) {
  if (b == 0)
    return a;
  return fpb(b, a % b);
}
int main() {
  int tc, n, m;
  cin >> tc;
  while (tc--) {
    cin >> n >> m;
    if (fpb(n, m) == 1) {
      cout << "Yes" << endl;
    } else {
      cout << "No " << n / fpb(n, m) << endl;
    }
  }
}