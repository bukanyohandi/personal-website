#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
long long x, ans, maks, maksleft, n, data[N], lefty[N], righty[N], tree[N];
unordered_map<long long, long long> idx;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> data[i];
    idx[data[i]]++;
    if (i == 0)
      continue;
    lefty[i + 1] = idx[data[i]];
    maksleft = max(lefty[i], maksleft);
  }
  idx.clear();
  for (int i = n - 1; i > 0; --i) {
    idx[data[i]]++;
    righty[n - i] = idx[data[i]];
    maks = max(righty[n - i], maks);
  }
  for (int i = 1; i < n; ++i) {
    x = righty[i];
    while (x <= maks)
      tree[x]++, x += x & -x;
    x = lefty[n - i] - 1;
    while (x > 0)
      ans += tree[x], x -= x & -x;
  }
  cout << ans << endl;
}