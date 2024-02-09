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

int Ca, Cb, N;
bool Found;
bool Vis[1111][1111];
pair<int, int> Now, Next;
pair<int, int> P[1111][1111];
queue<pair<int, int>> Bfs;
stack<int> Ans;

pair<int, int> Operation(pair<int, int> Cup, int Op) {
  if (Op == 1)
    return {Ca, Cup.sc};
  if (Op == 2)
    return {Cup.fs, Cb};
  if (Op == 3)
    return {0, Cup.sc};
  if (Op == 4)
    return {Cup.fs, 0};
  if (Op == 5)
    return {Cup.fs + Cup.sc - min(Cup.fs + Cup.sc, Cb),
            min(Cup.fs + Cup.sc, Cb)};
  if (Op == 6)
    return {min(Cup.fs + Cup.sc, Ca),
            Cup.fs + Cup.sc - min(Cup.fs + Cup.sc, Ca)};
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  while (cin >> Ca >> Cb >> N) {
    for (int i = 0; i <= Ca; ++i) {
      for (int j = 0; j <= Cb; ++j) {
        P[i][j] = {i, j};
        Vis[i][j] = 0;
      }
    }
    while (!Bfs.empty())
      Bfs.pop();
    Bfs.push({0, 0});
    Vis[0][0] = 1;
    while (true) {
      Now = Bfs.front();
      if (Now.sc == N)
        break;
      Bfs.pop();
      for (int i = 1; i <= 6; ++i) {
        Next = Operation(Now, i);
        if (!Vis[Next.fs][Next.sc]) {
          Vis[Next.fs][Next.sc] = 1;
          P[Next.fs][Next.sc] = Now;
          Bfs.push(Next);
        }
      }
    }
    while (!(Now.fs == 0 && Now.sc == 0)) {
      Next = P[Now.fs][Now.sc];
      for (int i = 1; i <= 6; ++i)
        if (Operation(Next, i) == Now)
          Ans.push(i);
      Now = Next;
    }
    while (!Ans.empty()) {
      if (Ans.top() == 1)
        puts("fill A");
      if (Ans.top() == 2)
        puts("fill B");
      if (Ans.top() == 3)
        puts("empty A");
      if (Ans.top() == 4)
        puts("empty B");
      if (Ans.top() == 5)
        puts("pour A B");
      if (Ans.top() == 6)
        puts("pour B A");
      Ans.pop();
    }
    puts("success");
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
