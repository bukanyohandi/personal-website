#include <bits/stdc++.h>
using namespace std;
string add(string a, string b) {
  string ret = "";
  int save = 0;
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  for (int i = 0; i < min(a.length(), b.length()); ++i) {
    save += a[i] + b[i] - 2 * '0';
    ret += (char)'0' + save % 10;
    save /= 10;
  }
  for (int i = min(a.length(), b.length()); i < a.length(); ++i) {
    save += a[i] - '0';
    ret += (char)'0' + save % 10;
    save /= 10;
  }
  for (int i = min(a.length(), b.length()); i < b.length(); ++i) {
    save += b[i] - '0';
    ret += (char)'0' + save % 10;
    save /= 10;
  }
  while (save) {
    ret += (char)'0' + save % 10;
    save /= 10;
  }
  reverse(ret.begin(), ret.end());
  return ret;
}
string subtractby1(string a) {
  reverse(a.begin(), a.end());
  for (int i = 0; i < a.length(); ++i) {
    if (a[i] != '0') {
      a[i] = (char)a[i] - 1;
      if (a[a.length() - 1] == '0')
        a.pop_back();
      if (a.length() == 0)
        a += '0';
      reverse(a.begin(), a.end());
      return a;
    }
    a[i] = '9';
  }
}
int N;
string S[1000];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  S[0] = "0";
  for (int i = 1; i <= 999; ++i) {
    S[i] = add(S[i - 1], S[i - 1]);
    if (i % 2)
      S[i] = add(S[i], "1");
    else
      S[i] = subtractby1(S[i]);
  }
  while (cin >> N) {
    cout << S[N - 1] << '\n';
  }
}