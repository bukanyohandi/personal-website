#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;
int judgebego[30];
int main() {
  string s;
  cin >> s;
  for (int i = 0; i < s.length(); ++i) {
    judgebego[s[i] - 'a']++;
  }
  sort(judgebego, judgebego + 26);
  cout << s.length() - judgebego[25] - judgebego[24] << endl;
}