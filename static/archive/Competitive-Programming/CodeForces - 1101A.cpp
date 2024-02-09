#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, a, b, c;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> b >> c;
    int tmp = c;
    if (a <= c) {
      tmp = (b + c) / c;
      cout << tmp * c << endl;
      continue;
    } else {
      cout << c << endl;
      continue;
    }
  }
}