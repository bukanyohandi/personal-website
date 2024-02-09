#include <bits/stdc++.h>
using namespace std;
int best, piv1, piv2, fs, sc, n, m, data[100005];
int main() {
  while (cin >> n >> m) {
    fs = sc = 0;
    best = 0;
    for (int i = 1; i <= m; ++i) {
      cin >> data[i];
    }
    piv1 = piv2 = data[1];
    while (piv1 <= m && piv2 <= m) {
      while (piv2 <= m && data[piv1] + n - 1 >= data[piv2]) {
        if ((piv2 - piv1 + 1) > best) {
          best = piv2 - piv1 + 1;
          fs = data[piv1];
          sc = data[piv2];
        }
        piv2++;
      }
      piv1++;
    }
    cout << best << " " << fs << " " << sc << endl;
  }
}