#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;

    int mark = -1;
    string t;
    for (int j = 0; j + 1 < s.length(); ++j) {
      if (s[j] == s[j + 1]) {
        mark = j;
        break;
      }
    }
    if (mark != -1) {
      for (int j = 0; j <= mark; ++j) {
        t.push_back(s[j]);
      }
      char c = s[mark];
      if (c == 'z')
        c = 'a';
      else
        c++;
      t.push_back(c);
      for (int j = mark + 1; j < s.length(); ++j) {
        t.push_back(s[j]);
      }
    } else {
      char c = s[0];
      if (c == 'z')
        c = 'a';
      else
        c++;
      t.push_back(c);
      t += s;
    }

    cout << t << endl;
  }

  return 0;
}