#include <bits/stdc++.h>
using namespace std;
int main() {
  long long ans = 1, piv = 1, n, c;
  cin >> n >> c;
  for (int i = (c - 3 * n) + 1; i <= (c - 2 * n); ++i) {
    ans = ((ans * i) % 1000000007) * 6 % 1000000007;
  }
  cout << ans << endl;
}