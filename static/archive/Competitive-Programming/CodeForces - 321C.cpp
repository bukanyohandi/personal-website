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

int T, N, A, B, Now = 1;
bool Removed[111111];
int Size[111111], CentroidP[111111], Ans[111111];
vector<int> Edge[111111], CentroidEdge[111111];
queue<int> Bfs;

void Precomp(int Now, int Par) {
  Size[Now] = 1;
  for (auto i : Edge[Now]) {
    if (i != Par && !Removed[i]) {
      Precomp(i, Now);
      Size[Now] += Size[i];
    }
  }
  return;
}

int Find(int Now) {
  Precomp(Now, -1);
  int N = Size[Now];
  bool Found = 0;
  while (!Found) {
    Found = 1;
    for (auto i : Edge[Now]) {
      if (Removed[i] || Size[i] > Size[Now])
        continue;
      if (Size[i] > N / 2) {
        Found = 0;
        Now = i;
        break;
      }
    }
  }
  return Now;
}

int Build(int Now) {
  Now = Find(Now);
  Removed[Now] = 1;
  for (auto i : Edge[Now]) {
    if (!Removed[i]) {
      i = Build(i);
      CentroidP[i] = Now;
      CentroidEdge[Now].push_back(i);
    }
  }
  return Now;
}

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  cin >> N;
  for (int i = 1; i <= N - 1; ++i) {
    cin >> A >> B;
    Edge[A].push_back(B);
    Edge[B].push_back(A);
  }
  for (int i = 1; i <= N; ++i)
    CentroidP[i] = i;
  Build(1);
  while (CentroidP[Now] != Now)
    Now = CentroidP[Now];
  Bfs.push(Now);
  while (!Bfs.empty()) {
    for (auto i : CentroidEdge[Bfs.front()]) {
      Ans[i] = Ans[Bfs.front()] + 1;
      Bfs.push(i);
    }
    Bfs.pop();
  }
  for (int i = 1; i <= N; ++i) {
    if (i != 1)
      cout << " ";
    cout << (char)(Ans[i] + 'A');
  }
  return 0;
}
