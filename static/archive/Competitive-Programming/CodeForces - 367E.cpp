#include <bits/stdc++.h>
/*
        Karya anak bangsa yang paling agung
        Author : Yohandi or... bukan..
*/

using lint = long long;
#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define endl "\n"
const lint MODX = 1000000007;
const lint MOD = MODX * MODX;

#define all(a) a.begin(), a.end()
#define lb(a, x) (lower_bound(all(a), x) - a.begin())
#define ub(a, x) (upper_bound(all(a), x) - a.begin())

#define rep(a, x, y) for (int a = (int)x; a <= (int)y; ++a)
#define repd(a, x, y, d) for (int a = (int)x; a <= (int)y; a += d)
#define res(a, x, y) for (int a = (int)x; a >= (int)y; --a)
#define resd(a, x, y, d) for (int a = (int)x; a >= (int)y; a -= d)

// Ordered Set, Ordered Multiset
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define o_set                                                                  \
  tree<int, null_type, less<int>, rb_tree_tag,                                 \
       tree_order_statistics_node_update>
#define o_multiset                                                             \
  tree<int, null_type, less_equal<int>, rb_tree_tag,                           \
       tree_order_statistics_node_update>
using namespace __gnu_pbds;
// .order_of_key(x) -> Number of elements less than x
// * .find_by_order(k) -> Kth smallest element (0-based)
// .erase(x) -> Remove all elements equal to x

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

mt19937 rng(time(NULL));

lint Power(lint A, lint B, lint C) {
  if (!B)
    return 1LL;
  lint tmp = Power(A, B >> 1, C);
  return tmp * tmp % C * (B & 1 ? A : 1) % C;
}

lint N, M, X, tmp;
lint Ans, Piv, Memo[2][333][333][2];

void Add(lint &Target, lint Num) {
  Target += Num;
  if (Target >= MODX)
    Target -= MODX;
}

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  cin >> N >> M >> X;
  if (N > M) {
    cout << 0 << endl;
  } else {
    swap(N, M);
    Memo[0][0][0][0] = 1;
    for (int i = 0; i < N; ++i) {
      // memset(Memo[1-i%2],0,sizeof(Memo[1-i%2]));
      for (int j = 0; j <= M; ++j)
        for (int k = 0; k <= j; ++k)
          for (int l = 0; l <= 1; ++l)
            Memo[1 - i % 2][j][k][l] = 0;
      for (int j = 0; j <= M; ++j) {
        for (int k = 0; k <= j; ++k) {
          for (int l = 0; l <= 1; ++l) {
            tmp = l;
            if (X == i + 1)
              tmp = 1;
            Piv = Memo[i % 2][j][k][l];
            if (Piv == 0)
              continue;
            Memo[1 - i % 2][j][k][l] += Piv;
            Memo[1 - i % 2][j][k][l] %= MOD;
            Memo[1 - i % 2][j + 1][k][tmp] += Piv;
            Memo[1 - i % 2][j + 1][k][tmp] %= MOD;
            if (j > k)
              Memo[1 - i % 2][j][k + 1][l] += Piv,
                  Memo[1 - i % 2][j][k + 1][l] %= MOD;
            if (j >= k)
              Memo[1 - i % 2][j + 1][k + 1][tmp] += Piv,
                  Memo[1 - i % 2][j + 1][k + 1][tmp] %= MOD;
          }
        }
      }
    }
    Ans = Memo[N % 2][M][M][1] % MODX;
    for (int i = 1; i <= M; ++i)
      Ans = (Ans * i) % MODX;
    cout << Ans << endl;
  }
  return 0;
}
