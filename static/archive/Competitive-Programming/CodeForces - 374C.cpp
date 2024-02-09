#include <bits/stdc++.h>
using namespace std;
int rw, cw, ans = 0, memo[1005][1005];
char grid[1005][1005];
bool rusak = false;
int solve(int x, int y, int point) {
  int a = 0, b = 0, c = 0, d = 0;
  if (rusak)
    return 0;
  if (point * 4 > rw * cw) {
    rusak = true;
    return 0;
  }
  if (memo[x][y] != -1)
    return memo[x][y];
  if (grid[x][y] == 'D') {
    if (grid[x + 1][y] == 'I')
      a = solve(x + 1, y, point);
    if (grid[x - 1][y] == 'I')
      b = solve(x - 1, y, point);
    if (grid[x][y + 1] == 'I')
      c = solve(x, y + 1, point);
    if (grid[x][y - 1] == 'I')
      d = solve(x, y - 1, point);
    return memo[x][y] = max(max(a, b), max(c, d));
  }
  if (grid[x][y] == 'I') {
    if (grid[x + 1][y] == 'M')
      a = solve(x + 1, y, point);
    if (grid[x - 1][y] == 'M')
      b = solve(x - 1, y, point);
    if (grid[x][y + 1] == 'M')
      c = solve(x, y + 1, point);
    if (grid[x][y - 1] == 'M')
      d = solve(x, y - 1, point);
    return memo[x][y] = max(max(a, b), max(c, d));
  }
  if (grid[x][y] == 'M') {
    if (grid[x + 1][y] == 'A')
      a = solve(x + 1, y, point);
    if (grid[x - 1][y] == 'A')
      b = solve(x - 1, y, point);
    if (grid[x][y + 1] == 'A')
      c = solve(x, y + 1, point);
    if (grid[x][y - 1] == 'A')
      d = solve(x, y - 1, point);
    return memo[x][y] = max(max(a, b), max(c, d));
  }
  if (grid[x][y] == 'A') {
    point++;
    if (grid[x + 1][y] == 'D')
      a = solve(x + 1, y, point);
    if (grid[x - 1][y] == 'D')
      b = solve(x - 1, y, point);
    if (grid[x][y + 1] == 'D')
      c = solve(x, y + 1, point);
    if (grid[x][y - 1] == 'D')
      d = solve(x, y - 1, point);
    return memo[x][y] = 1 + max(max(a, b), max(c, d));
  }
  return 0;
}
int main() {
  cin >> rw >> cw;
  for (int i = 0; i <= rw + 1; ++i) {
    for (int j = 0; j <= cw + 1; ++j) {
      if (i == 0 || j == 0 || i == rw + 1 || j == cw + 1) {
        grid[i][j] = '#';
        continue;
      }
      cin >> grid[i][j];
      memo[i][j] = -1;
    }
  }
  for (int i = 1; i <= rw; ++i) {
    for (int j = 1; j <= cw; ++j) {
      if (grid[i][j] == 'D') {
        if (rusak)
          break;
        ans = max(ans, solve(i, j, 0));
      }
    }
    if (rusak)
      break;
  }
  if (rusak) {
    cout << "Poor Inna!" << endl;
    return 0;
  }
  if (ans == 0) {
    cout << "Poor Dima!" << endl;
    return 0;
  }
  cout << ans << endl;
  return 0;
}
/*
5 5
DIMAD
DIMAI
DIMAM
DDMAA
AAMID
*/
