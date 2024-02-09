#include <bits/stdc++.h>
using namespace std;
int sx, sy, ex, ey;
string a, b;
bool visited[10][10];
void solve() {
  int piv, time = 0, tmpx, tmpy;
  queue<pair<int, int>> bfs;
  bfs.push(make_pair(sx, sy));
  visited[sx][sy] = true;
  while (!bfs.empty()) {
    piv = bfs.size();
    for (int i = 0; i < piv; ++i) {
      tmpx = bfs.front().first;
      tmpy = bfs.front().second;
      if (tmpx < 1 || tmpx > 8 || tmpy < 1 || tmpy > 8) {
        bfs.pop();
        continue;
      } else {
        visited[tmpx][tmpy] = true;
      }
      bfs.pop();
      if (tmpx == ex && tmpy == ey) {
        cout << "To get from " << a << " to " << b << " takes " << time
             << " knight moves." << endl;
        return;
      }
      if (!visited[tmpx + 2][tmpy + 1]) {
        bfs.push(make_pair(tmpx + 2, tmpy + 1));
      }
      if (!visited[tmpx + 2][tmpy - 1]) {
        bfs.push(make_pair(tmpx + 2, tmpy - 1));
      }
      if (!visited[tmpx - 2][tmpy + 1]) {
        bfs.push(make_pair(tmpx - 2, tmpy + 1));
      }
      if (!visited[tmpx - 2][tmpy - 1]) {
        bfs.push(make_pair(tmpx - 2, tmpy - 1));
      }
      if (!visited[tmpx + 1][tmpy + 2]) {
        bfs.push(make_pair(tmpx + 1, tmpy + 2));
      }
      if (!visited[tmpx + 1][tmpy - 2]) {
        bfs.push(make_pair(tmpx + 1, tmpy - 2));
      }
      if (!visited[tmpx - 1][tmpy + 2]) {
        bfs.push(make_pair(tmpx - 1, tmpy + 2));
      }
      if (!visited[tmpx - 1][tmpy - 2]) {
        bfs.push(make_pair(tmpx - 1, tmpy - 2));
      }
    }
    time++;
  }
}
int main() {
  while (cin >> a >> b) {
    sx = a[0] - 'a' + 1;
    sy = a[1] - '0';
    ex = b[0] - 'a' + 1;
    ey = b[1] - '0';
    solve();
    for (int i = 1; i <= 8; ++i) {
      for (int j = 1; j <= 8; ++j) {
        visited[i][j] = false;
      }
    }
  }
}