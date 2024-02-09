#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define fs first
#define sc second.first
#define th second.second
#define con 222222
using namespace std;
ll f[con], fh[con], sum[con], Row, Col, K, A, B, C;
vector<pair<ll, pair<ll, ll>>> vec;
inline ll combin(ll x, ll y) { return (f[x] * fh[y]) % MOD * fh[x - y] % MOD; }
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  f[0] = f[1] = fh[0] = 1LL;
  fh[200000] = 750007460;
  for (int i = 2; i <= 200000; ++i)
    f[i] = (i * f[i - 1]) % MOD;
  for (int i = 199999; i > 0; --i)
    fh[i] = (fh[i + 1] * (i + 1)) % MOD;
  cin >> Row >> Col >> K;
  for (int i = 1; i <= K; ++i) {
    cin >> A >> B;
    C = (A + B + MOD) % MOD;
    vec.push_back({A, {B, C}});
  }
  vec.push_back({Row, {Col, Row + Col}});
  sort(vec.begin(), vec.end());
  for (int i = 1; i <= K + 1; ++i) {
    sum[i] = combin(vec[i - 1].th - 2, vec[i - 1].fs - 1);
    for (int j = 1; j < i; ++j) {
      if (vec[j - 1].sc <= vec[i - 1].sc)
        sum[i] = ((sum[i] - sum[j] *
                                (combin(vec[i - 1].th - vec[j - 1].th,
                                        vec[i - 1].fs - vec[j - 1].fs) +
                                 MOD) %
                                MOD) +
                  MOD) %
                 MOD;
    }
  }
  cout << sum[K + 1] << endl;
}