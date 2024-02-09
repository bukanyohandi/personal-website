#include <bits/stdc++.h>
using namespace std;
int N, Le, Ri;
long long M, Sum, Ans;
long long Arr[300000];
int main() {
  cin >> N >> M;
  for (int i = 0; i < N; ++i)
    cin >> Arr[i];
  while (true) {
    while (Ri < N && Sum <= M) {
      Ans = max(Ans, Sum);
      Sum += Arr[Ri];
      Ri++;
    }
    while (Sum > M) {
      Sum -= Arr[Le];
      Le++;
    }
    if (Ri == N)
      break;
  }
  if (Sum <= M)
    Ans = max(Ans, Sum);
  cout << Ans << endl;
}