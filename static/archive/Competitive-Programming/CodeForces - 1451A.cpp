#include <iostream>

using namespace std;

int main() {

  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    if (n % 2 == 0) {
      if (n > 2) {
        cout << 2 << endl;
      } else {
        cout << 1 << endl;
      }
    } else {
      if (n > 3) {
        cout << 3 << endl;
      } else if (n == 3) {
        cout << 2 << endl;
      } else if (n == 1) {
        cout << 0 << endl;
      }
    }
  }
}