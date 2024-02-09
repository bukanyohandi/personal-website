#include <bits/stdc++.h>
using namespace std;
int memo[505][505];
string ans, ice = "welcome to code jam";
int knepsek(int idx, int len) {
  if (len == ice.length())
    return 1;
  if (idx == ans.length())
    return 0;
  if (memo[idx][len] != -1)
    return memo[idx][len];
  if (ans[idx] == ice[len]) {
    return memo[idx][len] =
               (knepsek(idx + 1, len + 1) + knepsek(idx + 1, len)) % 10000;
  } else {
    return memo[idx][len] = knepsek(idx + 1, len) % 10000;
  }
}
int main() {
  int n, fire;
  cin >> n;
  getchar();
  for (int i = 1; i <= n; ++i) {
    getline(cin, ans);
    for (int j = 0; j <= 500; ++j) {
      for (int k = 0; k <= 500; ++k) {
        memo[j][k] = -1;
      }
    }
    fire = knepsek(0, 0) % 10000;
    cout << "Case #" << i << ": ";
    if (fire > 999) {
      cout << fire << endl;
    } else if (fire > 99) {
      cout << "0" << fire << endl;
    } else if (fire > 9) {
      cout << "00" << fire << endl;
    } else {
      cout << "000" << fire << endl;
    }
  }
}