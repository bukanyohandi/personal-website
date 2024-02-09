#include <bits/stdc++.h>
using namespace std;
int r, c, data[105][105], arr[105], tc;
int maximath(int a, int b, int c) { return max(a, max(b, c)); }
int main() {
  cin >> tc;
  while (tc--) {
    int ans = 0;
    cin >> r >> c;
    for (int i = 1; i <= r; ++i) {
      for (int j = 1; j <= c; ++j) {
        arr[j] = 0;
      }
      for (int j = 1; j <= c; ++j) {
        cin >> data[i][j];
        if (j == 1) {
          arr[j] =
              max(data[i - 1][j] + data[i][j], data[i - 1][j + 1] + data[i][j]);
        } else if (j == c) {
          arr[j] =
              max(data[i - 1][j] + data[i][j], data[i - 1][j - 1] + data[i][j]);
        } else {
          arr[j] = maximath((data[i - 1][j - 1] + data[i][j]),
                            (data[i - 1][j] + data[i][j]),
                            (data[i - 1][j + 1] + data[i][j]));
        }
      }
      for (int j = 1; j <= c; ++j) {
        data[i][j] = arr[j];
      }
    }
    for (int i = 1; i <= c; ++i) {
      ans = max(ans, data[r][i]);
    }
    cout << ans << endl;
  }
}