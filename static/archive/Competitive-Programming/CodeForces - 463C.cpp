#include <bits/stdc++.h>

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back

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

int T, N, Le, Ri;
int X1, Y1, X2, Y2;
lint Ans1 = -1, Ans2 = -1;
lint Grid[2222][2222], D1[2222][2222], D2[2222][2222];
vector<pair<int, int>> Cons;

inline void Cleanse(bool First) {
  lint Sum = 0;
  rep(i, 0, (int)Cons.size() - 1) Sum += Grid[Cons[i].fs][Cons[i].sc];
  rep(i, 0, (int)Cons.size() - 1) {
    if (First)
      D1[Cons[i].fs][Cons[i].sc] = Sum;
    else
      D2[Cons[i].fs][Cons[i].sc] = Sum;
  }
  Cons.clear();
  return;
}

inline void Solve(int Case) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  rep(i, 1, N) rep(j, 1, N) cin >> Grid[i][j];
  rep(i, 1, N) {
    Le = 1;
    Ri = i;
    while (Le <= N && Ri <= N) {
      Cons.pb({Le, Ri});
      Le++;
      Ri++;
    }
    Cleanse(1);
  }
  rep(i, 2, N) {
    Le = i;
    Ri = 1;
    while (Le <= N && Ri <= N) {
      Cons.pb({Le, Ri});
      Le++;
      Ri++;
    }
    Cleanse(1);
  }
  rep(i, 1, N) {
    Le = i;
    Ri = 1;
    while (Le >= 1 && Ri <= N) {
      Cons.pb({Le, Ri});
      Le--;
      Ri++;
    }
    Cleanse(0);
  }
  rep(i, 2, N) {
    Le = N;
    Ri = i;
    while (Le >= 1 && Ri <= N) {
      Cons.pb({Le, Ri});
      Le--;
      Ri++;
    }
    Cleanse(0);
  }
  rep(i, 1, N) {
    rep(j, 1, N) {
      if ((i + j) % 2 == 1) {
        if (Ans1 < D1[i][j] + D2[i][j] - Grid[i][j]) {
          Ans1 = D1[i][j] + D2[i][j] - Grid[i][j];
          X1 = i;
          Y1 = j;
        }
      } else {
        if (Ans2 < D1[i][j] + D2[i][j] - Grid[i][j]) {
          Ans2 = D1[i][j] + D2[i][j] - Grid[i][j];
          X2 = i;
          Y2 = j;
        }
      }
    }
  }
  cout << Ans1 + Ans2 << endl;
  cout << X1 << " " << Y1 << " " << X2 << " " << Y2 << endl;
  return;
}

//  x
// y 1 2 3 4 5
// 1           1
// 2           2
// 3           3
// 4           4
// 5           5

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  T = 1;
  //	cin>>T;
  rep(t, 1, T) Solve(t);
  return 0;
}
