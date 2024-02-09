#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) {
  if (b == 0LL)
    return a;
  return gcd(b, a % b);
}
int main() {
  long long tmp = 0LL, tmp2 = 100LL, piv = -1LL;
  string s;
  cin >> s;
  for (long long i = 0LL; i < s.length(); ++i) {
    if (s[i] == '.') {
      piv = i;
    }
  }
  if (piv != -1) {
    for (long long i = piv; i < s.length() - 1; ++i) {
      s[i] = s[i + 1];
    }
    for (long long i = 0; i < s.length() - 1; ++i) {
      tmp = tmp * 10 + s[i] - '0';
    }
  } else {
    for (long long i = 0; i < s.length(); ++i) {
      tmp = tmp * 10 + s[i] - '0';
    }
  }
  for (int i = 1; i <= s.length() - piv - 1; ++i) {
    tmp2 *= 10;
  }
  if (piv != -1) {
    cout << tmp2 / gcd(tmp2, tmp) << endl;
  } else
    cout << 100 / gcd(100, tmp) << endl;
  // cout<<tmp<<" "<<s.length()-piv-1<<endl;
}