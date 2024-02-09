#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> H(N);
  for (int i = 0; i < N; ++i) {
    cin >> H[i];
  }

  int mx = H[0];
  int ans = 1;

  for (int i = 0; i < N; ++i) {
    if (mx < H[i]) {
      mx = H[i];
      ans = i + 1;
    }
  }

  cout << ans << endl;
}