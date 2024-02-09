#include <bits/stdc++.h>
using namespace std;
string S;
stack<char> St;
int Count, Case, Piv;
int main() {
  while (cin >> S) {
    if (S[0] == '-')
      return 0;
    Piv = Count = 0;
    while (St.size())
      St.pop();
    for (int i = 0; i < S.length(); ++i) {
      if (S[i] == '{')
        St.push('{');
      else if (St.size() && St.top() == '{')
        St.pop();
      else
        St.push('}');
    }
    while (St.size() && St.top() == '{')
      Piv++, St.pop();
    Count += (Piv + 1) / 2;
    Count += (St.size() + 1) / 2;
    cout << ++Case << ". " << Count << '\n';
  }
}