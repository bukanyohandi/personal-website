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

int N, A, B, Piv, Ans, Time, tmp, Case;
set<int> Nodes;
unordered_map<int, vector<int>> Edg;
unordered_map<int, bool> Vis;
queue<int> Bfs;

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  while (cin >> N) {
    if (N == 0)
      return 0;
    for (int i = 1; i <= N; ++i) {
      cin >> A >> B;
      Nodes.insert(A);
      Nodes.insert(B);
      Edg[A].pb(B);
      Edg[B].pb(A);
    }
    while (cin >> A >> B) {
      if (A == 0 && B == 0)
        break;
      Time = Vis[A] = 1;
      Ans = Nodes.size();
      while (!Bfs.empty())
        Bfs.pop();
      Bfs.push(A);
      while (!Bfs.empty() && Time <= B) {
        Piv = Bfs.size();
        for (int i = 0; i < Piv; ++i) {
          tmp = Bfs.front();
          Bfs.pop();
          for (auto j : Edg[tmp]) {
            if (!Vis[j]) {
              Vis[j] = 1;
              Bfs.push(j);
            }
          }
        }
        Time++;
      }
      for (auto i : Vis)
        Ans -= i.sc;
      cout << "Case " << ++Case << ": " << Ans
           << " nodes not reachable from node " << A << " with TTL = " << B
           << ".\n";
      for (auto i : Nodes)
        Vis[i] = 0;
    }
    for (auto i : Nodes)
      Edg[i].clear();
    Nodes.clear();
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
