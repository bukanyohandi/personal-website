#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;
ll tc, N;
struct matrix {
  ll a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
};
matrix fs;
ll add(ll a, ll b, ll c, ll d) {
  a %= MOD;
  b %= MOD;
  c %= MOD;
  d %= MOD;
  return ((((a + b) % MOD + (c + d) % MOD) % MOD) + MOD) % MOD;
}
matrix mult(matrix x, matrix y) {
  matrix tmp;
  tmp.a = add(x.a * y.a, x.b * y.e, x.c * y.i, x.d * y.m);
  tmp.b = add(x.a * y.b, x.b * y.f, x.c * y.j, x.d * y.n);
  tmp.c = add(x.a * y.c, x.b * y.g, x.c * y.k, x.d * y.o);
  tmp.d = add(x.a * y.d, x.b * y.h, x.c * y.l, x.d * y.p);
  tmp.e = add(x.e * y.a, x.f * y.e, x.g * y.i, x.h * y.m);
  tmp.f = add(x.e * y.b, x.f * y.f, x.g * y.j, x.h * y.n);
  tmp.g = add(x.e * y.c, x.f * y.g, x.g * y.k, x.h * y.o);
  tmp.h = add(x.e * y.d, x.f * y.h, x.g * y.l, x.h * y.p);
  tmp.i = add(x.i * y.a, x.j * y.e, x.k * y.i, x.l * y.m);
  tmp.j = add(x.i * y.b, x.j * y.f, x.k * y.j, x.l * y.n);
  tmp.k = add(x.i * y.c, x.j * y.g, x.k * y.k, x.l * y.o);
  tmp.l = add(x.i * y.d, x.j * y.h, x.k * y.l, x.l * y.p);
  tmp.m = add(x.m * y.a, x.n * y.e, x.o * y.i, x.p * y.m);
  tmp.n = add(x.m * y.b, x.n * y.f, x.o * y.j, x.p * y.n);
  tmp.o = add(x.m * y.c, x.n * y.g, x.o * y.k, x.p * y.o);
  tmp.p = add(x.m * y.d, x.n * y.h, x.o * y.l, x.p * y.p);
  return tmp;
}
matrix power(ll pow) {
  if (pow == 1)
    return fs;
  matrix tmp = power(pow / 2);
  if (pow % 2)
    return mult(mult(tmp, tmp), fs);
  return mult(tmp, tmp);
}
void print(matrix x) {
  cout << x.a << " " << x.b << " " << x.c << " " << x.d << endl;
  cout << x.e << " " << x.f << " " << x.g << " " << x.h << endl;
  cout << x.i << " " << x.j << " " << x.k << " " << x.l << endl;
  cout << x.m << " " << x.n << " " << x.o << " " << x.p << endl;
  return;
}
int main() {
  matrix tmp;
  fs.a = 5;
  fs.b = -8;
  fs.c = 5;
  fs.d = -1;
  fs.e = 1;
  fs.f = 0;
  fs.g = 0;
  fs.h = 0;
  fs.i = 0;
  fs.j = 1;
  fs.k = 0;
  fs.l = 0;
  fs.m = 0;
  fs.n = 0;
  fs.o = 1;
  fs.p = 0;
  //	matrix x=mult(fs,fs);
  //	print(x);
  cin >> tc;
  while (tc--) {
    cin >> N;
    if (N == 1)
      cout << 0 << endl;
    else if (N == 2)
      cout << 1 << endl;
    else if (N == 3)
      cout << 5 << endl;
    else if (N == 4)
      cout << 17 << endl;
    else {
      tmp = power(N - 4);
      //			print(tmp);
      cout << (tmp.a * 17 + tmp.b * 5 + tmp.c) % MOD << endl;
    }
  }
}