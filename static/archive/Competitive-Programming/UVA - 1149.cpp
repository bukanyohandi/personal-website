#include <bits/stdc++.h>
using namespace std;
int data[100005];
int main() {
  int x;
  cin >> x;
  for (int z = 0; z < x; ++z) {
    int w, n, bin = 0;
    cin >> n;
    cin >> w;
    for (int i = 0; i < n; i++) {
      cin >> data[i];
    }
    sort(data, data + n);
    int piv1 = 0, piv2 = n - 1;
    while (piv1 < piv2) {
      if (data[piv1] + data[piv2] <= w) {
        bin++;
        piv1++;
        piv2--;
      } else {
        bin++;
        piv2--;
      }
    }
    if (piv1 - piv2 == 0) {
      bin++;
    }
    cout << bin << endl;
    if (z == x - 1)
      return 0;
    cout << endl;
  }
}