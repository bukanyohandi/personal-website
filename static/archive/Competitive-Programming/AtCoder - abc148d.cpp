#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, cur = 1;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    if (A[i] == cur) {
      cur++;
    }
  }
  if (cur == 1) {
    cout << -1 << endl;
  } else {
    cout << N - cur + 1 << endl;
  }
}