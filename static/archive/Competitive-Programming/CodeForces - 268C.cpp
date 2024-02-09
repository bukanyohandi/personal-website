#include <bits/stdc++.h>
using namespace std;
int N, M;
int main() {
  cin >> N >> M;
  if (N > M)
    swap(N, M);
  cout << N + 1 << endl;
  for (int i = 0; i <= N; ++i) {
    cout << i << " " << N - i << endl;
  }
}