#include <bits/stdc++.h>
using namespace std;
struct node {
  int prefix, suffix, best, sum;
};
int N, Q, data[50005], par[50005];
node tree[200005];
node merge(node x, node y) {
  node tmp;
  tmp.sum = x.sum + y.sum;
  tmp.best = max(max(x.best, y.best), (x.suffix + y.prefix));
  tmp.prefix = max(x.prefix, x.sum + y.prefix);
  tmp.suffix = max(y.suffix, y.sum + x.suffix);
  return tmp;
}
void build(int low, int high, int pos) {
  if (low == high) {
    tree[pos].prefix = tree[pos].suffix = tree[pos].sum = tree[pos].best =
        data[low];
    par[low] = pos;
    return;
  }
  int mid = (low + high) / 2;
  build(low, mid, 2 * pos);
  build(mid + 1, high, 2 * pos + 1);
  tree[pos] = merge(tree[2 * pos], tree[2 * pos + 1]);
  return;
}
void update(int x, int New) {
  int pos = par[x];
  tree[pos].prefix = tree[pos].suffix = tree[pos].sum = tree[pos].best = New;
  pos /= 2;
  while (pos > 0) {
    tree[pos] = merge(tree[2 * pos], tree[2 * pos + 1]);
    pos /= 2;
  }
}
node query(int pos, int low, int high, int leftt, int rightt) {
  if (low == leftt && high == rightt)
    return tree[pos];
  int mid = (low + high) / 2;
  if (rightt <= mid)
    return query(2 * pos, low, mid, leftt, rightt);
  if (leftt > mid)
    return query(2 * pos + 1, mid + 1, high, leftt, rightt);
  return merge(query(2 * pos, low, mid, leftt, mid),
               query(2 * pos + 1, mid + 1, high, mid + 1, rightt));
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  for (int i = 1; i <= N; ++i)
    cin >> data[i];
  build(1, N, 1);
  cin >> Q;
  for (int i = 1; i <= Q; ++i) {
    int piv1, piv2, X;
    cin >> X >> piv1 >> piv2;
    if (X == 1)
      cout << query(1, 1, N, piv1, piv2).best << endl;
    else
      update(piv1, piv2);
  }
  return 0;
}