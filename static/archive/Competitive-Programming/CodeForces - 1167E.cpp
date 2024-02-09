#include <bits/stdc++.h>
using namespace std;
long long Ans, Piv, N, K, X, Kiri[1000005], Kanan[1000005], Arr[1000005];
int main() {
  cin >> N >> K;
  Kiri[K + 1] = N + 1;
  X = N;
  Ans = K;
  for (long long i = 1; i <= N; ++i) {
    cin >> Arr[i];
    if (Kiri[Arr[i]] == 0)
      Kiri[Arr[i]] = i;
    Kanan[Arr[i]] = i;
  }
  for (long long i = K; i >= 1; --i) {
    if (X < Kanan[i]) {
      Ans = K - i + 1;
      Piv = i + 1;
      break;
    } else if (Kiri[i] != 0)
      X = Kiri[i];
  }
  X = 0;
  for (long long i = K; i >= 1; --i)
    if (Kiri[i] == 0)
      Kiri[i] = Kiri[i + 1];
  for (long long i = 1; i < K; ++i) {
    Piv = max(Piv, i + 2);
    if (Kanan[i] == 0) {
      Ans += K - (Piv - 1) + 1;
      continue;
    }
    if (Kiri[i] < X)
      break;
    while (Piv - 1 <= K && Kanan[i] > Kiri[Piv])
      Piv++;
    Ans += K - (Piv - 1) + 1;
    if (Kanan[i] != 0)
      X = Kanan[i];
  }
  cout << Ans << endl;
}