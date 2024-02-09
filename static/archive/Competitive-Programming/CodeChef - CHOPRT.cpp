#include <bits/stdc++.h>
using namespace std;
char ans[100005];
int main() {
  long long n, i, a, b;
  cin >> n;
  for (i = 1; i <= n; i++) {
    cin >> a >> b;
    if (a == b) {
      ans[i] = '=';
    }
    if (a < b) {
      ans[i] = '<';
    }
    if (a > b) {
      ans[i] = '>';
    }
  }
  for (i = 1; i <= n; i++) {
    cout << ans[i] << endl;
  }
}