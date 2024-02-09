#include <bits/stdc++.h>
#define inp(x) x = scan();
#define outl(x) printf("%d\n", x)
using namespace std;
struct node {
  int idx1, idx2, val, flag;
  bool piv;
};
int tmp, i, x, n, q, le, ri, ans[200005], tree[120005], data[1000005] = {0};
node arr[230005];
inline int scan() {
  int ret = 0, c = getchar();
  while (c < '0' || c > '9')
    c = getchar();
  while (c >= '0' && c <= '9') {
    ret = (ret << 3) + (ret << 1) + c - '0';
    c = getchar();
  }
  return ret;
}
inline void add1() {
  arr[i].idx1 = i;
  arr[i].val = x;
  arr[i].piv = false;
  return;
}
inline void add2() {
  arr[i + n].idx1 = ri;
  arr[i + n].idx2 = i;
  arr[i + n].flag = le;
  arr[i + n].piv = true;
  return;
}
bool cmp(const node &a, const node &b) {
  if (a.idx1 == b.idx1)
    return a.val > b.val;
  return a.idx1 < b.idx1;
}
void update(int low, int high, int tmp, int pos) {
  if (low == high) {
    tree[tmp] ^= 1;
    return;
  }
  int mid = (low + high) / 2;
  if (mid >= pos)
    update(low, mid, 2 * tmp, pos);
  else
    update(mid + 1, high, 2 * tmp + 1, pos);
  tree[tmp] = tree[2 * tmp] + tree[2 * tmp + 1];
}
int query(int low, int high, int l, int r, int tmp) {
  if (l > r || low > r || l > high)
    return 0;
  if (l >= low && high >= r)
    return tree[tmp];
  int mid = (l + r) / 2;
  return query(low, high, l, mid, 2 * tmp) +
         query(low, high, mid + 1, r, 2 * tmp + 1);
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  inp(n);
  for (i = 1; i <= n; ++i) {
    inp(x);
    add1();
  }
  inp(q);
  for (i = 1; i <= q; ++i) {
    inp(le);
    inp(ri);
    add2();
  }
  sort(arr + 1, arr + n + q + 1, cmp);
  for (i = 1; i <= n + q; ++i) {
    if (arr[i].piv)
      ans[arr[i].idx2] = query(arr[i].flag, arr[i].idx1, 1, n, 1);
    else {
      tmp = arr[i].val;
      if (data[tmp] != 0)
        update(1, n, 1, data[tmp]);
      update(1, n, 1, arr[i].idx1);
      data[tmp] = arr[i].idx1;
    }
  }
  for (int i = 1; i <= q; ++i)
    outl(ans[i]);
  return 0;
}