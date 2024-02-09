#include <bits/stdc++.h>
#define oo 381654729
using namespace std;
int N, M, X, Ans = oo;
int A[15], C[15], Grid[15][15];

int main() {
  cin >> N >> M >> X;
  for (int i = 1; i <= N; ++i) {
    cin >> C[i];
    for (int j = 1; j <= M; ++j) {
      cin >> Grid[i][j];
    }
  }
  for (int i = 0; i < (1 << N); ++i) {
    memset(A, 0, sizeof(A));
    int Price = 0;
    for (int j = 0; j < N; ++j) {
      if (i & (1 << j)) {
        Price += C[j + 1];
        for (int k = 1; k <= M; ++k) {
          A[k] += Grid[j + 1][k];
        }
      }
    }
    bool Ok = 1;
    for (int i = 1; Ok && i <= M; ++i) {
      if (A[i] < X)
        Ok = 0;
    }
    if (Ok)
      Ans = min(Ans, Price);
  }
  if (Ans != oo)
    cout << Ans << endl;
  else
    cout << "-1\n";
}