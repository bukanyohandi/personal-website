#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;
using lint = long long;

lint Power(lint A, lint B, lint C) {
  if (!B)
    return 1;
  lint tmp = Power(A, B >> 1, C);
  return tmp * tmp % C * (B & 1 ? A : 1) % C;
}

int N, K, Q, Arr[202020], T, A, B, C, D, Piv, LowModulo[505][505];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> Q;
  K = sqrt(N);
  for (int q = 0; q < Q; ++q) {
    cin >> T;
    if (T == 1) {
      cin >> A >> B >> C;
      if (B <= K)
        LowModulo[B][A] += C;
      else
        for (int i = A; i <= N; i += B)
          Arr[i] += C;
    } else {
      cin >> D;
      Piv = 0;
      for (int i = 1; i <= K; ++i)
        Piv += LowModulo[i][D % i];
      cout << Piv + Arr[D] << '\n';
    }
  }
  return 0;
}
