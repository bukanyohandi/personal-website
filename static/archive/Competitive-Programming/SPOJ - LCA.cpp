#include <bits/stdc++.h>
using namespace std;
int N, Q, P[1001], X, Y, T;
bool V[1001];
int main() {
  cin >> T;
  V[1] = true;
  for (int t = 1; t <= T; ++t) {
    cin >> N;
    for (int i = 1; i <= N; ++i)
      P[i] = i;
    for (int i = 1; i <= N; ++i) {
      cin >> X;
      for (int j = 0; j < X; ++j)
        cin >> Y, P[Y] = i;
    }
    printf("Case %d:\n", t);
    cin >> Q;
    for (int i = 1; i <= Q; ++i) {
      for (int j = 2; j <= N; ++j)
        V[j] = false;
      cin >> X >> Y;
      do {
        V[X] = true;
        X = P[X];
      } while (P[X] != X);
      V[X] = true;
      while (!V[Y])
        Y = P[Y];
      cout << Y << endl;
    }
  }
}