#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, a, b, c, sum1 = 0, sum2 = 0, sum3 = 0;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a >> b >> c;
    sum1 += a;
    sum2 += b;
    sum3 += c;
  }
  if (sum1 == 0 && sum2 == 0 && sum3 == 0) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
}