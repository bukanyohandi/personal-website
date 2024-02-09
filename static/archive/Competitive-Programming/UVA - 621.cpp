#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  string s;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> s;
    if (s[s.length() - 1] == '5' && s[s.length() - 2] == '3') {
      cout << "-" << endl;
      continue;
    }
    if (s[0] == '9' && s[s.length() - 1] == '4') {
      cout << "*" << endl;
      continue;
    }
    if (s[0] == '1' && s[1] == '9' && s[2] == '0') {
      cout << "?" << endl;
      continue;
    }
    cout << "+" << endl;
    continue;
  }
}