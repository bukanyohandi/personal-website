#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<string> grid(8);
  for (int i = 0; i < 8; ++i) {
    cin >> grid[i];
  }

  int ans = 0;
  function<void(int)> brute = [&](int index) {
    if (index == 64) {
      int q = 0;
      for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
          if (grid[i][j] == 'Q') {
            q++;
          }
        }
      }
      if (q == 8) {
        ans++;
      }
      return;
    }

    int x = index / 8;
    int y = index % 8;
    if (grid[x][y] == '.') {
      bool valid = true;
      for (int i = 0; i < 8; ++i) {
        if (i != x && grid[i][y] == 'Q') {
          valid = false;
        }
      }
      for (int j = 0; j < 8; ++j) {
        if (j != y && grid[x][j] == 'Q') {
          valid = false;
        }
      }
      for (int k = 1; k < 8; ++k) {
        if (x - k >= 0 && y - k >= 0 && grid[x - k][y - k] == 'Q') {
          valid = false;
        }
        if (x - k >= 0 && y + k < 8 && grid[x - k][y + k] == 'Q') {
          valid = false;
        }
        if (x + k < 8 && y - k >= 0 && grid[x + k][y - k] == 'Q') {
          valid = false;
        }
        if (x + k < 8 && y + k < 8 && grid[x + k][y + k] == 'Q') {
          valid = false;
        }
      }

      if (valid) {
        grid[x][y] = 'Q';
        brute(index + 1);
        grid[x][y] = '.';
      }
    }

    return brute(index + 1);
  };

  brute(0);

  cout << ans << endl;

  return 0;
}