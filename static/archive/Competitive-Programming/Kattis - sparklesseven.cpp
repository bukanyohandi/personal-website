#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> Empty;
vector<vector<pair<int, int>>> Ans, tmp;
bool Ok = 1;
bool Grid[7][7], Destroyed[7][7];
string Name[7] = {"Twilight Sparkle", "Applejack",    "Rarity", "Pinkie Pie",
                  "Fluttershy",       "Rainbow Dash", "Spike"};
void Brute(int Pos) {
  if (Pos == 7) {
    if (Ans.empty() || tmp.size() < Ans.size())
      Ans = tmp;
    return;
  }
  int Count = tmp.size();
  bool AllDestroyed = 0;
  bool Found;
  for (int i = 0; i < 7; ++i) {
    AllDestroyed |= Grid[i][Pos];
    if (Grid[i][Pos]) {
      Found = 0;
      for (int j = 0; j < Count && !Found; ++j) {
        if (Destroyed[i][j])
          continue;
        Found = 1;
        Destroyed[i][j] = 1;
        tmp[j].push_back({i, Pos});
        Brute(Pos + 1);
        Destroyed[i][j] = 0;
        tmp[j].pop_back();
      }
      if (Found)
        continue;
      Destroyed[i][Count] = 1;
      tmp.push_back({{i, Pos}});
      Brute(Pos + 1);
      Destroyed[i][Count] = 0;
      tmp.pop_back();
    }
  }
  Ok &= AllDestroyed;
  return;
}
int main() {
  for (int i = 0; i < 7; ++i)
    for (int j = 0; j < 7; ++j)
      cin >> Grid[i][j];
  Brute(0);
  if (!Ok) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  cout << Ans.size() << endl;
  for (auto i : Ans) {
    cout << i.size() << endl;
    for (auto j : i) {
      cout << Name[j.first] << " " << j.second + 1 << endl;
    }
  }
} //