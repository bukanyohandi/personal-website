#include <iostream>
using namespace std;

int c;

int decrease(int x, int y) {
  if (y > 0) {
    c = c + 1;
    ;
    return decrease(x + 1, y - x);
  } else {
    return c;
  }
}

int main() {
  int x;
  cin >> x;
  cout << decrease(1, x);
  return 0;
}