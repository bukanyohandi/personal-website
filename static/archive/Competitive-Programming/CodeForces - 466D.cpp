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
#define MOD 1000000007

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

lint T, N, H;
lint Arr[2222], Memo[2222][2222];

lint DP(int Pos, int Check) {
  if (Pos == N)
    return Check == 0;
  lint &Ret = Memo[Pos][Check];
  if (Ret != -1)
    return Ret;
  Ret = 0;
  if (Arr[Pos] + Check == H) {
    Ret += DP(Pos + 1, Check);
    if (Check > 0)
      Ret += Check * DP(Pos + 1, Check - 1);
  } else if (Arr[Pos] + Check + 1 == H) {
    Ret += DP(Pos + 1, Check) * Check;
    Ret += DP(Pos + 1, Check + 1) + DP(Pos + 1, Check);
  }
  return Ret % MOD;
}

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  // T=1;
  //	cin>>T;
  // rep(t,1,T){

  // }
  memset(Memo, -1, sizeof(Memo));
  cin >> N >> H;
  for (int i = 0; i < N; ++i)
    cin >> Arr[i];

  cout << DP(0, 0) << endl;
  //
  // for(int mulai=
  // cout<<mulai<<" : "<<"Batas->"<<Batas<<endl;
  // cout<<"MASUK\n";
  // cout<<Ok<<endl;
  return 0;
}
