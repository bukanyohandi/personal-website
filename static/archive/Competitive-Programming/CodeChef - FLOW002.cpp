#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b, n, i, ans[1005];
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a >> b;
    ans[i] = a % b;
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << endl;
  }
}