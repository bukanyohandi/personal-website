#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  vector<string> w(t);
  for (int i = 0; i < t; ++i) {
    cin >> w[i];
    if (w[i] == "and" || w[i] == "not" || w[i] == "that" || w[i] == "the" ||
        w[i] == "you") {
      cout << "Yes\n";
      return 0;
    }
  }
  cout << "No\n";
  return 0;
}