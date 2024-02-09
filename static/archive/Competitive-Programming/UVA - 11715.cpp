#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, piv = 0;
  double a, b, c;
  while (cin >> n) {
    if (n == 0)
      return 0;
    piv++;
    cin >> a >> b >> c;
    if (n == 1) {
      cout << fixed << setprecision(3) << "Case " << piv << ": "
           << (a + b) * c / 2 << " " << (b - a) / c << endl;
    }
    if (n == 2) {
      cout << fixed << setprecision(3) << "Case " << piv << ": "
           << (b * b - a * a) / (2 * c) << " " << (b - a) / c << endl;
    }
    if (n == 3) {
      cout << fixed << setprecision(3) << "Case " << piv << ": "
           << a + (-2 * a + sqrt(4 * a * a + 8 * b * c)) / 2 << " "
           << (-2 * a + sqrt(4 * a * a + 8 * b * c)) / (2 * b) << endl;
    }
    if (n == 4) {
      cout << fixed << setprecision(3) << "Case " << piv << ": "
           << a - (2 * a - sqrt(4 * a * a - 8 * b * c)) / 2 << " "
           << (2 * a - sqrt(4 * a * a - 8 * b * c)) / (2 * b) << endl;
    }
  }
}