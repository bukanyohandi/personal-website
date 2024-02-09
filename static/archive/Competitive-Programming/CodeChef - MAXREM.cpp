#include <bits/stdc++.h>
using namespace std;
long long piv, maks = 0, n, data[200005];
int main() {
  while (cin >> n) {
    maks = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> data[i];
      maks = max(maks, data[i]);
    }
    sort(data + 1, data + 1 + n);
    for (int i = n; i >= 0; --i) {
      if (data[i] != maks) {
        cout << data[i] << endl;
        break;
      }
    }
  }
}