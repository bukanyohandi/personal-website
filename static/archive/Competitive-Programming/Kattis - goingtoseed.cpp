#include <bits/stdc++.h>
using namespace std;
int N, L, Mid[3], R, Seg;
bool W1, W2;
int main() {
  cin >> N;
  L = 1;
  R = N;
  while (R - L + 1 > 4) {
    Seg = R - L + 1;
    Mid[0] = L + Seg / 4 + (Seg % 4 >= 1);
    Mid[1] = Mid[0] + Seg / 4 + (Seg % 4 >= 3);
    Mid[2] = Mid[1] + Seg / 4 + (Seg % 4 >= 2);
    cout << "Q " << Mid[0] + 1 << " " << Mid[2] << " " << Mid[1] + 1 << " " << R
         << endl;
    cin >> W1 >> W2;
    if (W1 && W2) {
      L = Mid[1];
      R = Mid[2] + 1;
    } else if (W1) {
      L = Mid[0];
      R = Mid[1] + 1;
    } else if (W2) {
      L = Mid[2];
    } else {
      R = Mid[0] + 1;
    }
    L = max(L, 1);
    R = min(R, N);
  }
  cout << "Q " << min(L + 1, R) << " " << min(L + 2, R) << " " << min(L + 2, R)
       << " " << R << endl;
  cin >> W1 >> W2;
  if (W1 && W2)
    cout << "A " << min(L + 2, R);
  else if (W1)
    cout << "A " << min(L + 1, R);
  else if (W2)
    cout << "A " << R << endl;
  else
    cout << "A " << L << endl;
}