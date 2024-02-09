#include <bits/stdc++.h>
using namespace std;
int n, r, c, data[1005][1005], visited[1005][1005];
void solve() {
  int tmpx, tmpy, piv, cur;
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                 greater<pair<int, pair<int, int>>>>
      bfs;
  bfs.push(make_pair(0, make_pair(1, 1)));
  visited[1][1] = 0;
  while (!bfs.empty()) {
    piv = bfs.size();
    for (int i = 0; i < piv; ++i) {
      tmpx = bfs.top().second.first;
      tmpy = bfs.top().second.second;
      bfs.pop();
      if (tmpx > 1 && visited[tmpx - 1][tmpy] >
                          visited[tmpx][tmpy] + data[tmpx - 1][tmpy]) {
        visited[tmpx - 1][tmpy] = visited[tmpx][tmpy] + data[tmpx - 1][tmpy];
        bfs.push(make_pair(visited[tmpx - 1][tmpy], make_pair(tmpx - 1, tmpy)));
      }
      if (tmpx < r && visited[tmpx + 1][tmpy] >
                          visited[tmpx][tmpy] + data[tmpx + 1][tmpy]) {
        visited[tmpx + 1][tmpy] = visited[tmpx][tmpy] + data[tmpx + 1][tmpy];
        bfs.push(make_pair(visited[tmpx + 1][tmpy], make_pair(tmpx + 1, tmpy)));
      }
      if (tmpy > 1 && visited[tmpx][tmpy - 1] >
                          visited[tmpx][tmpy] + data[tmpx][tmpy - 1]) {
        visited[tmpx][tmpy - 1] = visited[tmpx][tmpy] + data[tmpx][tmpy - 1];
        bfs.push(make_pair(visited[tmpx][tmpy - 1], make_pair(tmpx, tmpy - 1)));
      }
      if (tmpy < c && visited[tmpx][tmpy + 1] >
                          visited[tmpx][tmpy] + data[tmpx][tmpy + 1]) {
        visited[tmpx][tmpy + 1] = visited[tmpx][tmpy] + data[tmpx][tmpy + 1];
        bfs.push(make_pair(visited[tmpx][tmpy + 1], make_pair(tmpx, tmpy + 1)));
      }
    }
  }
}
int main() {
  cin >> n;
  while (n--) {
    cin >> r >> c;
    for (int i = 1; i <= r; ++i)
      for (int j = 1; j <= c; ++j) {
        cin >> data[i][j];
        visited[i][j] = 9000009;
      }
    solve();
    cout << visited[r][c] + data[1][1] << endl;
  }
}