#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define fo(i, a, b) dfo(int, i, a, b)
#define fr(i, n) dfr(int, i, n)
#define fe(i, a, b) dfe(int, i, a, b)
#define fq(i, n) dfq(int, i, n)
#define nfo(i, a, b) dfo(, i, a, b)
#define nfr(i, n) dfr(, i, n)
#define nfe(i, a, b) dfe(, i, a, b)
#define nfq(i, n) dfq(, i, n)
#define dfo(d, i, a, b) for (d i = (a); i < (b); i++)
#define dfr(d, i, n) dfo(d, i, 0, n)
#define dfe(d, i, a, b) for (d i = (a); i <= (b); i++)
#define dfq(d, i, n) dfe(d, i, 1, n)
#define ffo(i, a, b) dffo(int, i, a, b)
#define ffr(i, n) dffr(int, i, n)
#define ffe(i, a, b) dffe(int, i, a, b)
#define ffq(i, n) dffq(int, i, n)
#define nffo(i, a, b) dffo(, i, a, b)
#define nffr(i, n) dffr(, i, n)
#define nffe(i, a, b) dffe(, i, a, b)
#define nffq(i, n) dffq(, i, n)
#define dffo(d, i, a, b) for (d i = (b)-1; i >= (a); i--)
#define dffr(d, i, n) dffo(d, i, 0, n)
#define dffe(d, i, a, b) for (d i = (b); i >= (a); i--)
#define dffq(d, i, n) dffe(d, i, 1, n)
#define ll long long
#define alok(n, t) ((t *)malloc((n) * sizeof(t)))
#define pf printf
#define sf scanf
#define pln pf("\n")

#define mod 1000000007
#define dim 7

ll **alokmat() {
  ll **A = alok(dim, ll *);
  fr(i, dim) A[i] = alok(dim, ll);
  return A;
}
void freemat(ll **A) {
  fr(i, dim) free(A[i]);
  free(A);
}
ll *b = alok(dim, ll);
ll **A = alokmat();

void mulv(ll **A, ll *b) {
  ll *c = alok(dim, ll);
  fr(i, dim) {
    c[i] = 0;
    fr(j, dim) {
      c[i] += A[i][j] * b[j];
      c[i] %= mod;
    }
  }
  fr(i, dim) b[i] = c[i];
  free(c);
}
void mulm(ll **a, ll **b) {
  ll **c = alokmat();
  fr(i, dim) fr(j, dim) {
    c[i][j] = 0;
    fr(k, dim) {
      c[i][j] += a[i][k] * b[k][j];
      c[i][j] %= mod;
    }
  }
  fr(i, dim) fr(j, dim) a[i][j] = c[i][j];
  freemat(c);
}
void mpow(ll **b, ll e) {
  if (!e) {
    fr(i, dim) fr(j, dim) b[i][j] = i == j;
    return;
  }
  if (e == 1)
    return;
  if (e & 1) {
    ll **c = alokmat();
    fr(i, dim) fr(j, dim) c[i][j] = b[i][j];
    ;
    mpow(b, e - 1);
    mulm(b, c);
    freemat(c);
    return;
  }
  mulm(b, b);
  mpow(b, e >> 1);
}
ll f(ll n, ll k) {
  if (n < 0)
    return 0;
  if (k == 0)
    return n == 0;
  if (k == 1)
    return n <= 2;
  if (n == 0)
    return 1;
  if (n == 1)
    return k * k;

  A[0][0] = k - 2;
  A[0][1] = k;
  A[0][2] = k * (k + 1);
  A[0][3] = k * k;
  A[0][4] = k * (k - 1);
  A[0][5] = k * (k + 1) * (k - 1);
  A[0][6] = -k * (k - 1) * (k - 2);
  A[1][0] = 0;
  A[1][1] = (2 * k - 3);
  A[1][2] = (k - 1) * (k - 1);
  A[1][3] = k * (k - 1);
  A[1][4] = (k - 1) * (k - 2);
  A[1][5] = k * (k - 1) * (k - 1);
  A[1][6] = -(k - 1) * (k - 2) * (k - 2);
  A[2][0] = 0;
  A[2][1] = 1;
  A[2][2] = 0;
  A[2][3] = 0;
  A[2][4] = 0;
  A[2][5] = 0;
  A[2][6] = 0;
  A[3][0] = 0;
  A[3][1] = 0;
  A[3][2] = 1;
  A[3][3] = 0;
  A[3][4] = 0;
  A[3][5] = 0;
  A[3][6] = 0;
  A[4][0] = 0;
  A[4][1] = (k - 2);
  A[4][2] = k * (k - 1);
  A[4][3] = k * (k - 2);
  A[4][4] = (k - 1) * (k - 1);
  A[4][5] = (k * k - k - 1) * (k - 1);
  A[4][6] = -(k * k - 3 * k + 3) * (k - 2);
  A[5][0] = 0;
  A[5][1] = 0;
  A[5][2] = 0;
  A[5][3] = 0;
  A[5][4] = 1;
  A[5][5] = 0;
  A[5][6] = 0;
  A[6][0] = 0;
  A[6][1] = 0;
  A[6][2] = 0;
  A[6][3] = 0;
  A[6][4] = 0;
  A[6][5] = 1;
  A[6][6] = 0;

  b[0] = k * k;
  b[1] = (k - 1) * (k - 1);
  b[2] = 1;
  b[3] = 0;
  b[4] = (k - 1) * (k - 1);
  b[5] = 1;
  b[6] = 0;
  mpow(A, n - 1);
  mulv(A, b);
  return *b;
}

int main() {
  int z;
  sf("%d", &z);
  fq(cas, z) {
    int n, k;
    sf("%d%d", &n, &k);
    ll ans = f(n, k) % mod;
    if (ans < 0)
      ans += mod;
    pf("%lld\n", ans);
  }
}
/*
ajaksnakakakakkasmakamakananakakakanamamamamsmsnsnsnsjsjsjsnsnsnsnsnsnsn
ajaksnakakakakkasmakamakananakakakanamamamamsmsnsnsnsjsjsjsnsnsnsnsnsnsn
ajaksnakakakakkasmakamakananakakakanamamamamsmsnsnsnsjsjsjsnsnsnsnsnsnsn
ajaksnakakakakkasmakamakananakakakanamamamamsmsnsnsnsjsjsjsnsnsnsnsnsnsn
ajaksnakakakakkasmakamakananakakakanamamamamsmsnsnsnsjsjsjsnsnsnsnsnsnsn
ajaksnakakakakkasmakamakananakakakanamamamamsmsnsnsnsjsjsjsnsnsnsnsnsnsn
ajaksnakakakakkasmakamakananakakakanamsjsjamamamsmsnsnsnsjsjsjsnsnsnsnsnsnsn
*/