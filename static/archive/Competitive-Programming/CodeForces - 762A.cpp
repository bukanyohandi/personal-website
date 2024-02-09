#include <bits/stdc++.h>
#include <stack>
using namespace std;
int main() {
  stack<int> st;
  long long n, k;
  long long ans = -1;
  cin >> n >> k;
  for (long long i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      k--;
      if (i * i != n) {
        st.push(i);
      }
    }
    if (k == 0) {
      ans = i;
      break;
    }
  }
  if (k != 0 && k <= st.size()) {
    for (long long i = 0; i < k - 1; i++) {
      st.pop();
    }
    ans = n / st.top();
  }
  cout << ans << endl;
}