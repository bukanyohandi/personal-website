#include <bits/stdc++.h>
using namespace std;

int main() {
  string s, t;
  cin >> s;
  cin >> t;

  int n = s.length();
  int m = t.length();
  int last = 0;

  deque<pair<char, int>> dq;
  for (int i = 0; i < n; ++i) {
    if (dq.empty()) {
      if (s[i] == t[0]) {
        dq.push_front({s[i], 0});
      } else {
        dq.push_front({s[i], -1});
      }
    } else {
      last = dq.front().second;
      if (s[i] == t[last + 1]) {
        dq.push_front({s[i], last + 1});
      } else if (s[i] == t[0]) {
        dq.push_front({s[i], 0});
      } else {
        dq.push_front({s[i], -1});
      }
    }

    if (dq.front().second == m - 1) {
      for (int j = 0; j < m; ++j) {
        dq.pop_front();
      }
    }
  }

  string result = "";
  while (!dq.empty()) {
    result.push_back(dq.back().first);
    dq.pop_back();
  }

  cout << result << endl;
  return 0;
}
