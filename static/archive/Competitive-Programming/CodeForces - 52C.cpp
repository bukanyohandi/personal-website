#include <bits/stdc++.h>

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define begin_end(a) a.begin(), a.end()
#define Mid (Low + High) / 2
#define LS Low, Mid, 2 * Pos
#define LS2 Low, Mid, Left, Right, 2 * Pos
#define RS Mid + 1, High, 2 * Pos + 1
#define RS2 Mid + 1, High, Left, Right, 2 * Pos + 1

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

lint N, Q, A[222222], Tree[888888], Lazy[888888], O[3], Piv;
string S;

inline void Push(int Low, int High, int Pos) {
  if (!Lazy[Pos])
    return;
  Tree[Pos] += Lazy[Pos];
  if (Low != High) {
    Lazy[2 * Pos] += Lazy[Pos];
    Lazy[2 * Pos + 1] += Lazy[Pos];
  }
  Lazy[Pos] = 0;
  return;
}

lint Build(int Low, int High, int Pos) {
  return Tree[Pos] = High - Low ? min(Build(LS), Build(RS)) : A[Low];
}

lint Query(int Low, int High, int Left, int Right, int Pos) {
  Push(Low, High, Pos);
  if (High < Left || Right < Low)
    return 4e18;
  if (Left <= Low && High <= Right)
    return Tree[Pos];
  return min(Query(LS2), Query(RS2));
}

lint Update(int Low, int High, int Left, int Right, int Pos) {
  Push(Low, High, Pos);
  if (High < Left || Right < Low)
    return 4e18;
  if (Left <= Low && High <= Right) {
    Tree[Pos] += O[2];
    if (Low != High) {
      Lazy[2 * Pos] += O[2];
      Lazy[2 * Pos + 1] += O[2];
    }
    return Tree[Pos];
  }
  Update(LS2);
  Update(RS2);
  Tree[Pos] = min(Tree[2 * Pos], Tree[2 * Pos + 1]);
  //	return Tree[Pos]=min(Update(LS2),Update(RS2));
}

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  cin >> N;
  for (int i = 0; i < N; ++i)
    cin >> A[i];
  Build(0, N - 1, 1);
  cin >> Q;
  getchar();
  for (int i = 0; i < Q; ++i, Piv = 0) {
    getline(cin, S);
    stringstream Read(S);
    while (Read >> O[Piv++])
      ;
    if (Piv % 2) {
      if (O[0] <= O[1])
        cout << Query(0, N - 1, O[0], O[1], 1) << '\n';
      else
        cout << min(Query(0, N - 1, 0, O[1], 1),
                    Query(0, N - 1, O[0], N - 1, 1))
             << '\n';
    } else {
      if (O[0] <= O[1])
        Update(0, N - 1, O[0], O[1], 1);
      else {
        Update(0, N - 1, 0, O[1], 1);
        Update(0, N - 1, O[0], N - 1, 1);
      }
    }
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
