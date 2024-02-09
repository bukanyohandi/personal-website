#include <bits/stdc++.h>
using namespace std;
long long mod, n, m;
struct matrix {
  long long a, b, c, d;
};
matrix fs;
matrix mult(matrix x, matrix y) {
  matrix tmp;
  tmp.a = ((x.a * y.a) % mod + (x.b * y.c) % mod) % mod;
  tmp.b = ((x.a * y.b) % mod + (x.b * y.d) % mod) % mod;
  tmp.c = ((x.a * y.c) % mod + (x.c * y.d) % mod) % mod;
  tmp.d = ((x.b * y.c) % mod + (x.d * y.d) % mod) % mod;
  return tmp;
}
matrix power(long long pow) {
  if (pow == 1LL)
    return fs;
  matrix tmp = power(pow / 2);
  if (pow % 2)
    return mult(mult(tmp, tmp), fs);
  return mult(tmp, tmp);
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  fs.a = 1;
  fs.b = 1;
  fs.c = 1;
  fs.d = 0;
  while (cin >> n >> m) {
    if (n == 0LL) {
      printf("0\n");
      continue;
    }
    mod = (1 << m);
    printf("%lld\n", power(n).b);
  }
}