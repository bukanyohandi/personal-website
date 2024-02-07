#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/print-the-longest-palindromic-prefix-of-a-given-string/
string LongestPalindromicPrefix(string str) {
  string temp = str + '?';
  reverse(str.begin(), str.end());

  temp += str;
  int n = temp.length();
  int lps[n];

  fill(lps, lps + n, 0);

  for (int i = 1; i < n; i++) {
    int len = lps[i - 1];
    while (len > 0 && temp[len] != temp[i]) {
      len = lps[len - 1];
    }
    if (temp[i] == temp[len]) {
      len++;
    }
    lps[i] = len;
  }

  return temp.substr(0, lps[n - 1]);
}

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;

    int le = 0;
    int ri = (int)s.length() - 1;
    while (le < ri && s[le] == s[ri]) {
      le++;
      ri--;
    }
    if (le >= ri) {
      cout << s << endl;
      continue;
    }

    string tmp = s.substr(le, ri - le + 1);
    string consider_1 = LongestPalindromicPrefix(tmp);
    reverse(tmp.begin(), tmp.end());
    string consider_2 = LongestPalindromicPrefix(tmp);

    string ans = "";
    for (int i = 0; i < le; ++i) {
      ans.push_back(s[i]);
    }
    if ((int)consider_1.length() >= (int)consider_2.length()) {
      ans += consider_1;
    } else {
      ans += consider_2;
    }
    for (int i = ri + 1; i < (int)s.length(); ++i) {
      ans.push_back(s[i]);
    }

    cout << ans << endl;
  }

  return 0;
}
