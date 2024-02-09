#include <bits/stdc++.h>
using namespace std;
int N, K;
double L, V1, V2;
int main() {
  cin >> N >> L >> V1 >> V2 >> K;
  cout << fixed << setprecision(10)
       << (double)((V1 + V2) * L / (V1 + V2 + 2 * ((N + K - 1) / K - 1) * V1) /
                       V2 +
                   (L - (V1 + V2) * L /
                            (V1 + V2 + 2 * ((N + K - 1) / K - 1) * V1)) /
                       V1)
       << endl;
}