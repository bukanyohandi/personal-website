#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, piv, x;
  string s;
  while (cin >> n >> s && n != 0) {
    piv = s.length() / n;
    x = piv;
    while (x <= s.length()) {
      for (int i = x - 1; i >= x - piv; --i) {
        cout << s[i];
      }
      x += piv;
    }
    cout << endl;
  }
}