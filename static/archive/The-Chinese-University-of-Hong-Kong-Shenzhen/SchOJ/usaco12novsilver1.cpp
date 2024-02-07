#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);

  string s;
  cin >> s;

  int ans = 0;
  stack<int> st;
  for (auto c : s) {
    if (c == '(') {
      st.push(c);
    } else if (!st.empty() && st.top() == '(') {
      st.pop();
    } else {
      st.push('(');
      ans++;
    }
  }

  cout << (int)ans + st.size() / 2 << endl;
  return 0;
}
