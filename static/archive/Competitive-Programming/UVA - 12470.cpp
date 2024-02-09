#include <bits/stdc++.h>
#define MOD 1000000009
using namespace std;
struct matrix {
  long long a, b, c, d, e, f, g, h, i;
};
matrix fs;
matrix mult(matrix x, matrix y) {
  matrix tmp;
  tmp.a = ((x.a * y.a) % MOD + (x.b * y.d) % MOD + (x.c * y.g) % MOD) % MOD;
  tmp.b = ((x.a * y.b) % MOD + (x.b * y.e) % MOD + (x.c * y.h) % MOD) % MOD;
  tmp.c = ((x.a * y.c) % MOD + (x.b * y.f) % MOD + (x.c * y.i) % MOD) % MOD;
  tmp.d = ((x.d * y.a) % MOD + (x.e * y.d) % MOD + (x.f * y.g) % MOD) % MOD;
  tmp.e = ((x.d * y.b) % MOD + (x.e * y.e) % MOD + (x.f * y.h) % MOD) % MOD;
  tmp.f = ((x.d * y.c) % MOD + (x.e * y.f) % MOD + (x.f * y.i) % MOD) % MOD;
  tmp.g = ((x.g * y.a) % MOD + (x.h * y.d) % MOD + (x.i * y.g) % MOD) % MOD;
  tmp.h = ((x.g * y.b) % MOD + (x.h * y.e) % MOD + (x.i * y.h) % MOD) % MOD;
  tmp.i = ((x.g * y.c) % MOD + (x.h * y.f) % MOD + (x.i * y.i) % MOD) % MOD;
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
long long n;
int main() {
  matrix tmp;
  fs.a = 1;
  fs.b = 1;
  fs.c = 1;
  fs.d = 1;
  fs.e = 0;
  fs.f = 0;
  fs.g = 0;
  fs.h = 1;
  fs.i = 0;
  while (cin >> n) {
    if (n == 0)
      return 0;
    if (n == 1)
      printf("0\n");
    else if (n == 2)
      printf("1\n");
    else if (n == 3)
      printf("2\n");
    else {
      tmp = power(n - 3);
      printf("%lld\n", (tmp.a * 2 + tmp.b) % MOD);
    }
  }
}