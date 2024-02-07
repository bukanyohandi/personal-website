#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;

  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  vector<int> ans(n, 0);
  stack<int> st;
  for (int i = 0; i < n; ++i) {
    if (st.empty() || arr[st.top()] >= arr[i]) {
      st.push(i);
      continue;
    }
    while (!st.empty() && arr[st.top()] < arr[i]) {
      ans[st.top()] = i + 1;
      st.pop();
    }
    st.push(i);
  }

  for (int i = 0; i < n; ++i) {
    cout << ans[i] << "\n";
  }

  return 0;
}
