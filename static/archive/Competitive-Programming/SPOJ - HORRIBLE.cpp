#include <bits/stdc++.h>
using namespace std;
long long leftt, rightt, val, op, tc, N, C, tree[400005], lazy[400005];
void add(long long low, long long high, long long pos) {
  if (lazy[pos] != 0) {
    tree[pos] += (high - low + 1) * lazy[pos];
    if (low != high) {
      lazy[2 * pos] += lazy[pos];
      lazy[2 * pos + 1] += lazy[pos];
    }
    lazy[pos] = 0;
  }
  if (rightt < low || leftt > high)
    return;
  if (leftt <= low && rightt >= high) {
    tree[pos] += (high - low + 1) * val;
    if (low != high) {
      lazy[2 * pos] += val;
      lazy[2 * pos + 1] += val;
    }
    return;
  }
  long long mid = (low + high) / 2;
  add(low, mid, 2 * pos);
  add(mid + 1, high, 2 * pos + 1);
  tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
}
long long query(long long low, long long high, long long pos) {
  if (lazy[pos] != 0) {
    tree[pos] += (high - low + 1) * lazy[pos];
    if (low != high) {
      lazy[2 * pos] += lazy[pos];
      lazy[2 * pos + 1] += lazy[pos];
    }
    lazy[pos] = 0;
  }
  if (rightt < low || leftt > high)
    return 0;
  if (leftt <= low && rightt >= high)
    return tree[pos];
  long long mid = (low + high) / 2;
  return query(low, mid, 2 * pos) + query(mid + 1, high, 2 * pos + 1);
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> tc;
  while (tc--) {
    cin >> N >> C;
    for (long long i = 1; i <= 4 * N; ++i)
      tree[i] = lazy[i] = 0;
    for (long long i = 1; i <= C; ++i) {
      cin >> op >> leftt >> rightt;
      if (op == 0) {
        cin >> val;
        add(1, N, 1);
      } else {
        cout << query(1, N, 1) << endl;
      }
    }
  }
}