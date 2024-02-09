#include <bits/stdc++.h>

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define all(a) a.begin(), a.end()

// Ordered Set, Ordered Multiset
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define o_set                                                                  \
  tree<int, null_type, less<int>, rb_tree_tag,                                 \
       tree_order_statistics_node_update>
#define o_multiset                                                             \
  tree<int, null_type, less<int>, rb_tree_tag,                                 \
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

lint Power(lint A, lint B) {
  if (!B)
    return 1LL;
  lint tmp = Power(A, B >> 1);
  return tmp * tmp * (B & 1 ? A : 1);
}

lint Power(lint A, lint B, lint C) {
  if (!B)
    return 1LL;
  lint tmp = Power(A, B >> 1, C);
  return tmp * tmp % C * (B & 1 ? A : 1) % C;
}

int N, M, K, Piv, Size;
bool Vis[555][555];
char Grid[555][555];
pair<int, int> Start, tmp;
vector<pair<int, int>> Dot;
queue<pair<int, int>> Bfs;
map<int, vector<pair<int, int>>> Depth;

bool inRange(int X, int Y) { return X >= 1 && X <= N && Y >= 1 && Y <= M; }

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  cin >> N >> M >> K;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      cin >> Grid[i][j];
      if (Grid[i][j] == '.') {
        Dot.pb({i, j});
        Start = {i, j};
      }
    }
  }
  //	Start=Dot[rng()%Dot.size()];
  Vis[Start.fs][Start.sc] = 1;
  Depth[1].pb(Start);
  Bfs.push(Start);
  Piv = 2;
  while (!Bfs.empty()) {
    Size = Bfs.size();
    for (int i = 0; i < Size; ++i) {
      tmp = Bfs.front();
      Bfs.pop();
      for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
          if (abs(x) + abs(y) != 1)
            continue;
          if (!inRange(tmp.fs + x, tmp.sc + y))
            continue;
          if (Grid[tmp.fs + x][tmp.sc + y] == '#')
            continue;
          if (Vis[tmp.fs + x][tmp.sc + y])
            continue;
          Vis[tmp.fs + x][tmp.sc + y] = 1;
          Depth[Piv].pb({tmp.fs + x, tmp.sc + y});
          Bfs.push({tmp.fs + x, tmp.sc + y});
        }
      }
    }
    Piv++;
  }
  while (K > 0) {
    Piv--;
    for (int i = 0; i < min(K, (int)Depth[Piv].size()); ++i) {
      Grid[Depth[Piv][i].fs][Depth[Piv][i].sc] = 'X';
    }
    K -= min(K, (int)Depth[Piv].size());
  }
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j)
      cout << Grid[i][j];
    cout << endl;
  }
  return 0;
}
