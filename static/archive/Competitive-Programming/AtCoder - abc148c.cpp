#include <bits/stdc++.h>
using namespace std;

int main() {
  long long A, B;
  cin >> A >> B;
  cout << A / __gcd(A, B) * B << endl;
}