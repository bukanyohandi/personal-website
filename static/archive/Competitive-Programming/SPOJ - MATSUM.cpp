#include <bits/stdc++.h>
using namespace std;
int T, N, A, B, C, D;
string S;
map<pair<int, int>, int> Data;
struct FenwickTree {
  int Matrix[1234][1234];
  inline void Reset() { memset(Matrix, 0, sizeof(Matrix)); }
  inline void Add(int A, int B, int Val) {
    for (int X = A; X <= N; X += X & -X)
      for (int Y = B; Y <= N; Y += Y & -Y)
        Matrix[X][Y] += Val;
  }
  inline int Sum(int A, int B) {
    int Ret = 0;
    for (int X = A; X; X -= X & -X)
      for (int Y = B; Y; Y -= Y & -Y)
        Ret += Matrix[X][Y];
    return Ret;
  }
  inline int Query(int X1, int Y1, int X2, int Y2) {
    return Sum(X2, Y2) + Sum(X1 - 1, Y1 - 1) - Sum(X2, Y1 - 1) -
           Sum(X1 - 1, Y2);
  }
} Bit;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    cin >> N;
    Bit.Reset();
    Data.clear();
    while (cin >> S && S != "END") {
      if (S == "SET") {
        cin >> A >> B >> C;
        Bit.Add(A + 1, B + 1, -Data[{A, B}] + C);
        Data[{A, B}] = C;
      } else {
        cin >> A >> B >> C >> D;
        cout << Bit.Query(A + 1, B + 1, C + 1, D + 1) << '\n';
      }
    }
    if (t != T)
      cout << '\n';
  }
}