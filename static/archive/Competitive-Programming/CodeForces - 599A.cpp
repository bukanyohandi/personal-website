#include <bits/stdc++.h>
using namespace std;

int main() {
  int a, b, c;
  cin >> a >> b >> c;
  cout << min(min(a + a + b + b, a + c + b), min(a + c + c + a, b + c + c + b));
}