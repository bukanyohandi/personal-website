#include <iostream>
using namespace std;
int le, ri;
string s;
int main() {
  cin >> s;
  for (int i = 0; i < s.length() && le == 0; ++i) {
    if (s[i] == 'A')
      le = i + 1;
  }
  for (int i = s.length() - 1; i >= 0 && ri == 0; --i) {
    if (s[i] == 'Z')
      ri = i + 1;
  }
  if (le < ri)
    cout << ri - le + 1 << endl;
}