#include <bits/stdc++.h>
using namespace std;
bool prima(int x) {
  if (x == 1)
    return false;
  if (x % 2 == 0 && x > 2)
    return false;
  for (int i = 3; i * i <= x; i += 2) {
    if (x % i == 0)
      return false;
  }
  return true;
}
int main() {
  int n;
  while (cin >> n) {
    if (n == 0)
      return 0;
    cout << setw(3) << n << "! =";
    int piv2 = 1;
    for (int i = 1; i <= n; ++i) {
      int piv = 0;
      if (prima(i)) {
        for (int j = i; j <= n; j *= i) {
          piv += n / j;
        }
        if (piv2 % 16 == 0) {
          cout << endl;
          cout << setw(9) << piv;
        } else {
          cout << setw(3) << piv;
        }
        piv2++;
      }
    }
    cout << endl;
  }
}