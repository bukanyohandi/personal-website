#include <bits/stdc++.h>
using namespace std;

#define int long long

const long long MOD = 998244353;

long long pow(long long A, long long B) {
  if (B == 0)
    return 1;
  if (B == 1)
    return A;
  long long tmp = pow(A, B / 2);
  return tmp * tmp % MOD * (B % 2 == 1 ? A : 1) % MOD;
}

int N, M, K;
long long memo[1005][1005];

long long f(int cur, int K) {
  if (cur == N)
    return 1;
  if (K == 0)
    return 0;
  if (cur > N)
    return f(N - (cur - N), K);

  long long &ret = memo[cur][K];

  if (ret != -1)
    return ret;

  ret = 0;
  for (int i = 1; i <= M; ++i) {
    ret += f(cur + i, K - 1) * pow(M, MOD - 2);
    ret %= MOD;
  }

  return ret;
}

signed main() {
  memset(memo, -1, sizeof(memo));

  cin >> N >> M >> K;

  if (M * K < N) {
    cout << 0 << endl;
    return 0;
  }

  cout << f(0, K) << endl;
}