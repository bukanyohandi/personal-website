#include <bits/stdc++.h>
using namespace std;
long long a, b, tmp, tmp2;
string s;
void solvex(long long x) {
  long long tm;
  if (x == 0)
    return;
  solvex(x / b);
  tm = x % b;
  if (tm >= 10) {
    if (tm == 10)
      cout << "A";
    if (tm == 11)
      cout << "B";
    if (tm == 12)
      cout << "C";
    if (tm == 13)
      cout << "D";
    if (tm == 14)
      cout << "E";
    if (tm == 15)
      cout << "F";
  } else {
    cout << tm;
  }
  return;
}
bool check() {
  for (int i = 0; i < s.length(); ++i) {
    tmp = 17;
    if (s[i] - '0' <= 9 && s[i] - '0' >= 0) {
      tmp = s[i] - '0';
    }
    if (s[i] - 'A' <= 5 && s[i] - 'A' >= 0) {
      tmp = s[i] - 'A' + 10;
    }
    if (tmp >= a)
      return false;
  }
  return true;
}
long long to10() {
  long long tm = 0;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] - '0' <= 9 && s[i] - '0' >= 0) {
      tmp = s[i] - '0';
    }
    if (s[i] - 'A' <= 5 && s[i] - 'A' >= 0) {
      tmp = s[i] - 'A' + 10;
    }
    tm = tm * a + tmp;
  }
  return tm;
}
void convert() {
  tmp2 = to10();
  if (tmp2 == 0) {
    cout << tmp2;
  } else {
    solvex(tmp2);
  }
  return;
}
int main() {
  while (cin >> a >> b >> s) {
    if (check()) {
      cout << s << " base " << a << " = ";
      convert();
      cout << " base " << b << endl;
    } else {
      cout << s << " is an illegal base " << a << " number" << endl;
    }
  }
}