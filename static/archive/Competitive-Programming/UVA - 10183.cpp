#include <bits/stdc++.h>
using namespace std;
int r, c, n, x, y;
pair<pair<int, int>, int> monster[105];
char petak[205][205];
bool visited[205][205];
int jarakkuadrat(int x1, int y1, int x2, int y2) {
  return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}
void solve() {
  int piv, time = 0, tmpx, tmpy;
  bool gbatas, gbbawah, gbkiri, gbkanan;
  pair<int, int> current;
  queue<pair<int, int>> bfs;
  bfs.push(make_pair(1, 1));
  visited[1][1] = true;
  while (!bfs.empty()) {
    piv = bfs.size();
    for (int i = 0; i < piv; ++i) {
      tmpx = bfs.front().first;
      tmpy = bfs.front().second;
      bfs.pop();
      petak[tmpx][tmpy] = 'R';
      //			cout<<tmpx<<" "<<tmpy<<endl;
      if (tmpx == r && tmpy == c) {
        cout << time << endl;
        return;
      }
      gbatas = gbbawah = gbkiri = gbkanan = false;
      for (int j = 0; j < n; ++j) {
        if (tmpx >= r || (jarakkuadrat(tmpx + 1, tmpy, monster[j].first.first,
                                       monster[j].first.second) <=
                          monster[j].second * monster[j].second))
          gbatas = true;
        if (tmpx <= 1 || (jarakkuadrat(tmpx - 1, tmpy, monster[j].first.first,
                                       monster[j].first.second) <=
                          monster[j].second * monster[j].second))
          gbbawah = true;
        if (tmpy >= c || (jarakkuadrat(tmpx, tmpy + 1, monster[j].first.first,
                                       monster[j].first.second) <=
                          monster[j].second * monster[j].second))
          gbkiri = true;
        if (tmpy <= 1 || (jarakkuadrat(tmpx, tmpy - 1, monster[j].first.first,
                                       monster[j].first.second) <=
                          monster[j].second * monster[j].second))
          gbkanan = true;

        //				cout<<jarakkuadrat(tmpx+1,tmpy,monster[j].first.first,monster[j].first.second)<<"
        //"<<monster[j].second*monster[j].second<<endl;
        //				cout<<jarakkuadrat(tmpx-1,tmpy,monster[j].first.first,monster[j].first.second)<<"
        //"<<monster[j].second*monster[j].second<<endl;
        //				cout<<jarakkuadrat(tmpx,tmpy+1,monster[j].first.first,monster[j].first.second)<<"
        //"<<monster[j].second*monster[j].second<<endl;
        //				cout<<jarakkuadrat(tmpx,tmpy-1,monster[j].first.first,monster[j].first.second)<<"
        //"<<monster[j].second*monster[j].second<<endl;
      }
      if (!gbatas && !visited[tmpx + 1][tmpy] && petak[tmpx + 1][tmpy] == '.') {
        visited[tmpx + 1][tmpy] = true;
        bfs.push(make_pair(tmpx + 1, tmpy));
      }
      if (!gbbawah && !visited[tmpx - 1][tmpy] &&
          petak[tmpx - 1][tmpy] == '.') {
        visited[tmpx - 1][tmpy] = true;
        bfs.push(make_pair(tmpx - 1, tmpy));
      }
      if (!gbkiri && !visited[tmpx][tmpy + 1] && petak[tmpx][tmpy + 1] == '.') {
        visited[tmpx][tmpy + 1] = true;
        bfs.push(make_pair(tmpx, tmpy + 1));
      }
      if (!gbkanan && !visited[tmpx][tmpy - 1] &&
          petak[tmpx][tmpy - 1] == '.') {
        visited[tmpx][tmpy - 1] = true;
        bfs.push(make_pair(tmpx, tmpy - 1));
      }
    }
    time++;
  }
  cout << "Impossible." << endl;
  return;
}
int main() {
  while (cin >> r >> c) {
    if (r == 0 && c == 0)
      return 0;
    for (int i = 0; i <= r + 1; ++i) {
      for (int j = 0; j <= c + 1; ++j) {
        if (i == 0 || j == 0 || i == r + 1 || j == c + 1) {
          petak[i][j] = '#';
        } else {
          visited[i][j] = false;
          petak[i][j] = '.';
        }
      }
    }
    cin >> n;
    for (int i = 0; i < n; ++i) {
      cin >> x >> y;
      petak[x][y] = '#';
    }
    cin >> n;
    for (int i = 0; i < n; ++i) {
      cin >> monster[i].first.first >> monster[i].first.second >>
          monster[i].second;
    }
    solve();
    //		for(int i=0;i<=r+1;++i){
    //			for(int j=0;j<=c+1;++j){
    //				cout<<petak[i][j];
    //			}
    //			cout<<endl;
    //		}
  }
}