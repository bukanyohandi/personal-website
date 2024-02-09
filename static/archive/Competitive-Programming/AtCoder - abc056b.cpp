#include <iostream>
using namespace std;
int W, a, b;
int abs(int a, int b) {
  int tmp = a - b;
  if (tmp < 0)
    tmp *= -1;
  return tmp;
}
int main() {
  cin >> W >> a >> b;
  cout << max(0, abs(a, b) - W) << endl;
}