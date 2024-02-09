#include <bits/stdc++.h>
#define INF 381654729
using namespace std;
int Le, Ri, K, N, Q, Sparse[2][101010][25];
inline double dMax(double A, double B) { return A > B ? A : B; }
inline void Build(bool Type) {
  for (int j = 1; j <= K; ++j)
    for (int i = 1; i <= N - (1 << j) + 1; ++i)
      if (Type)
        Sparse[Type][i][j + 1] =
            max(Sparse[Type][i][j], Sparse[Type][i + (1 << (j - 1))][j]);
      else
        Sparse[Type][i][j + 1] =
            min(Sparse[Type][i][j], Sparse[Type][i + (1 << (j - 1))][j]);
}
inline int Query(bool Type, int Le, int Ri) {
  if (Ri < Le)
    return -1;
  K = log2(Ri - Le + 1) + 1;
  if (Type)
    return max(Sparse[Type][Le][K], Sparse[Type][Ri - (1 << (K - 1)) + 1][K]);
  else
    return min(Sparse[Type][Le][K], Sparse[Type][Ri - (1 << (K - 1)) + 1][K]);
}
inline double Ans() {
  int A = Query(1, 1, Le - 1), B = Query(1, Ri + 1, N), C = Query(1, Le, Ri),
      D = Query(0, Le, Ri);
  double Time = (double)(C + D) / 2;
  if (A != -1)
    Time = dMax(Time, A + D);
  if (B != -1)
    Time = dMax(Time, B + D);
  return Time;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  K = log2(N);
  for (int i = 1; i <= N; ++i) {
    cin >> Sparse[0][i][1];
    Sparse[1][i][1] = Sparse[0][i][1];
  }
  Build(0);
  Build(1);
  cin >> Q;
  for (int i = 1; i <= Q; ++i) {
    cin >> Le >> Ri;
    Le++;
    Ri++;
    cout << fixed << setprecision(1) << Ans() << '\n';
  }
}