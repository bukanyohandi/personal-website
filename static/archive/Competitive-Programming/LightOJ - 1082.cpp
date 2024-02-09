#include <bits/stdc++.h>
using namespace std;
int leftt, rightt, maks, tc, N, Q, tree[400005], data[100005];
void build(int low, int high, int pos) {
  if (low == high) {
    tree[pos] = data[low];
    return;
  }
  int mid = (low + high) / 2;
  build(low, mid, 2 * pos + 1);
  build(mid + 1, high, 2 * pos + 2);
  tree[pos] = min(tree[2 * pos + 1], tree[2 * pos + 2]);
  return;
}
int query(int low, int high, int pos) {
  if (leftt > high || rightt < low)
    return maks;
  if (leftt <= low && rightt >= high)
    return tree[pos];
  return min(query(low, (low + high) / 2, 2 * pos + 1),
             query((low + high + 2) / 2, high, 2 * pos + 2));
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> tc;
  for (int t = 1; t <= tc; ++t) {
    maks = -100001;
    cin >> N >> Q;
    for (int i = 0; i < N; ++i) {
      cin >> data[i];
      maks = max(maks, data[i]);
    }
    build(0, N - 1, 0);
    cout << "Case " << t << ":" << endl;
    while (Q--) {
      cin >> leftt >> rightt;
      leftt--;
      rightt--;
      cout << query(0, N - 1, 0) << endl;
    }
  }
}