#include <bits/stdc++.h>
using namespace std;

int main() {
  int tc;
  cin >> tc;

  for (int t = 0; t < tc; ++t) {
    int N, x, ans = 0;
    vector<int> V;

    cin >> N;
    V.resize(N);
    for (int i = 0; i < N; ++i) {
      cin >> x;
      if (x % 2 == 1) {
        ans++;
      }
    }
    cout << ans << endl;
  }
}