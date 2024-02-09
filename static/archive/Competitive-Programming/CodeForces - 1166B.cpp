#include <bits/stdc++.h>
using namespace std;
bool primagak(int x) {
  if (x % 2 == 0)
    return false;
  for (int i = 3; i * i <= x; ++i) {
    if (x % i == 0)
      return false;
  }
  return true;
}
int dibagi(int x) {
  for (int i = 5; i * i <= x; ++i) {
    if (x % i == 0)
      return i;
  }
  return 0;
}
int main() {
  int n, a, b;
  string tmp, s1 = "aouei", s2 = "oueia", s3 = "ueiao", s4 = "eiaou",
              s5 = "iaoue";
  cin >> n;
  if (n < 25 || primagak(n) || dibagi(n) == 0) {
    cout << -1 << endl;
    return 0;
  } else {
    a = dibagi(n);
    b = n / a;
    for (int i = 0; i < a; ++i) {
      if (i % 5 == 0)
        tmp = s1;
      if (i % 5 == 1)
        tmp = s2;
      if (i % 5 == 2)
        tmp = s3;
      if (i % 5 == 3)
        tmp = s4;
      if (i % 5 == 4)
        tmp = s5;
      for (int j = 0; j < b; ++j) {
        cout << tmp[j % 5];
      }
    }
  }
}