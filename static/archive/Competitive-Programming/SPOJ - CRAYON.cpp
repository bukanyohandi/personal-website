#include <bits/stdc++.h>
using namespace std;
map<int, int> Compressed;
int N, Piv;
int Refer[1000001], I[1000001], L[1000001], R[1000001], BITL[2000001],
    BITR[2000001];
char Op[1000001];
void AddL(int Idx, int Val) {
  for (; Idx <= Piv; Idx += Idx & -Idx)
    BITL[Idx] += Val;
  return;
}
void AddR(int Idx, int Val) {
  for (; Idx <= Piv; Idx += Idx & -Idx)
    BITR[Idx] += Val;
  return;
}
int QueryL(int Idx) {
  int Ret = 0;
  for (; Idx > 0; Idx -= Idx & -Idx)
    Ret += BITL[Idx];
  return Ret;
}
int QueryR(int Idx) {
  int Ret = 0;
  for (; Idx > 0; Idx -= Idx & -Idx)
    Ret += BITR[Idx];
  return Ret;
}
int main() {
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> Op[i];
    if (Op[i] == 'C') {
      cin >> I[i];
    } else {
      cin >> L[i] >> R[i];
      Compressed[L[i]]++;
      Compressed[R[i]]++;
      if (Op[i] == 'D')
        Refer[++Piv] = i;
    }
  }
  for (int i = 1; i <= N; i++)
    I[i] = Refer[I[i]];
  Piv = 0;
  for (auto &i : Compressed)
    i.second = ++Piv;
  for (int i = 1; i <= N; i++) {
    if (Op[i] == 'D') {
      AddL(Compressed[L[i]], 1);
      AddR(Compressed[R[i]], 1);
    } else if (Op[i] == 'C') {
      AddL(Compressed[L[I[i]]], -1);
      AddR(Compressed[R[I[i]]], -1);
    } else {
      cout << QueryL(Compressed[R[i]]) - QueryR(Compressed[L[i]] - 1) << endl;
    }
  }
}