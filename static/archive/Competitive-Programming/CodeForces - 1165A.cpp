#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b, c, ans = 0;
  string s;
  cin >> a >> b >> c;
  cin >> s;
  reverse(s.begin(), s.end());
  for (int i = 0; i < c; i++) {
    if (s[i] == '1') {
      ans++;
    }
  }
  if (s[c] == '0') {
    ans++;
  }
  for (int i = c + 1; i < b; i++) {
    if (s[i] == '1') {
      ans++;
    }
  }
  cout << ans << endl;
}