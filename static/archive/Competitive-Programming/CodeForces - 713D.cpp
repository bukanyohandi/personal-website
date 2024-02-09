#include <bits/stdc++.h>

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define min3(a, b, c) min(a, min(b, c))
#define min4(a, b, c, d) min(min(a, b), min(c, d))
#define max3(a, b, c) max(a, max(b, c))
#define max4(a, b, c, d) max(max(a, b), max(c, d))

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

int T, N, M, K, L, Q, X1, X2, Y1, Y2, Le, Ri, Mid, Save;
short Log2[1111] = {-1};
short Arr[1001][1001];
short Sparse[1001][1001][10][10];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> M;
  for (int i = 1; i <= 1000; ++i)
    Log2[i] = Log2[i >> 1] + 1;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      cin >> Arr[i][j];
      if (Arr[i][j] == 1) {
        Sparse[i][j][0][0] =
            min3(Sparse[i - 1][j - 1][0][0], Sparse[i - 1][j][0][0],
                 Sparse[i][j - 1][0][0]) +
            1;
      }
    }
  }
  for (int j = 1; j <= Log2[M]; ++j)
    for (int x = 1; x <= N; ++x)
      for (int y = 1; y <= M - (1 << j) + 1; ++y)
        Sparse[x][y][0][j] = max(Sparse[x][y][0][j - 1],
                                 Sparse[x][y + (1 << (j - 1))][0][j - 1]);
  for (int i = 1; i <= Log2[N]; ++i)
    for (int j = 0; j <= Log2[M]; ++j)
      for (int x = 1; x <= N - (1 << i) + 1; ++x)
        for (int y = 1; y <= M - (1 << j) + 1; ++y)
          Sparse[x][y][i][j] = max(Sparse[x][y][i - 1][j],
                                   Sparse[x + (1 << (i - 1))][y][i - 1][j]);
  cin >> Q;
  auto Query = [&](int X1, int Y1, int X2, int Y2) {
    int K = Log2[X2 - X1 + 1];
    int L = Log2[Y2 - Y1 + 1];
    return max4(Sparse[X1][Y1][K][L], Sparse[X2 - (1 << K) + 1][Y1][K][L],
                Sparse[X1][Y2 - (1 << L) + 1][K][L],
                Sparse[X2 - (1 << K) + 1][Y2 - (1 << L) + 1][K][L]);
  };
  for (int i = 1; i <= Q; ++i) {
    cin >> X1 >> Y1 >> X2 >> Y2;
    Save = 0;
    Le = 1;
    Ri = min(X2 - X1 + 1, Y2 - Y1 + 1);
    while (Le <= Ri) {
      Mid = (Le + Ri) >> 1;
      if (Query(X1 + Mid - 1, Y1 + Mid - 1, X2, Y2) >= Mid) {
        Save = Mid;
        Le = Mid + 1;
      } else {
        Ri = Mid - 1;
      }
    }
    cout << Save << '\n';
  }
  return 0;
}
