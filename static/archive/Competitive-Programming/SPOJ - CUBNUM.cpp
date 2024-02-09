#include <bits/stdc++.h>
using namespace std;
int Case, N, DP[100001], Cubic[47];
int main() {
  for (int i = 1; i <= 46; ++i)
    Cubic[i] = i * i * i;
  for (int i = 1; i <= 100000; ++i)
    DP[i] = 100000;
  for (int i = 1; i <= 100000; ++i)
    for (int j = 1; j <= 46 && i >= Cubic[j]; ++j)
      DP[i] = min(DP[i], DP[i - Cubic[j]] + 1);
  while (cin >> N)
    cout << "Case #" << ++Case << ": " << DP[N] << '\n';
}