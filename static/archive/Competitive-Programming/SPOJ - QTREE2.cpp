#include <bits/stdc++.h>
/*
        Karya anak bangsa yang paling agung
        Author : Yohandi or... bukan..
*/

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

int T, N, U, V, C, K, UV, Log;
int P[11111], Depth[11111], Dist[11111];
int Par[11111][22];
vector<pair<int, int>> Edg[11111];
string S;

inline void DFS(int Now, int Parent) {
  P[Now] = Parent;
  if (Now != Parent)
    Depth[Now] = Depth[Parent] + 1;
  for (auto i : Edg[Now]) {
    if (i.fs != Parent) {
      Dist[i.fs] = Dist[Now] + i.sc;
      DFS(i.fs, Now);
    }
  }
  return;
}

inline void Build() {
  P[1] = 1;
  memset(Par, -1, sizeof(Par));
  for (int i = 1; i <= N; ++i)
    Par[i][0] = P[i];
  for (int j = 1; j <= Log; ++j)
    for (int i = 1; i <= N; ++i)
      if (Par[i][j - 1] != -1 && Par[Par[i][j - 1]][j - 1] != -1)
        Par[i][j] = Par[Par[i][j - 1]][j - 1];
}

inline int Ancestor(int U, int Diff) {
  for (int j = Log; j >= 0; --j) {
    if (Diff & (1 << j)) {
      U = Par[U][j];
      Diff -= (1 << j);
    }
  }
  return U;
}

inline int LCA(int U, int V) {
  if (Depth[U] < Depth[V])
    swap(U, V);
  U = Ancestor(U, Depth[U] - Depth[V]);
  if (U == V)
    return U;
  for (int j = Log; j >= 0; --j) {
    if (Par[U][j] != Par[V][j]) {
      U = Par[U][j];
      V = Par[V][j];
    }
  }
  return P[U];
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  T = 1;
  cin >> T;
  rep(t, 1, T) {
    cin >> N;
    Log = log2(N);
    for (int i = 1; i <= N; ++i)
      Edg[i].clear();
    for (int i = 1; i < N; ++i) {
      cin >> U >> V >> C;
      Edg[U].pb({V, C});
      Edg[V].pb({U, C});
    }
    DFS(1, -1);
    Build();
    while (cin >> S) {
      if (S == "DONE")
        break;
      cin >> U >> V;
      UV = LCA(U, V);
      if (S == "DIST") {
        cout << Dist[U] + Dist[V] - 2 * Dist[UV] << endl;
      }
      if (S == "KTH") {
        cin >> K;
        if (K <= Depth[U] - Depth[UV] + 1) {
          cout << Ancestor(U, K - 1) << endl;
        } else {
          cout << Ancestor(V, (Depth[V] - Depth[UV]) -
                                  (K - (Depth[U] - Depth[UV] + 1)))
               << endl;
        }
      }
    }
  }
  return 0;
}
