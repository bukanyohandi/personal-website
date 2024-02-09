#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, ans = 0;
  cin >> n;
  if (n == 2) {
    cout << 1 << endl;
    cout << 2 << endl;
  }
  if (n == 3) {
    cout << 1 << endl;
    cout << 3 << endl;
  }
  if (n >= 4) {
    cout << n / 2 << endl;
    while (n > 3) {
      n -= 2;
      if (n == 0) {
        cout << 2;
      } else {
        cout << 2 << " ";
      }
    }
    if (n == 2) {
      cout << 2 << endl;
    }
    if (n == 3) {
      cout << 3 << endl;
    }
  }
}