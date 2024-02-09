#include <bits/stdc++.h>
/*
        Karya anak bangsa yang paling agung
        Author : Yohandi or... bukan..
*/

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define endl "\n"

#define all(a) a.begin(), a.end()
#define lb(a, x) (lower_bound(all(a), x) - a.begin())
#define ub(a, x) (upper_bound(all(a), x) - a.begin())

#define rep(a, x, y) for (int a = (int)x; a <= (int)y; ++a)
#define repd(a, x, y, d) for (int a = (int)x; a <= (int)y; a += d)
#define res(a, x, y) for (int a = (int)x; a >= (int)y; --a)
#define resd(a, x, y, d) for (int a = (int)x; a >= (int)y; a -= d)
#define MOD 1000000007

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
lint Memo[2][2][250][5001];
string Input;

lint DP(bool Compare, bool Flag, int Pos, int Check) {
  lint &Ret = Memo[Compare][Flag][Pos][Check];
  if (Ret != -1)
    return Ret;
  Ret = 0;
  // cout<<Ret<<endl;
  if (Pos == Input.length())
    return Ret = Compare && Check > 2500;
  if (Flag) {
    if (Compare) {
      for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= 9; ++j) {
          Ret = (Ret + DP(Compare, Flag, Pos + 1, Check + j - i)) % MOD;
        }
      }
    } else {
      for (int i = 0; i <= 9; ++i) {
        Ret += DP(false, Flag, Pos + 1, Check) % MOD;
        for (int j = i + 1; j <= 9; ++j) {
          Ret = (Ret + DP(true, Flag, Pos + 1, Check + j - i)) % MOD;
        }
      }
    }
  } else {
    if (Compare) {
      for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= Input[Pos] - '0'; ++j) {
          Ret = (Ret + DP(true, j < Input[Pos] - '0', Pos + 1, Check + j - i)) %
                MOD;
        }
      }
    } else {
      for (int i = 0; i <= 9; ++i) {
        for (int j = i; j <= Input[Pos] - '0'; ++j) {
          Ret =
              (Ret + DP(i != j, j < Input[Pos] - '0', Pos + 1, Check + j - i)) %
              MOD;
        }
      }
    }
  }
  return Ret;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> Input;
  for (int i = 0; i <= 249; ++i) {
    for (int j = 0; j <= 5000; ++j) {
      Memo[0][0][i][j] = Memo[0][1][i][j] = Memo[1][0][i][j] =
          Memo[1][1][i][j] = -1;
    }
  }
  cout << DP(0, 0, 0, 2500) << endl;
  return 0;
}