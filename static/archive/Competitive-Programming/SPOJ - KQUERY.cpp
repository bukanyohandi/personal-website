#include <bits/stdc++.h>
#define inp(x) scanf("%d", &x)
#define inp3(x, y, z) scanf("%d%d%d", &x, &y, &z)
#define outln(x) printf("%d\n", x)
#define fs first
#define sc second
using namespace std;
struct info {
  int i, j, k, idx;
};
bool cmp(info x, info y) { return x.k > y.k; }
info data[200005];
int n, q, ans[200005], piv, tree[30005];
pair<int, int> data2[30005];
inline void updt(int x) {
  for (; x <= n; x += x & -x)
    tree[x]++;
}
inline int pref(int x) {
  int sum = 0;
  for (; x > 0; x -= x & -x)
    sum += tree[x];
  return sum;
}
int main() {
  inp(n);
  for (int i = 0; i < n; ++i)
    inp(data2[i].fs), data2[i].sc = i + 1;
  sort(data2, data2 + n);
  inp(q);
  for (int i = 0; i < q; ++i)
    inp3(data[i].i, data[i].j, data[i].k), data[i].idx = i;
  sort(data, data + q, cmp);
  piv = n - 1;
  for (int i = 0; i < q; ++i) {
    for (; piv < n && data2[piv].fs > data[i].k; piv--)
      updt(data2[piv].sc);
    ans[data[i].idx] = pref(data[i].j) - pref(data[i].i - 1);
  }
  for (int i = 0; i < q; ++i)
    outln(ans[i]);
}