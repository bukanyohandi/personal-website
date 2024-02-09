#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000;
// C(N+K-1,K-1)
long long N, K, Ans, GCD;
vector<long long> Numerator;
int main() {
  while (cin >> N >> K) {
    if (N == 0 && K == 0)
      return 0;
    Ans = 1;
    Numerator.clear();
    for (int i = 1; i <= K - 1; ++i)
      Numerator.push_back(N + i);
    for (int i = 1; i <= K - 1; ++i) {
      long long Pivot = i;
      int j = 0;
      while (Pivot != 1) {
        GCD = __gcd(Pivot, Numerator[j]);
        if (GCD != 1) {
          Pivot /= GCD;
          Numerator[j] /= GCD;
        }
        j++;
      }
    }
    for (auto i : Numerator) {
      Ans *= i;
      Ans %= MOD;
    }
    cout << Ans << endl;
  }
}