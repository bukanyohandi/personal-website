#include <bits/stdc++.h>
using namespace std;
int beda[200005], data[200005], data2[200005];
int main() {
  int n, xmin = 0;
  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    cin >> beda[i];
  }
  data[0] = 0;
  for (int i = 1; i < n; ++i) {
    data[i] = data[i - 1] + beda[i - 1];
    xmin = min(xmin, data[i]);
  }
  xmin = 1 - xmin;
  for (int i = 0; i < n; i++) {
    data[i] += xmin;
    data2[i] = data[i];
  }
  sort(data2, data2 + n);
  for (int i = 0; i < n; i++) {
    if (data2[i] != i + 1) {
      cout << -1 << endl;
      return 0;
    }
  }
  for (int i = 0; i < n - 1; i++) {
    cout << data[i] << " ";
  }
  cout << data[n - 1] << endl;
}