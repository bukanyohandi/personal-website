#include <bits/stdc++.h>
using namespace std;
int main() {
  int tmp, a, b, x, y, z, moves = 0;
  cin >> a >> b;
  x = y = z = b;
  while (x < a || y < a || z < a) {
    tmp = min(x, min(y, z));
    if (x == tmp)
      x = y + z - 1;
    else if (y == tmp)
      y = x + z - 1;
    else
      z = x + y - 1;
    moves++;
  }
  cout << moves << endl;
}