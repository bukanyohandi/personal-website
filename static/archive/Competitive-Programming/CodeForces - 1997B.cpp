#include <bits/stdc++.h>
using namespace std;

int main() {
  int tc;
  cin >> tc;

  for (int t = 0; t < tc; ++t) {
    int n;
    cin >> n;

    vector<vector<char>> v(2, vector<char>(n));
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < n; ++j) {
        cin >> v[i][j];
      }
    }

    int ans = 0;
    for (int i = 0; i < 2; ++i) {
      for (int j = 1; j + 1 < n; ++j) {
        if (v[i][j] == '.' && v[i][j - 1] == '.' && v[i][j + 1] == '.' &&
            v[1 - i][j] == '.' && v[1 - i][j - 1] == 'x' &&
            v[1 - i][j + 1] == 'x') {
          ans++;
        }
      }
    }

    cout << ans << endl;
  }

  return 0;
}