#include <bits/stdc++.h>

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define begin_end(a) a.begin(), a.end()

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;
using lint = long long;

lint Power(lint A, lint B, lint C) {
  if (!B)
    return 1;
  lint tmp = Power(A, B >> 1, C);
  return tmp * tmp % C * (B & 1 ? A : 1) % C;
}

int L, R, C, Piv, Time, tmpx, tmpy, tmpz;
bool Vis[33][33][33];
char Grid[33][33][33];
tuple<int, int, int> S, E;
queue<tuple<int, int, int>> Bfs;

inline bool inRange(int X, int Y, int Z) {
  return X >= 1 && Y >= 1 && Z >= 1 && X <= L && Y <= R && Z <= C;
}

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  while (cin >> L >> R >> C) {
    if (L == 0 && R == 0 && C == 0)
      return 0;
    memset(Vis, 0, sizeof(Vis));
    for (int i = 1; i <= L; ++i) {
      for (int j = 1; j <= R; ++j) {
        for (int k = 1; k <= C; ++k) {
          cin >> Grid[i][j][k];
          if (Grid[i][j][k] == 'S')
            S = make_tuple(i, j, k);
          if (Grid[i][j][k] == 'E')
            E = make_tuple(i, j, k);
          if (Grid[i][j][k] == '#')
            Vis[i][j][k] = 1;
        }
      }
    }
    Time = 0;
    while (!Bfs.empty())
      Bfs.pop();
    Vis[get<0>(S)][get<1>(S)][get<2>(S)] = 1;
    Bfs.push(S);
    while (!Bfs.empty()) {
      Piv = Bfs.size();
      for (int i = 0; i < Piv; ++i) {
        tmpx = get<0>(Bfs.front());
        tmpy = get<1>(Bfs.front());
        tmpz = get<2>(Bfs.front());
        Bfs.pop();
        if (tmpx == get<0>(E) && tmpy == get<1>(E) && tmpz == get<2>(E))
          break;
        for (int dx = -1; dx <= 1; ++dx) {
          for (int dy = -1; dy <= 1; ++dy) {
            for (int dz = -1; dz <= 1; ++dz) {
              if (abs(dx) + abs(dy) + abs(dz) != 1)
                continue;
              if (!inRange(tmpx + dx, tmpy + dy, tmpz + dz))
                continue;
              if (!Vis[tmpx + dx][tmpy + dy][tmpz + dz]) {
                Vis[tmpx + dx][tmpy + dy][tmpz + dz] = 1;
                Bfs.push(make_tuple(tmpx + dx, tmpy + dy, tmpz + dz));
              }
            }
          }
        }
      }
      if (tmpx == get<0>(E) && tmpy == get<1>(E) && tmpz == get<2>(E))
        break;
      Time++;
    }
    if (tmpx == get<0>(E) && tmpy == get<1>(E) && tmpz == get<2>(E))
      cout << "Escaped in " << Time << " minute(s).\n";
    else
      cout << "Trapped!\n";
  }
  return 0;
}

/*
                              ,,aaaaa,,
                           ,dP"''    `""""Ya,
                       ,aP"'                `"Yb,
                     ,8"'                       `"8a,
                   ,8"                             `"8,
                 ,8"                                  "Yb,
               ,8"                                      `8,
              dP'                                        8I
            ,8"                           bg,           ,P'
           ,8'                              "Y8"Ya,,,,ad"
          ,d"                            a,  I8   `"""'
         ,8'                              ""888
         dP                                  `Yb,
        dP'   ,d8P::::Y8b,                     `Ya
   ,adba8',d88P::;;::;;;:"b:::Ya,                Ya
  dP":::"Y88P:;P"""YP"""Yb;::::::"Ya,             "Y,
  8:::::::Yb;d" _  "_    dI:::::::::"Yb,  ,,gd88ba,db
  Yb:::::::"8(,8P _d8   d8:::::::::::::Y88P"::::::Y8I
  `Yb;:::::::""::"":b,,dP::::::::::::::::::;aaa;:::8(
    `Y8a;:::::::::::::::::::::;;::::::::::8P""Y8)::8I
      8b"ba::::::::::::::::;adP:::::::::::":::dP::;8'
      `8b;::::::::::::;aad888P::::::::::::::;dP::;8'
       `8b;::::::::""""88"  d::::::::::b;:::::;;dP'
         "Yb;::::::::::Y8bad::::::::::;"8Paaa""'
           `"Y8a;;;:::::::::::::;;aadP""
               ``""Y88bbbdddd88P""8b,
                        _,d8"::::::"8b,
                      ,dP8"::::::;;:::"b,
                    ,dP"8:::::::Yb;::::"b,
                  ,8P:dP:::::::::Yb;::::"b,
               _,dP:;8":::::::::::Yb;::::"b
     ,aaaaaa,,d8P:::8":::::::::::;dP:::::;8
  ,ad":;;:::::"::::8"::::::::::;dP::::::;dI
 dP";adP":::::;:;dP;::::aaaad88"::::::adP:8b,
d8:::8;;;aadP"::8'Y8:d8P"::::::::::;dP";d"'`Yb:"b
8I:::;""":::::;dP I8P"::::::::::;a8"a8P"     "b:P
Yb::::"8baa8"""'  8;:;d"::::::::d8P"'         8"
 "YbaaP::8;P      `8;d::;a::;;;;dP           ,8
    `"Y8P"'         Yb;;d::;aadP"           ,d'
                     "YP:::"P'             ,d'
                       "8bdP'    _        ,8'
                      ,8"`""Yba,d"      ,d"
                     ,P'     d"8'     ,d"
                    ,8'     d'8'     ,P'
                    (b      8 I      8,
                     Y,     Y,Y,     `b,
               ____   "8,__ `Y,Y,     `Y""b,
           ,adP""""b8P""""""""Ybdb,        Y,
         ,dP"    ,dP'            `""       `8
        ,8"     ,P'                        ,P
        8'      8)                        ,8'
        8,      Yb                      ,aP'
        `Ya      Yb                  ,ad"'
          "Ya,___ "Ya             ,ad"'
            ``""""""`Yba,,,,,,,adP"'
                       `"""""""'
*/
