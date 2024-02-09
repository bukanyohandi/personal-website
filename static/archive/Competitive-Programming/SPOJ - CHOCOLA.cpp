#include <bits/stdc++.h>
using namespace std;
int N, M, T;
long long Le, Ri, Ans, Arr[1001], Arr2[1001];
int main() {
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    cin >> N >> M;
    Ans = 0;
    N--;
    M--;
    Le = 1;
    Ri = 1;
    for (int i = 1; i <= N; ++i)
      cin >> Arr[i];
    for (int i = 1; i <= M; ++i)
      cin >> Arr2[i];
    sort(Arr + 1, Arr + N + 1);
    sort(Arr2 + 1, Arr2 + M + 1);
    while (N > 0 && M > 0) {
      if (Arr[N] > Arr2[M]) {
        Ans += Arr[N] * Le;
        Ri++;
        N--;
      } else {
        Ans += Arr2[M] * Ri;
        Le++;
        M--;
      }
    }
    while (N > 0)
      Ans += Arr[N] * Le, N--;
    while (M > 0)
      Ans += Arr2[M] * Ri, M--;
    cout << Ans << endl;
  }
}