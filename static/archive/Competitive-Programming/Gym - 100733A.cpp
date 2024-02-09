#include <bits/stdc++.h>
using namespace std;
int data[1000005];
int main() {
  double n, R, r;
  cin >> n >> R >> r;
  cout << fixed << setprecision(11) << n * R * r * sin(3.14159265359 / n)
       << endl;
}