#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b;
  cin >> a >> b;
  int c = min(abs(1 - b), abs(a - b));
  a *= 3;
  cout << a + c << endl;
}