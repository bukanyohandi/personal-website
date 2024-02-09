#include <bits/stdc++.h>
using namespace std;
int data[105], prefix[105];
int main() {
  int n, x = 0;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> data[i];
    if (data[i] == 0) {
      x++;
    }
    prefix[i] = prefix[i - 1] + data[i];
  }
  if (x == n) {
    cout << "NO" << endl;
    return 0;
  }
  if (prefix[n] != 0) {
    cout << "YES" << endl;
    cout << 1 << endl;
    cout << 1 << " " << n << endl;
    return 0;
  }
  for (int i = 1; i <= n; ++i) {
    if (prefix[i] - prefix[i - 1] != 0) {
      x = i;
      break;
    }
  }
  cout << "YES" << endl;
  cout << 2 << endl;
  cout << 1 << " " << x << endl;
  cout << x + 1 << " " << n << endl;
}