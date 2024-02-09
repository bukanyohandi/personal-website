#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool palindrome(string s) {
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == s[s.length() - i - 1]) {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

int palindromepivot(int x, int y, string s) {
  int ans = 0;
  if (!palindrome(s))
    return ans;
  for (int i = x; i <= y; ++i) {
    if (s[i] == s[y + x - i]) {
      ans++;
    }
  }
  return ans;
}

int main() {
  int best = 0, p = 0, q = 0;
  string a;
  cin >> a;
  if (palindrome(a)) {
    cout << a << endl;
    return 0;
  } else {
    for (int i = a.length() - 1; i >= 0; --i) {
      if (palindromepivot(i, a.length() - 1, a) > best) {
        best = palindromepivot(i, a.length() - 1, a);
        p = i;
        q = a.length() - 1;
      }
    }
    for (int i = 0; i < a.length(); ++i) {
      if (palindromepivot(0, i, a) > best) {
        best = palindromepivot(0, i, a);
        p = 0;
        q = i;
      }
    }
    if (p == 0) {
      for (int i = a.length() - 1; i > q; --i) {
        cout << a[i];
      }
      cout << a << endl;
    } else {
      cout << a;
      for (int i = p - 1; i >= 0; --i) {
        cout << a[i];
      }
      cout << endl;
    }
  }
}