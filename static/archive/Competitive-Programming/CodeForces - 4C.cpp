#include <bits/stdc++.h>
using namespace std;
int main() {
  map<string, int> nama;
  int n;
  string s;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> s;
    if (nama[s] == 0) {
      nama[s]++;
      cout << "OK" << endl;
    } else {
      cout << s << nama[s] << endl;
      nama[s]++;
    }
  }
}