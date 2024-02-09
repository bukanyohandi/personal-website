#include <bits/stdc++.h>

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define MOD 100000000

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
using lint = long long;

mt19937 rng(time(NULL));

lint Power(lint A, lint B, lint C) {
  if (!B)
    return 1LL;
  lint tmp = Power(A, B >> 1, C);
  return tmp * tmp % C * (B & 1 ? A : 1) % C;
}

int T;
int N[3], K[3];
lint Memo[111][111][3];

lint DP(int N1, int N2, int Flag) {
  if (N1 < 0 || N2 < 0)
    return 0;
  if (N1 == 0 && N2 == 0)
    return 1;
  lint &Ret = Memo[N1][N2][Flag];
  if (Ret != -1)
    return Ret;
  Ret = 0;
  if (Flag == 1) {
    for (int i = 1; i <= min(K[1], N1); ++i)
      Ret = (Ret + DP(N1 - i, N2, 2)) % MOD;
  }
  if (Flag == 2) {
    for (int i = 1; i <= min(K[2], N2); ++i)
      Ret = (Ret + DP(N1, N2 - i, 1)) % MOD;
  }
  return Ret;
}

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  memset(Memo, -1, sizeof(Memo));
  for (int i = 1; i <= 2; ++i)
    cin >> N[i];
  for (int i = 1; i <= 2; ++i)
    cin >> K[i];
  cout << (DP(N[1], N[2], 1) + DP(N[1], N[2], 2)) % MOD << endl;
  return 0;
}
