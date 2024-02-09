#include <iostream>
#include <string.h>
using namespace std;
int T, N, M, X;
unsigned DP[1010101];
int comp(const int *a, const int *b) { return (*a) - (*b); }
int main() {
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    cin >> M;
    cin >> N;
    memset(DP, -1, sizeof(DP));
    DP[0] = 0;
    for (int i = 1; i <= N; ++i) {
      cin >> X;
      for (int j = M - 1; j >= 0; --j) {
        if (DP[j] != -1) {
          if (DP[j + X] > DP[j] + 1) {
            DP[j + X] = DP[j] + 1;
          }
        }
      }
    }
    while (DP[M] == -1)
      M++;
    cout << M << " " << DP[M] << endl;
  }
}