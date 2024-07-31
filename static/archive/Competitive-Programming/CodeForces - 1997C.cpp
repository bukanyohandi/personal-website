#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
  int tc;
  cin >> tc;

  for (int i = 0; i < tc; ++i) {
    int n;
    cin >> n;
    string s;
    cin >> s;

    // int a = 0;
    // int b = 0;
    // for (auto c : s) {
    //   if (c == '(') {
    //     a++;
    //   } else if (c == ')') {
    //     b++;
    //   }
    // }

    int ans = 0;
    stack<pair<char, int>> st;
    for (int j = 0; j < s.length(); ++j) {
      if (s[j] == '(') {
        st.push({s[j], j});
      } else if (s[j] == '_') {
        if (!st.empty()) {
          ans += j - st.top().second;
          st.pop();
        } else {
          st.push({'(', j});
        }
      } else {
        assert(!st.empty());
        ans += j - st.top().second;
        st.pop();
      }
    }

    cout << ans << endl;
  }

  return 0;
}