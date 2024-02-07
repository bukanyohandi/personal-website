#include <bits/stdc++.h>
using namespace std;

int main() {
  int tc;
  cin >> tc;

  for (int t = 0; t < tc; ++t) {
    int n, m;
    cin >> n >> m;

    int memo[25][25][25];
    memset(memo, -1, sizeof(memo));
    function<int(int, int, int)> solve = [&](int apples, int last_apples,
                                             int plates) {
      if (apples == 0) {
        return 0;
      }
      if (last_apples > apples) {
        return 0;
      }
      if (plates == 1) {
        return 1;
      }
      int &ret = memo[apples][last_apples][plates];
      if (ret != -1) {
        return ret;
      }
      ret = 0;
      for (int i = last_apples; i <= n - 1; ++i) {
        ret += solve(apples - i, i, plates - 1);
      }

      return ret;
    };

    cout << solve(n, 0, m) << endl;
  }
}