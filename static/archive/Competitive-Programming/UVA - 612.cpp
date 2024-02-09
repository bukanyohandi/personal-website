#include <bits/stdc++.h>
using namespace std;
pair<pair<int, int>, string> dna[105];
int bubble(string s) {
  int ret = 0;
  for (int i = 0; i < s.length() - 1; ++i) {
    for (int j = i + 1; j < s.length(); ++j) {
      if (s[i] > s[j])
        ret++;
    }
  }
  return ret;
}
int main() {
  int n, a, b;
  cin >> n;
  for (int z = 0; z < n; ++z) {
    cin >> a >> b;
    for (int i = 1; i <= b; ++i) {
      cin >> dna[i].second;
      dna[i].first.second = i;
      dna[i].first.first = bubble(dna[i].second);
    }
    sort(dna + 1, dna + 1 + b);
    for (int i = 1; i <= b; ++i) {
      cout << dna[i].second << endl;
    }
    if (z != n - 1)
      cout << endl;
  }
}