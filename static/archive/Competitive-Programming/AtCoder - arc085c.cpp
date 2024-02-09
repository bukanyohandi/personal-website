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
#define INF 4e18

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

lint N, Source, Sink, X;
lint Cost[105], Par[105];
lint Cap[105][105], Adj[105][105];
bool Vis[105];

bool BFS() {
  lint U, V;
  memset(Vis, 0, sizeof(Vis));
  queue<int> Q;
  Q.push(Source);
  Vis[Source] = 1;
  Par[Source] = -1;
  while (!Q.empty()) {
    U = Q.front();
    Q.pop();
    for (V = 0; V <= N + 1; ++V) {
      if (Vis[V] == 0 && Cap[U][V] > 0) {
        Q.push(V);
        Par[V] = U;
        Vis[V] = 1;
      }
    }
  }
  return Vis[Sink];
}

lint Maxflow() {
  lint U, V;
  for (int i = 0; i <= N + 1; ++i)
    for (int j = 0; j <= N + 1; ++j)
      Cap[i][j] = Adj[i][j];
  lint Max_Flow = 0;
  while (BFS()) {
    lint Path_Flow = INF;
    V = Sink;
    while (V != Source) {
      U = Par[V];
      Path_Flow = min(Path_Flow, Cap[U][V]);
      V = Par[V];
    }
    V = Sink;
    while (V != Source) {
      U = Par[V];
      Cap[U][V] -= Path_Flow;
      Cap[V][U] += Path_Flow;
      V = Par[V];
    }
    Max_Flow += Path_Flow;
  }
  return Max_Flow;
}

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> Cost[i];
    if (Cost[i] > 0) {
      X += Cost[i];
      Adj[i][N + 1] = Cost[i];
    } else {
      Adj[0][i] = -Cost[i];
    }
    for (int j = 2 * i; j <= N; j += i) {
      Adj[i][j] = INF;
    }
  }
  Source = 0;
  Sink = N + 1;
  cout << X - Maxflow() << endl;
  return 0;
}
