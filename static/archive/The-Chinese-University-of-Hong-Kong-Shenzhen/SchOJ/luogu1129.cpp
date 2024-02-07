#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;
  for (int tc = 0; tc < T; ++tc) {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cin >> grid[i][j];
      }
    }

    int run = 1;
    for (int i = 0; i < n; ++i) {
      run *= (i + 1);
    }
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);

    bool ans = false;
    for (int i = 0; i < run; ++i) {
      bool valid = true;
      for (int j = 0; j < n; ++j) {
        if (grid[p[j]][j] == 0) {
          valid = false;
        }
      }

      ans |= valid;
      next_permutation(p.begin(), p.end());
    }

    cout << (ans ? "Yes" : "No") << endl;
  }

  return 0;
}
