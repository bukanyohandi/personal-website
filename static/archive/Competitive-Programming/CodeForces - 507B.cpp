#include <bits/stdc++.h>
using namespace std;
int main() {
  long long r, a, b, x, y;
  cin >> r >> a >> b >> x >> y;
  x = (x - a) * (x - a) + (y - b) * (y - b);
  cout << ceil(sqrt(x) / (2 * r)) << endl;
}