#include <bits/stdc++.h>
using namespace std;
int main() {
  int a = 0, b = 0;
  string s;
  cin >> s;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == 'o') {
      a++;
    } else {
      b++;
    }
  }
  if (a <= 1 || b == 0) {
    cout << "YES" << endl;
    return 0;
  }
  if (b % a == 0) {
    cout << "YES" << endl;
    return 0;
  }
  cout << "NO" << endl;
  return 0;
}