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

int T, N, M, U, V, Time, Ans;
int P[10000], Size[10000], Disc[10000], Low[10000], Child[10000];
vector<int> Cons;
vector<int> Edg[10000], TEdg[10000];
bool Tag[10000];

int DFS(int U, int Parent) {
  P[U] = Parent;
  Disc[U] = Low[U] = Time++;
  for (auto V : Edg[U]) {
    if (Disc[V] == -1) {
      Size[U] += DFS(V, U);
      TEdg[U].pb(V);
      if (Low[V] > Disc[U])
        Tag[V] = 1;
      Low[U] = min(Low[U], Low[V]);
    } else if (V != Parent) {
      Low[U] = min(Low[U], Disc[V]);
    }
  }
  return Size[U];
}

void DFS2(int U, int Parent) {
  if (Tag[U]) {
    Ans -= Size[U];
    return;
  }
  for (auto V : TEdg[U]) {
    if (V != Parent)
      DFS2(V, U);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  //	T=1;
  //	cin>>T;
  //	rep(t,1,T) Solve(t);
  cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    Disc[i] = -1;
    Size[i] = 1;
  }
  for (int i = 1; i <= M; ++i) {
    cin >> U >> V;
    Edg[U].pb(V);
    Edg[V].pb(U);
  }
  DFS(0, -1);
  Ans = N;
  DFS2(0, -1);
  cout << Ans << endl;
  return 0;
}
