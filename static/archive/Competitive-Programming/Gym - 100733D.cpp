#include <bits/stdc++.h>
using namespace std;
int N, Arr[1000006];
int main() {
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> Arr[i];
    if (i >= 5)
      Arr[i] += max(Arr[i - 3], max(Arr[i - 4], Arr[i - 5]));
    else if (i >= 4)
      Arr[i] += max(Arr[i - 3], Arr[i - 4]);
    else if (i >= 3)
      Arr[i] += Arr[i - 3];
  }
  cout << max(Arr[N], max(Arr[N - 1], Arr[N - 2])) << '\n';
}