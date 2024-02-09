#include <bits/stdc++.h>
using namespace std;
int N, Ans, Le, Ri;
int Arr[2002];
int main() {
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> Arr[i];
    Arr[i] = abs(Arr[i]);
  }
  for (int i = 1; i <= N; ++i) {
    Le = 0;
    Ri = 0;
    for (int j = 1; j < i; ++j)
      if (Arr[j] < Arr[i])
        Le++;
    for (int j = i + 1; j <= N; ++j)
      if (Arr[j] < Arr[i])
        Ri++;
    Ans += min(Le, Ri);
  }
  cout << Ans << endl;
}