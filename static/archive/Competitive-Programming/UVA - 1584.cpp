#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string s, tmp;
    cin >> s;
    tmp = s;
    s += s;
    for (int j = 0; j < tmp.length(); ++j) {
      tmp = min(tmp, s.substr(j, tmp.length()));
    }
    cout << tmp << endl;
  }
}