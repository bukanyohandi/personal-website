#include <bits/stdc++.h>
using namespace std;
int main() {
  int i, c = 0;
  string s;
  cin >> s;
  for (i = 0; i < s.length() / 2; i++) {
    if (s[i] != s[s.length() - i - 1])
      c++;
  }
  if (c == 0 && s.length() % 2 == 1 || c == 1) {
    cout << "YES";
  } else {
    cout << "NO";
  }
}