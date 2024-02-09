#include <bits/stdc++.h>
using namespace std;
int data[105], data2[105];
int main() {
  int n, m;
  cin >> n >> m;
  if (m == 0 && n == 1) {
    cout << "0 0" << endl;
    return 0;
  }
  if (m == 0 || m > n * 9) {
    cout << "-1 -1" << endl;
    return 0;
  }
  for (int i = 1; i <= n; ++i) {
    if (m >= 9) {
      data[i] += 9;
      m -= 9;
    } else if (m > 0) {
      data[i] += m;
      m = 0;
      break;
    }
  }
  for (int i = 1; i <= n; ++i)
    data2[i] = data[i];
  for (int i = n; i >= 1; --i) {
    if (data2[i] > 0) {
      data2[i]--;
      data2[n]++;
      break;
    }
  }
  for (int i = n; i >= 1; --i) {
    cout << data2[i];
  }
  cout << " ";
  for (int i = 1; i <= n; ++i) {
    cout << data[i];
  }
  cout << endl;
}