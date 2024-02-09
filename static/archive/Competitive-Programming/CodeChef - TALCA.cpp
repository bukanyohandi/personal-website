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

int T, N, U, V, R, Q;
int Par[222222][22], Parent[222222], Depth[222222] = {-1};
vector<int> Cons;
vector<int> Edg[222222];
pair<int, int> Ans;

void DFS(int Now, int Prev) {
  Depth[Now] = Depth[Prev] + 1;
  Parent[Now] = Prev;
  for (auto i : Edg[Now])
    if (i != Prev)
      DFS(i, Now);
}

void Build() {
  memset(Par, -1, sizeof(Par));
  Parent[1] = 1;
  rep(j, 0, (int)log2(N) - 1) {
    rep(i, 1, N) {
      if (j == 0)
        Par[i][j] = Parent[i];
      else if (Par[i][j - 1] != -1)
        Par[i][j] = Par[Par[i][j - 1]][j - 1];
    }
  }
}

int LCA(int U, int V) {
  if (Depth[U] < Depth[V])
    swap(U, V);
  int Diff = Depth[U] - Depth[V];
  res(j, log2(N), 0) {
    if (Diff >= (1 << j)) {
      U = Par[U][j];
      Diff -= (1 << j);
    }
  }
  if (U == V)
    return U;
  res(j, log2(N), 0) {
    if (Par[U][j] != Par[V][j]) {
      U = Par[U][j];
      V = Par[V][j];
    }
  }
  return Par[U][0];
}

int Dist(int U, int V) {
  return (Depth[U] - Depth[LCA(U, V)]) + (Depth[V] - Depth[LCA(U, V)]);
}

int SpecialDist() {
  Ans = {222222, 222222};
  Cons.clear();
  Cons.pb(R);
  Cons.pb(U);
  Cons.pb(V);
  Cons.pb(LCA(R, U));
  Cons.pb(LCA(R, V));
  Cons.pb(LCA(U, V));
  rep(i, 0, 5) Ans = min(
      Ans, {Dist(Cons[i], R) + Dist(Cons[i], U) + Dist(Cons[i], V), Cons[i]});
  return Ans.sc;
}

inline void Solve(int Case) {
  cin >> N;
  rep(i, 1, N - 1) {
    cin >> U >> V;
    Edg[U].pb(V);
    Edg[V].pb(U);
  }
  Depth[0] = -1;
  DFS(1, 0);
  Build();
  cin >> Q;
  rep(i, 1, Q) {
    cin >> R >> U >> V;
    cout << SpecialDist() << endl;
  }
  return;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  T = 1;
  //	cin>>T;
  rep(t, 1, T) Solve(t);
  return 0;
}
