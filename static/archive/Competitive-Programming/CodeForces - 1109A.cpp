#include <bits/stdc++.h>
using namespace std;
long long hasil, x, data[300005], dp[1048579][2], n;
int main() {
  cin >> n;
  dp[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    cin >> x;
    data[i] = data[i - 1] ^ x;
    if (i % 2 == 0) {
      hasil = hasil + dp[data[i]][0];
      dp[data[i]][0] += 1;
    } else {
      hasil = hasil + dp[data[i]][1];
      dp[data[i]][1] += 1;
    }
  }
  cout << hasil << endl;
}