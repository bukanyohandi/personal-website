#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
double x;
int main() {
  int n, x1, y1, x2, y2, x3, y3, x4, y4, a, b, c, d, e, f, det;
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  cout << "INTERSECTING LINES OUTPUT" << endl;
  while (n--) {
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    a = y1 - y2;
    b = x2 - x1;
    c = x2 * y1 - x1 * y2;
    d = y3 - y4;
    e = x4 - x3;
    f = x4 * y3 - x3 * y4;
    x = (double)(a * 1.0 / d);
    if (x * d == a && x * e == b && x * f == c) {
      cout << "LINE" << endl;
      continue;
    }
    det = a * e - b * d;
    if (!det) {
      cout << "NONE" << endl;
      continue;
    }
    cout << fixed << setprecision(2) << "POINT "
         << (double)((c * e - b * f) * 1.0 / (det * 1.0)) << " "
         << (double)((a * f - c * d) * 1.0 / (det * 1.0)) << endl;
  }
  cout << "END OF OUTPUT" << endl;
  return 0;
}