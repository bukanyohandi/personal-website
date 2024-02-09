#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b, c;
  cin >> a >> b;
  c = max(a, b);
  if (c == 1) {
    cout << "1/1" << endl;
  }
  if (c == 2) {
    cout << "5/6" << endl;
  }
  if (c == 3) {
    cout << "2/3" << endl;
  }
  if (c == 4) {
    cout << "1/2" << endl;
  }
  if (c == 5) {
    cout << "1/3" << endl;
  }
  if (c == 6) {
    cout << "1/6" << endl;
  }
}