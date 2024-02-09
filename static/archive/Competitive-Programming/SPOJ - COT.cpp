#include <bits/stdc++.h>
/*
        Karya anak bangsa yang paling agung
        Author : Yohandi or... bukan..
*/

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define Mid ((Low + High) / 2)

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

struct Node {
  int Val = 0;
  Node *Left;
  Node *Right;
} * Root[111111];

int T, N, Q, U, V, UV, K, Log;
int Arr[111111], Kth[111111], P[111111], Depth[111111];
int Par[111111][22];
pair<int, int> Ord[111111];
vector<int> Edg[111111];

inline void Build0(Node *Now, int Low, int High) {
  Now->Val = 0;
  if (Low == High)
    return;
  Now->Left = new Node();
  Now->Right = new Node();
  Build0(Now->Left, Low, Mid);
  Build0(Now->Right, Mid + 1, High);
  return;
}

inline void Build1(Node *Prev, Node *Now, int Low, int High, int Pos) {
  if (Low == High) {
    Now->Val = 1;
    return;
  }
  Now->Left = new Node();
  Now->Right = new Node();
  if (Kth[Pos] <= Mid) {
    Now->Right = Prev->Right;
    Build1(Prev->Left, Now->Left, Low, Mid, Pos);
  } else {
    Now->Left = Prev->Left;
    Build1(Prev->Right, Now->Right, Mid + 1, High, Pos);
  }
  Now->Val = Now->Left->Val + Now->Right->Val;
  return;
}

inline int Query(Node *A, Node *B, Node *C, Node *D, int Low, int High) {
  if (Low == High)
    return Ord[Low].fs;
  int tmp = A->Left->Val + B->Left->Val - C->Left->Val - D->Left->Val;
  if (K <= tmp) {
    return Query(A->Left, B->Left, C->Left, D->Left, Low, Mid);
  } else {
    K -= tmp;
    return Query(A->Right, B->Right, C->Right, D->Right, Mid + 1, High);
  }
}

inline void DFS(int Now, int Parent) {
  Build1(Root[Parent], Root[Now], 1, N, Now);
  Depth[Now] = Depth[Parent] + 1;
  P[Now] = Parent;
  for (auto i : Edg[Now]) {
    if (i != Parent) {
      DFS(i, Now);
    }
  }
  return;
}

inline void BuildLCA() {
  P[1] = 1;
  memset(Par, -1, sizeof(Par));
  for (int i = 1; i <= N; ++i)
    Par[i][0] = P[i];
  for (int j = 1; j <= Log; ++j)
    for (int i = 1; i <= N; ++i)
      if (Par[i][j - 1] != -1 && Par[Par[i][j - 1]][j - 1] != -1)
        Par[i][j] = Par[Par[i][j - 1]][j - 1];
  P[1] = 0;
  return;
}

inline int Ancestor(int U, int Diff) {
  for (int j = Log; j >= 0; --j)
    if (Diff & (1 << j))
      U = Par[U][j];
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
  return Par[U][0];
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  T = 1;
  //	cin>>T;
  rep(t, 1, T) {
    cin >> N >> Q;
    Log = log2(N);
    for (int i = 0; i <= N; ++i)
      Root[i] = new Node();
    for (int i = 1; i <= N; ++i) {
      cin >> Arr[i];
      Ord[i].fs = Arr[i];
      Ord[i].sc = i;
    }
    sort(Ord + 1, Ord + N + 1);
    for (int i = 1; i <= N; ++i) {
      Kth[Ord[i].sc] = i;
    }
    Build0(Root[0], 1, N);
    for (int i = 1; i <= N - 1; ++i) {
      cin >> U >> V;
      Edg[U].pb(V);
      Edg[V].pb(U);
    }
    DFS(1, 0);
    BuildLCA();
    for (int i = 1; i <= Q; ++i) {
      cin >> U >> V >> K;
      UV = LCA(U, V);
      cout << Query(Root[U], Root[V], Root[UV], Root[P[UV]], 1, N) << endl;
    }
  }
  return 0;
}

////