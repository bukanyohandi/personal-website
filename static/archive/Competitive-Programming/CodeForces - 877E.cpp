#include <bits/stdc++.h>

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define all(a) a.begin(), a.end()
#define Mid (Low + High) / 2
#define LHS Low, Mid, 2 * Pos
#define RHS Mid + 1, High, 2 * Pos + 1

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;
using lint = long long;

mt19937 rng(time(NULL));

lint Power(lint A, lint B, lint C) {
  if (!B)
    return 1;
  lint tmp = Power(A, B >> 1, C);
  return tmp * tmp % C * (B & 1 ? A : 1) % C;
}

int N, V, P, Q, Size = 1;
int T[222222], Start[222222], End[222222], Tree[888888];
bool Lazy[888888];
vector<int> Order;
vector<int> Child[222222];
string Op;

void DFS(int Pos) {
  Order.pb(Pos);
  if (Start[Pos] == 0)
    Start[Pos] = Size++;
  for (auto i : Child[Pos])
    DFS(i);
  End[Pos] = Size - 1;
  return;
}

void Build(int Low, int High, int Pos) {
  if (Low == High) {
    Tree[Pos] = T[Order[Low - 1]];
    return;
  }
  Build(LHS);
  Build(RHS);
  Tree[Pos] = Tree[2 * Pos] + Tree[2 * Pos + 1];
  return;
}

void Push(int Low, int High, int Pos) {
  if (!Lazy[Pos])
    return;
  if (Low != High) {
    Lazy[2 * Pos] = !Lazy[2 * Pos];
    Lazy[2 * Pos + 1] = !Lazy[2 * Pos + 1];
  }
  Tree[Pos] = (High - Low + 1) - (Tree[Pos]);
  Lazy[Pos] = 0;
  return;
}

void Update(int Low, int High, int Pos) {
  Push(Low, High, Pos);
  if (Start[V] <= Low && High <= End[V]) {
    Lazy[Pos] = 1;
    Push(Low, High, Pos);
    return;
  }
  if (Low > End[V] || High < Start[V])
    return;
  Update(LHS);
  Update(RHS);
  Tree[Pos] = Tree[2 * Pos] + Tree[2 * Pos + 1];
  return;
}

int Query(int Low, int High, int Pos) {
  Push(Low, High, Pos);
  if (Start[V] <= Low && High <= End[V])
    return Tree[Pos];
  if (Low > End[V] || High < Start[V])
    return 0;
  return Query(LHS) + Query(RHS);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  for (int i = 2; i <= N; ++i) {
    cin >> P;
    Child[P].pb(i);
  }
  DFS(1);
  for (int i = 1; i <= N; ++i)
    cin >> T[i];
  Build(1, N, 1);
  cin >> Q;
  for (int i = 1; i <= Q; ++i) {
    cin >> Op >> V;
    if (Op == "pow")
      Update(1, N, 1);
    if (Op == "get")
      cout << Query(1, N, 1) << '\n';
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
