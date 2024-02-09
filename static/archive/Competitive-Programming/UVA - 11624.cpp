/*
** The holy #include <bits/stdc++.h>
*/
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>

#define endl '\n'
const double PI = 3.14159265358979323846;
using namespace std;
inline void boost() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}
inline void timenull() { srand(time(NULL)); }
queue<pair<int, int>> fire, joe;
int r, c, tc;
char data[1005][1005];
void solve() {
  int piv, tmpx, tmpy, time = 1;
  while (!joe.empty()) {
    piv = fire.size();
    for (int i = 0; i < piv; ++i) {
      tmpx = fire.front().first;
      tmpy = fire.front().second;
      fire.pop();
      for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
          if (abs(x) + abs(y) == 1) {
            if (data[tmpx + x][tmpy + y] == '.' ||
                data[tmpx + x][tmpy + y] == 'J') {
              fire.push(make_pair(tmpx + x, tmpy + y));
              data[tmpx + x][tmpy + y] = 'F';
            }
          }
        }
      }
    }
    piv = joe.size();
    for (int i = 0; i < piv; ++i) {
      tmpx = joe.front().first;
      tmpy = joe.front().second;
      joe.pop();
      if (tmpx == 1 || tmpx == r || tmpy == 1 || tmpy == c) {
        cout << time << endl;
        return;
      }
      for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
          if (abs(x) + abs(y) == 1) {
            if (data[tmpx + x][tmpy + y] == '.') {
              data[tmpx + x][tmpy + y] = 'J';
              joe.push(make_pair(tmpx + x, tmpy + y));
            }
          }
        }
      }
    }
    time++;
  }
  cout << "IMPOSSIBLE" << endl;
  return;
}
int main() {
  //	boost();
  //	timenull();
  cin >> tc;
  while (tc--) {
    cin >> r >> c;
    for (int i = 0; i <= 1001; ++i) {
      for (int j = 0; j <= 1001; ++j) {
        data[i][j] = '#';
      }
    }
    for (int i = 1; i <= r; ++i) {
      for (int j = 1; j <= c; ++j) {
        cin >> data[i][j];
        if (data[i][j] == 'F') {
          fire.push(make_pair(i, j));
        } else if (data[i][j] == 'J') {
          joe.push(make_pair(i, j));
        }
      }
    }
    solve();
    //		for(int i=1;i<=r;++i){
    //			for(int j=1;j<=c;++j){
    //				cout<<data[i][j];
    //			}
    //			cout<<endl;
    //		}
    while (!joe.empty())
      joe.pop();
    while (!fire.empty())
      fire.pop();
  }
}