#include <bits/stdc++.h>
using namespace std;
int Le, Ri, K, N, Q, Sparse[100005][20];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  K = log2(N);
  for (int i = 0; i < N; ++i)
    cin >> Sparse[i][0];
  for (int j = 1; j <= K; ++j)
    for (int i = 0; i <= N - (1 << j) + 1; ++i)
      Sparse[i][j] = min(Sparse[i][j - 1], Sparse[i + (1 << (j - 1))][j - 1]);
  cin >> Q;
  for (int i = 0; i < Q; ++i) {
    cin >> Le >> Ri;
    K = log2(Ri - Le + 1);
    cout << min(Sparse[Le][K], Sparse[Ri - (1 << K) + 1][K]) << '\n';
  }
}