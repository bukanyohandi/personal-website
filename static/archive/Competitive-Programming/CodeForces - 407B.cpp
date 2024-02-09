#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
int N;
int P[1002];
long long DP[1002];
int main() {
  cin >> N;
  for (int i = 1; i <= N; ++i)
    cin >> P[i];
  for (int i = 1; i <= N; ++i)
    DP[i + 1] = (2 * DP[i] + 2 - DP[P[i]] + MOD) % MOD;
  cout << DP[N + 1] << endl;
}