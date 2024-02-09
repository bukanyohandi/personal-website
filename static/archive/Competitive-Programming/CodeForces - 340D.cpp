#include <bits/stdc++.h>
using namespace std;
long long n, data[100005], fenwick[100005], x, piv, tmp, best;
int main() {
  scanf("%lld", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &x);
    tmp = 0;
    for (piv = x - 1; piv > 0; piv -= piv & -piv)
      tmp = max(tmp, fenwick[piv]);
    data[x] = max(data[x], tmp + 1);
    for (piv = x; piv <= 100000; piv += piv & -piv)
      fenwick[piv] = max(fenwick[piv], tmp + 1);
    best = max(best, data[x]);
  }
  printf("%lld\n", best);
}