#include <iostream>
using namespace std;

int main() {
  int c, d, i, k, n;
  cin >> n;
  c = 0;
  d = 0;
  for (i = 1; i <= n; i++) {
    cin >> k;
    if (k == 100) {
      c++;
    } else {
      d++;
    }
  }
  if (((c % 2 == 0) && (d % 2 == 0)) ||
      ((c != 0 && c % 2 == 0) && (d % 2 == 1))) {
    cout << "YES";
  } else {
    cout << "NO";
  }
}