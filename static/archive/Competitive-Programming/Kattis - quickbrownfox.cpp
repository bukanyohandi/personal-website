#include <bits/stdc++.h>
using namespace std;
int tc, cnt;
string x;
bool alph[26];
int main() {
  cin >> tc;
  getchar();
  while (tc--) {
    getline(cin, x);
    cnt = 0;
    for (int i = 0; i < 26; ++i)
      alph[i] = false;
    for (int i = 0; i < x.length(); ++i) {
      if (x[i] >= 'A' && x[i] <= 'A' + 25)
        alph[x[i] - 'A'] = true;
      if (x[i] >= 'a' && x[i] <= 'a' + 25)
        alph[x[i] - 'a'] = true;
    }
    for (int i = 0; i < 26; ++i) {
      if (alph[i])
        cnt++;
    }
    if (cnt == 26) {
      cout << "pangram" << endl;
    } else {
      cout << "missing ";
      for (int i = 0; i < 26; ++i) {
        if (!alph[i]) {
          char t = 'a' + i;
          cout << t;
        }
      }
      cout << endl;
    }
  }
}