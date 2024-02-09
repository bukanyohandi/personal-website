#include <bits/stdc++.h>
#define oo 381456729
#define min3(a, b, c) min(a, min(b, c))
using namespace std;
int Ans, N, M, Grid[105][105];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> M;
  Ans = oo;
  for (int i = 0; i <= N + 1; ++i)
    for (int j = 0; j <= M + 1; ++j)
      if (i == 0 || j == 0 || i == N + 1 || j == M + 1)
        Grid[i][j] = oo;
      else
        cin >> Grid[i][j];
  for (int i = 2; i <= N; ++i)
    for (int j = 1; j <= M; ++j)
      Grid[i][j] = Grid[i][j] +
                   min3(Grid[i - 1][j - 1], Grid[i - 1][j], Grid[i - 1][j + 1]);
  for (int j = 1; j <= M; ++j)
    Ans = min(Ans, Grid[N][j]);
  cout << Ans << '\n';
}