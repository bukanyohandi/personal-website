#include <bits/stdc++.h>
#define ll long long
#define pb(a) push_back(a)
using namespace std;
bool notprime[65536], wrong;
vector<ll> prime;
ll n, m1, m2, j, cnt;
int main() {
  for (ll i = 2; i < 65536; ++i) {
    if (!notprime[i]) {
      prime.pb(i);
      for (ll j = i * i; j < 65536; j += i) {
        notprime[j] = true;
      }
    }
  }
  while (cin >> n >> m2) {
    wrong = false;
    vector<ll> fact, piv;
    m1 = m2;
    for (int i = 0; i < prime.size() && m1 > 1; ++i) {
      if (m1 % prime[i] == 0) {
        fact.pb(prime[i]);
        piv.pb(0);
        while (m1 % prime[i] == 0) {
          piv[piv.size() - 1]++;
          m1 /= prime[i];
        }
      }
    }
    if (m1 > 1) {
      fact.pb(m1);
      piv.pb(1);
    }
    for (int i = 0; i < fact.size() && !wrong; ++i) {
      j = n;
      cnt = 0;
      while (j >= fact[i]) {
        j /= fact[i];
        cnt += j;
      }
      if (cnt < piv[i]) {
        wrong = true;
        break;
      }
    }
    if (!wrong)
      cout << m2 << " divides " << n << "!" << endl;
    else
      cout << m2 << " does not divide " << n << "!" << endl;
  }
}
