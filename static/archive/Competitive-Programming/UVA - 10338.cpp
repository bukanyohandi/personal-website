#include <bits/stdc++.h>
using namespace std;
int data[26];
int main() {
  int tc;
  long long ans;
  string s;
  cin >> tc;
  for (int z = 1; z <= tc; ++z) {
    cin >> s;
    ans = 1;
    for (int i = 0; i < 26; ++i)
      data[i] = 0;
    cout << "Data set " << z << ": ";
    for (int i = 0; i < s.length(); ++i) {
      ans *= (i + 1);
      data[s[i] - 'A']++;
      ans /= data[s[i] - 'A'];
    }
    cout << ans << endl;
  }
}