#include <iostream>
using namespace std;
long long x, tmp = 1LL;
int main() {
  cin >> x;
  for (int i = 2; i <= x; ++i) {
    tmp = (tmp * i) % 1000000007;
  }
  cout << tmp << endl;
}