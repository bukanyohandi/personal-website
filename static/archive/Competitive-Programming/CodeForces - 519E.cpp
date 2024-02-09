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

int T, N, Q, U, V, Piv;
int Depth[111111], Parent[111111], Par[111111][22], Size[111111];
vector<int> Edg[111111];

int DFS(int Now, int Prev) {
  bool GrandChild = 1;
  Parent[Now] = Prev;
  Depth[Now] = (Prev == -1) ? (0) : (Depth[Prev] + 1);
  for (auto i : Edg[Now]) {
    if (i != Prev) {
      Size[Now] += DFS(i, Now);
    }
  }
  return Size[Now];
}

void Build() {
  memset(Par, -1, sizeof(Par));
  for (int i = 1; i <= N; ++i)
    Par[i][0] = Parent[i];
  for (int j = 1; j <= log2(N); ++j)
    for (int i = 1; i <= N; ++i)
      if (Par[i][j - 1] != -1 && Par[Par[i][j - 1]][j - 1] != -1)
        Par[i][j] = Par[Par[i][j - 1]][j - 1];
}

int Anc(int U, int Diff) {
  for (int j = log2(N); j >= 0; --j) {
    if (Diff & (1 << j))
      U = Par[U][j];
  }
  return U;
}

int LCA(int U, int V) {
  if (Depth[U] < Depth[V])
    swap(U, V);
  int Diff = Depth[U] - Depth[V];
  U = Anc(U, Diff);
  if (U == V)
    return U;
  for (int j = log2(N); j >= 0; --j) {
    if (Par[U][j] == -1 || Par[V][j] == -1)
      continue;
    if (Par[U][j] != Par[V][j]) {
      U = Par[U][j];
      V = Par[V][j];
    }
  }
  return Parent[U];
}

int Dist(int U, int V) { return Depth[U] + Depth[V] - 2 * Depth[LCA(U, V)]; }

inline void Solve(int Case) {
  cin >> N;
  for (int i = 1; i <= N - 1; ++i) {
    cin >> U >> V;
    Edg[U].pb(V);
    Edg[V].pb(U);
  }
  for (int i = 1; i <= N; ++i)
    Size[i] = 1;
  DFS(1, -1);
  Build();
  cin >> Q;
  for (int i = 1; i <= Q; ++i) {
    cin >> U >> V;
    if (U == V) {
      cout << N << endl;
    } else if (Dist(U, V) % 2 == 1) {
      cout << 0 << endl;
    } else if (Depth[U] == Depth[V]) {
      cout << N - Size[Anc(U, Depth[U] - Depth[LCA(U, V)] - 1)] -
                  Size[Anc(V, Depth[V] - Depth[LCA(U, V)] - 1)]
           << endl;
    } else {
      if (Depth[U] < Depth[V])
        swap(U, V);
      cout << Size[Anc(U, Dist(U, V) / 2)] - Size[Anc(U, Dist(U, V) / 2 - 1)]
           << endl;
    }
  }
  return;
}

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  T = 1;
  //	cin>>T;
  rep(t, 1, T) Solve(t);
  return 0;
}
