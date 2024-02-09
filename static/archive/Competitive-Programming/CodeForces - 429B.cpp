#include <bits/stdc++.h>

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
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

int T, N, M, Piv, Ans;
int Arr[1000][1000], Memo[4][1000][1000];

int DP(int Pos, int R, int C) {
  int &Ret = Memo[Pos][R][C];
  if (Ret != 0)
    return Ret;
  Ret = Arr[R][C];
  if (Pos == 0) {
    if (R == N - 1 && C == M - 1)
      return Ret;
    Ret += max(R < N - 1 ? DP(Pos, R + 1, C) : 0,
               C < M - 1 ? DP(Pos, R, C + 1) : 0);
  }
  if (Pos == 1) {
    if (R == 0 && C == M - 1)
      return Ret;
    Ret +=
        max(R > 0 ? DP(Pos, R - 1, C) : 0, C < M - 1 ? DP(Pos, R, C + 1) : 0);
  }
  if (Pos == 2) {
    if (R == N - 1 && C == 0)
      return Ret;
    Ret +=
        max(R < N - 1 ? DP(Pos, R + 1, C) : 0, C > 0 ? DP(Pos, R, C - 1) : 0);
  }
  if (Pos == 3) {
    if (R == 0 && C == 0)
      return Ret;
    Ret += max(R > 0 ? DP(Pos, R - 1, C) : 0, C > 0 ? DP(Pos, R, C - 1) : 0);
  }
  return Ret;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  T = 1;
  //	cin>>T;
  rep(t, 1, T) {
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j)
        cin >> Arr[i][j];
    DP(0, 0, 0);
    DP(1, N - 1, 0);
    DP(2, 0, M - 1);
    DP(3, N - 1, M - 1);
    // for(int k=0;k<4;++k){
    //     for(int i=0;i<N;++i){
    //         for(int j=0;j<M;++j)
    //             cout<<Memo[k][i][j]<<" ";
    //         cout<<endl;
    //     }
    // }
    for (int i = 1; i < N - 1; ++i) {
      for (int j = 1; j < M - 1; ++j) {
        Ans = max(Ans, Memo[3][i][j - 1] + Memo[0][i][j + 1] +
                           Memo[2][i + 1][j] + Memo[1][i - 1][j]);
        Ans = max(Ans, Memo[3][i - 1][j] + Memo[0][i + 1][j] +
                           Memo[2][i][j - 1] + Memo[1][i][j + 1]);
      }
    }
    cout << Ans << endl;
  }
  return 0;
}
