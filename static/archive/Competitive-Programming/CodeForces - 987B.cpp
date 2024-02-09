#include <bits/stdc++.h>
using namespace std;
int main() {
  int x, y;
  double a, b;
  cin >> x >> y;
  // x^y .. y^x
  // y*log(x) .. x*log(y)
  if (x == y) {
    cout << "=" << endl;
    return 0;
  }
  a = y * log(x);
  b = x * log(y);
  if (abs(a - b) <= 1e-8) {
    cout << "=" << endl;
    return 0;
  }
  if (a < b) {
    cout << "<" << endl;
    return 0;
  } else {
    cout << ">" << endl;
    return 0;
  }
}