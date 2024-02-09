#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
  int n;
  cin >> n;

  if (n == 1) {
    cout << 0 << endl;
  } else if (n == 2) {
    cout << 3 << endl;
  } else {
    int second_last = 0;
    int last = 3;
    int tmp;
    for (int i = 3; i <= n; ++i) {
      tmp = (2 * last + 3 * second_last) % 1000000007;
      second_last = last;
      last = tmp;
    }

    cout << last << endl;
  }
}