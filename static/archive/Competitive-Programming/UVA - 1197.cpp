/*
** The holy #include <bits/stdc++.h>
*/
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>

#define endl '\n'
const double PI = 3.14159265358979323846;
using namespace std;
inline void boost() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}
int ans, A, B, N, M, grp, piv, p[30005], sz[30005];
int par(int X) {
  if (p[X] == X)
    return X;
  return p[X] = par(p[X]);
}
int main() {
  //	boost();
  //	srand(time(NULL));
  while (cin >> N >> M) {
    if (N == 0 && M == 0)
      return 0;
    ans = 0;
    for (int i = 0; i < N; ++i) {
      p[i] = i;
    }
    for (int i = 1; i <= M; ++i) {
      piv = -1;
      cin >> grp;
      cin >> A;
      A = par(A);
      for (int j = 2; j <= grp; ++j) {
        cin >> B;
        B = par(B);
        if (par(B) == 0)
          piv = B;
        else
          p[B] = A;
      }
      if (piv != -1)
        p[A] = piv;
    }
    for (int i = 0; i < N; ++i) {
      if (par(i) == 0)
        ans++;
    }
    cout << ans << endl;
  }
}