#include <bits/stdc++.h>
using namespace std;
bool prima(int x) {
  if (x == 1)
    return true;
  if (x % 2 == 0 && x > 2)
    return false;
  for (int i = 3; i * i <= x; i += 2) {
    if (x % i == 0)
      return false;
  }
  return true;
}
int main() {
  string s;
  while (cin >> s) {
    int ans = 0;
    for (int i = 0; i < s.length(); ++i) {
      if (s[i] - 'a' >= 0 && s[i] - 'a' < 26) {
        ans += s[i] - 'a' + 1;
      } else {
        ans += s[i] - 'A' + 27;
      }
    }
    if (prima(ans)) {
      cout << "It is a prime word." << endl;
    } else {
      cout << "It is not a prime word." << endl;
    }
  }
}