#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  string s;
  cin >> s;

  int n = (int)s.length();
  sort(s.begin(), s.end());

  vector<bool> visited(n, false);
  function<void(string)> print = [&](string str) {
    if (str.length() == n) {
      cout << str << "\n";
      return;
    }
    for (int i = 0; i < n; ++i) {
      if (!visited[i]) {
        str.push_back(s[i]);
        visited[i] = true;
        print(str);
        str.pop_back();
        visited[i] = false;
      }
    }
    return;
  };

  print("");

  return 0;
}
