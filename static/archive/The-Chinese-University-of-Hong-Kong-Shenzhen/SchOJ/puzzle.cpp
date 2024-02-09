#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MOD = 1e9 + 7;
const int BASE = 998244353;

int exp(int A, int B) {
  if (B == 0)
    return 1LL;
  int tmp = exp(A, B / 2);
  int pred = 1;
  if (B % 2 == 1)
    pred = A;
  return tmp * tmp % MOD * pred % MOD;
}

int H(vector<int> &v) {
  int n = v.size();
  int ret = 0;

  for (int i = 1; i <= n; ++i) {
    ret += exp(BASE, n - i) * v[i - 1];
    ret %= MOD;
  }

  return ret;
}

signed main() {
  int n;
  cin >> n;

  vector<int> a(n), b(n), c(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> c[i];
  }

  map<int, vector<int>> mv;

  int H_a = H(a);
  int H_b = H(b);
  int H_c = H(c);

  mv[H_b].push_back(0);

  for (int i = 0; i < n; ++i) {
    H_b -= exp(BASE, n - 1) * b[i];
    H_b %= MOD;

    H_b += MOD;
    H_b %= MOD;

    H_b *= BASE;
    H_b %= MOD;

    H_b += b[i];
    H_b %= MOD;

    mv[H_b].push_back(i + 1);
  }

  int ans = 2 * n + 1;

  if (!mv[(H_c - H_a + MOD) % MOD].empty())
    ans = min(ans, mv[(H_c - H_a + MOD) % MOD][0]);

  for (int i = 0; i < n; ++i) {
    H_a -= (exp(BASE, n - 1) * a[i]) % MOD;
    H_a += MOD;
    H_a %= MOD;

    H_a *= BASE;
    H_a %= MOD;

    H_a += a[i];
    H_a %= MOD;

    if (mv[(H_c - H_a + MOD) % MOD].empty())
      continue;

    ans = min(ans, i + 1 + mv[(H_c - H_a + MOD) % MOD][0]);
  }

  if (ans == 2 * n + 1) {
    cout << -1 << endl;
    return 0;
  }

  cout << ans << endl;
}
