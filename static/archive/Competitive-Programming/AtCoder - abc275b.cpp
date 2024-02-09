#include <bits/stdc++.h>
using namespace std;

int main() {
  long long A, B, C, D, E, F;

  cin >> A >> B >> C >> D >> E >> F;

  A %= 998244353;
  B %= 998244353;
  C %= 998244353;
  D %= 998244353;
  E %= 998244353;
  F %= 998244353;

  cout << ((((A * B) % 998244353 * C) % 998244353) -
           (((D * E) % 998244353 * F) % 998244353) + 998244353) %
              998244353
       << endl;
}