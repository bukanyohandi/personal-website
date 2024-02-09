#include <bits/stdc++.h>
using namespace std;
int data[4];
int main() {
  int n;
  string s;
  cin >> n;
  cin >> s;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'U')
      data[0]++;
    if (s[i] == 'D')
      data[1]++;
    if (s[i] == 'L')
      data[2]++;
    if (s[i] == 'R')
      data[3]++;
  }
  int ans = 0;
  ans += 2 * min(data[2], data[3]);
  ans += 2 * min(data[0], data[1]);
  cout << ans << endl;
}