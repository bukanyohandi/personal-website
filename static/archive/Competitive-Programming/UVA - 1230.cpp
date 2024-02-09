#include <iostream>
using namespace std;
int tcdata[1005];
int powermod(int x, int y, int z) {
  int i, tmp;
  if (y == 1) {
    return x % z;
  }
  if (y % 2 == 0) {
    tmp = powermod(x, y / 2, z) % z;
    return tmp * tmp % z;
  } else {
    tmp = powermod(x, y / 2, z) % z;
    return tmp * tmp % z * x % z;
  }
}
int main() {
  int tc, a, b, c, iniapaan;
  cin >> tc;
  for (int i = 1; i <= tc; i++) {
    cin >> a >> b >> c;
    tcdata[i] = powermod(a, b, c);
  }
  cin >> iniapaan;
  for (int i = 1; i <= tc; i++) {
    cout << tcdata[i] << endl;
  }
}