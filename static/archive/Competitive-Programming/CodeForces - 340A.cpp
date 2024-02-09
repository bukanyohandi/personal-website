#include <bits/stdc++.h>
using namespace std;
int X, Y, A, B;
int main() {
  cin >> X >> Y >> A >> B;
  X = X * Y / __gcd(X, Y);
  cout << (B / X) - ((A - 1) / X) << endl;
}