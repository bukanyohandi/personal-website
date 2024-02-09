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

int T, N, Ans, tmp;
int DP[16777216];
string S[10000];

int Count(int Number) {
  int Ret = 0;
  for (; Number > 0; Number /= 2)
    Ret += Number % 2;
  return Ret;
}

void Add(int Pos) {
  cin >> S[Pos];
  tmp = 0;
  for (auto j : S[Pos])
    if ((tmp & 1 << (j - 'a')) == 0)
      tmp += 1 << (j - 'a');
  for (int j = tmp; j > 0; j = (j - 1) & tmp)
    DP[j] += (Count(j) % 2 ? 1 : -1);
}

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  T = 1;
  //	cin>>T;
  rep(t, 1, T) {
    cin >> N;
    for (int i = 0; i < N; ++i)
      Add(i);
    for (int i = 0; i < 24; ++i)
      for (int j = (1 << 24) - 1; j >= 0; --j)
        if ((1 << i) & j)
          DP[j] += DP[j & ((1 << 24) - (1 << i) - 1)];
    for (int i = 0; i < (1 << 24); ++i)
      Ans ^= (DP[i] * DP[i]);
    cout << Ans << endl;
  }
  return 0;
}
