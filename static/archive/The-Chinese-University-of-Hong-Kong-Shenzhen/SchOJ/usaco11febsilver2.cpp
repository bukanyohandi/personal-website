#include <bits/stdc++.h>
using namespace std;

int main() {
  const long long MOD = 12345678910;

  int n;
  cin >> n;

  stack<long long> st;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    if (x == 0) {
      st.push(-1);
    } else {
      long long val;
      if (st.top() == -1) {
        val = 1;
        st.pop();
      } else {
        val = (2 * st.top()) % 12345678910;
        st.pop();
        st.pop();
      }

      while (!st.empty() && st.top() != -1) {
        val += st.top();
        val %= MOD;
        st.pop();
      }
      st.push(val);
    }
  }

  cout << st.top() << endl;
  return 0;
}