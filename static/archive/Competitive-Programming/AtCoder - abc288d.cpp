#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;
  cin >> N >> K;

  vector<int> A(N + 1, 0);
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    A[i] += A[i - 1];
  }

  int Q;
  cin >> Q;
  for (int i = 0; i < Q; ++i) {
    int L, R;
    cin >> L >> R;
    // cout << A[R] - A[L - 1] << endl;
    if ((A[R] - A[L - 1]) % K == 0) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}