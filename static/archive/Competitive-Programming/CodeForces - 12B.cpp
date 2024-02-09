#include <bits/stdc++.h>
using namespace std;
int data[10] = {};
int main() {
  long long a, b, p, c = 0LL;
  string s;
  cin >> a >> s;
  if (a == 0 && s[0] == '0' && s[1] != '0') {
    cout << "OK";
    return 0;
  }
  if (s[0] == '0') {
    cout << "WRONG_ANSWER";
    return 0;
  }
  b = stoll(s);
  while (a > 0) {
    p = a % 10;
    data[p]++;
    a = a / 10;
  }
  for (int i = 1; i <= 9; i++) {
    if (data[i] != 0) {
      c = c * 10 + i;
      data[i]--;
      break;
    }
  }
  while (data[0] != 0) {
    c = c * 10;
    data[0]--;
  }
  for (int i = 1; i <= 9; i++) {
    while (data[i] != 0) {
      c = c * 10 + i;
      data[i]--;
    }
  }
  if (c == b) {
    cout << "OK" << endl;
  } else {
    cout << "WRONG_ANSWER" << endl;
  }
}