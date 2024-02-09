#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, a = 0;
  string s;
  cin >> s >> n;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '0')
      a++;
  }
  if (a < n) {
    cout << s.length() - 1 << endl;
    return 0;
  }
  a = 0;
  for (int i = s.length() - 1; i >= 0; i--) {
    if (s[i] == '0') {
      n--;
      a++;
    }
    if (n == 0) {
      cout << s.length() - i - a << endl;
      return 0;
    }
  }
}