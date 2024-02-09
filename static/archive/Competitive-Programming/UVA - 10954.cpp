#include <bits/stdc++.h>
using namespace std;
long long data[5005];
int main() {
  priority_queue<int, vector<int>, greater<int>> pq;
  long long tmp, n, x, ans, prev;
  while (cin >> n && n != 0) {
    ans = prev = 0;
    while (!pq.empty())
      pq.pop();
    for (int i = 1; i <= n; ++i) {
      cin >> x;
      pq.push(x);
    }
    while (pq.size() > 1) {
      ans += pq.top();
      tmp = pq.top();
      pq.pop();
      ans += pq.top();
      tmp += pq.top();
      pq.pop();
      pq.push(tmp);
    }
    cout << ans << endl;
  }
}