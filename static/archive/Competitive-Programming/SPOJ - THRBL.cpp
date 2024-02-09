#include <bits/stdc++.h>
using namespace std;
int Le, Ri, K, N, Q, Ans, Sparse[50505][35];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> Q;
  K = log2(N);
  for (int i = 1; i <= N; ++i)
    cin >> Sparse[i][1];
  for (int j = 1; j <= K; ++j)
    for (int i = 1; i <= N - (1 << j) + 1; ++i)
      Sparse[i][j + 1] = max(Sparse[i][j], Sparse[i + (1 << (j - 1))][j]);
  for (int i = 1; i <= Q; ++i) {
    cin >> Le >> Ri;
    Ri--;
    K = log2(Ri - Le + 1) + 1;
    if (max(Sparse[Le][K], Sparse[Ri - (1 << (K - 1)) + 1][K]) <= Sparse[Le][1])
      Ans++;
  }
  cout << Ans << '\n';
}