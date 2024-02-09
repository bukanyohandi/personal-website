#include <bits/stdc++.h>
using namespace std;
int N, Q, V, L, R, O, Idx, Ones, Zeroes;
int Arr[100001];
int BIT[27][100001];
long long Ans;
string Op;
void Add(int Pos, int Idx, int Val) {
  for (; Idx <= N; Idx += Idx & -Idx)
    BIT[Pos][Idx] += Val;
  return;
}
int Query(int Pos, int Idx) {
  int Ret = 0;
  for (; Idx > 0; Idx -= Idx & -Idx)
    Ret += BIT[Pos][Idx];
  return Ret;
}
int main() {
  cin >> N >> Q;
  for (int i = 1; i <= N; i++)
    cin >> Arr[i];
  for (int j = 0; j < 27; j++) {
    for (int i = 1; i <= N; i++) {
      if (Arr[i] & (1 << j)) {
        Add(j, i, 1);
      }
    }
  }
  for (int i = 1; i <= Q; i++) {
    cin >> O;
    if (O == 1) {
      cin >> V >> Idx;
      for (int j = 0; j < 27; j++) {
        if (Arr[Idx] & (1 << j)) {
          Add(j, Idx, -1);
        }
      }
      Arr[Idx] = V;
      for (int j = 0; j < 27; j++) {
        if (Arr[Idx] & (1 << j)) {
          Add(j, Idx, 1);
        }
      }
    }
    if (O == 2) {
      cin >> Op >> L >> R;
      Ans = 0;
      for (int j = 0; j < 27; j++) {
        Ones = Query(j, R) - Query(j, L - 1);
        Zeroes = (R - L + 1) - Ones;
        if (Op == "AND") {
          Ans += (long long)(1 << j) * Ones * (Ones - 1) / 2;
        }
        if (Op == "XOR") {
          Ans += (long long)(1 << j) * Ones * Zeroes;
        }
        if (Op == "OR") {
          Ans += (long long)(1 << j) * Ones * (Ones - 1) / 2;
          Ans += (long long)(1 << j) * Ones * Zeroes;
        }
      }
      cout << Ans << endl;
    }
  }
}