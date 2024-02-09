#include <bits/stdc++.h>
using namespace std;
int n, data[10];
string s;
void print() {
  bool udah = false;
  for (int i = 1; i <= s.length(); ++i) {
    if (data[i] == 0) {
      if (udah)
        cout << 0;
    } else {
      cout << 1;
      udah = true;
    }
  }
  return;
}
int main() {
  cin >> s;
  for (int i = 0; i < s.length(); ++i) {
    n = max(n, s[i] - '0');
    data[i + 1] = s[i] - '0';
  }
  cout << n << endl;
  for (int i = 0; i < n; ++i) {
    if (i != 0)
      cout << " ";
    print();
    for (int j = 1; j <= s.length(); ++j) {
      if (data[j] != 0)
        data[j]--;
    }
  }
  cout << endl;
}