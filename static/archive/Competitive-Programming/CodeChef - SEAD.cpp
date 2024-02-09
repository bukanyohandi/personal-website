#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; ++i)
using namespace std;
int K, N, M, T, D, L, R, Le, Ri, Mid, A[101010], Sparse[101010][20];
inline bool G(int X) {
  int L = X, R = ::R - 1;
  K = log2(R - L + 1);
  return max(Sparse[L][K], Sparse[R - (1 << K) + 1][K]) <= D;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  K = log2(N);
  rep(i, 1, N) cin >> A[i];
  rep(i, 1, N - 1) Sparse[i][0] = A[i + 1] - A[i];
  rep(j, 1, K) rep(i, 1, N - (1 << j)) Sparse[i][j] =
      max(Sparse[i][j - 1], Sparse[i + (1 << (j - 1))][j - 1]);
  cin >> M;
  rep(i, 1, M) {
    cin >> T >> D;
    R = 1;
    Le = 2;
    Ri = N;
    while (Le <= Ri) {
      Mid = (Le + Ri) / 2;
      if (A[Mid] <= T) {
        R = Mid;
        Le = Mid + 1;
      } else
        Ri = Mid - 1;
    }
    L = R;
    Le = 1;
    Ri = R - 1;
    while (Le <= Ri) {
      Mid = (Le + Ri) / 2;
      if (G(Mid)) {
        L = Mid;
        Ri = Mid - 1;
      } else
        Le = Mid + 1;
    }
    cout << L << '\n';
  }
}