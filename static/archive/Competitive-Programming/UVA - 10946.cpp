#include <bits/stdc++.h>
using namespace std;
multiset<pair<int, char>> Set;
char Grid[50][50];
int R, C, Size, Case;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};
char Last;
bool inRange(int X, int Y) { return X >= 0 && X < R && Y >= 0 && Y < C; }
void Flood(int X, int Y) {
  if (!inRange(X, Y) || Grid[X][Y] != Last)
    return;
  Size++;
  Grid[X][Y] = '.';
  for (int i = 0; i < 4; ++i) {
    Flood(X + dx[i], Y + dy[i]);
  }
}
int main() {
  while (cin >> R >> C) {
    if (R == 0 && C == 0)
      return 0;
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        cin >> Grid[i][j];
      }
    }
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        if (Grid[i][j] != '.') {
          Size = 0;
          Last = Grid[i][j];
          Flood(i, j);
          Set.insert({-Size, Last});
        }
      }
    }
    cout << "Problem " << ++Case << ":" << endl;
    for (auto i : Set) {
      cout << i.second << " " << -i.first << endl;
    }
    Set.clear();
  }
}