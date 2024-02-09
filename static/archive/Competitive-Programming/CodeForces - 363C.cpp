#include <bits/stdc++.h>
using namespace std;
int i, j;
string S;
vector<pair<char, int>> Vec;
vector<pair<int, int>> Pos;
int main() {
  cin >> S;
  for (i = 0; i < S.length(); ++i) {
    for (j = i + 1; j < S.length(); ++j)
      if (S[i] != S[j])
        break;
    Vec.push_back({S[i], j - i});
    i = j - 1;
  }
  for (i = 0; i < Vec.size(); ++i)
    if (Vec[i].second > 2)
      Vec[i].second = 2;
  for (i = 0; i < Vec.size(); ++i) {
    if (Vec[i].second != 2)
      continue;
    for (j = i + 1; j < Vec.size(); ++j)
      if (Vec[i].second != Vec[j].second)
        break;
    Pos.push_back({i, j - 1});
    i = j - 1;
  }
  for (pair<int, int> p : Pos) {
    for (i = p.first + 1; i <= p.second; i += 2)
      Vec[i].second = 1;
  }
  for (i = 0; i < Vec.size(); ++i)
    for (j = 0; j < Vec[i].second; ++j)
      cout << Vec[i].first;
  puts("");
}