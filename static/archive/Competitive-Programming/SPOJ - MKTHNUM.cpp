#include <bits/stdc++.h>

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define all(a) a.begin(), a.end()
#define Mid (Low + High) / 2

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

struct Node {
  int Val = 0;
  Node *Left, *Right;
} * Root[111111];

int N, Q, Le, Ri, K;
int Ord[111111];
pair<int, int> A[111111];

void Build(Node *Now, int Low, int High) {
  Now->Val = 0;
  if (Low == High)
    return;
  Now->Left = new Node();
  Now->Right = new Node();
  Build(Now->Left, Low, Mid);
  Build(Now->Right, Mid + 1, High);
  return;
}

void Update(Node *Prev, Node *Now, int Low, int High, int Pos) {
  //	cout<<"Low : "<<Low<<"\n"<<"Mid : "<<Mid<<"\n"<<"High : "<<High<<"\n";
  //	cout<<Prev->Val<<" "<<Now->Val<<"\n";
  if (Low == High) {
    Now->Val = Prev->Val + (Low == Ord[Pos]);
    return;
  }
  Now->Left = new Node();
  Now->Right = new Node();
  if (Ord[Pos] <= Mid) {
    Now->Right = Prev->Right;
    Update(Prev->Left, Now->Left, Low, Mid, Pos);
  } else {
    Now->Left = Prev->Left;
    Update(Prev->Right, Now->Right, Mid + 1, High, Pos);
  }
  Now->Val = Now->Left->Val + Now->Right->Val;
  return;
}

int Query(Node *Prev, Node *Now, int Low, int High, int Kth) {
  if (Low == High)
    return Low;
  int tmp = Now->Left->Val - Prev->Left->Val;
  if (Kth <= tmp) {
    return Query(Prev->Left, Now->Left, Low, Mid, Kth);
  } else {
    return Query(Prev->Right, Now->Right, Mid + 1, High, Kth - tmp);
  }
}

void Print(Node *Prev, Node *Now, int Low, int High) {
  if (Low == High) {
    cout << Now->Val - Prev->Val << "\n";
    return;
  }
  cout << Now->Val - Prev->Val << "\n";
  Print(Prev->Left, Now->Left, Low, Mid);
  Print(Prev->Right, Now->Right, Mid + 1, High);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> Q;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i].fs;
    A[i].sc = i;
  }
  sort(A + 1, A + N + 1);
  for (int i = 1; i <= N; ++i) {
    Ord[A[i].sc] = i;
  }
  Root[0] = new Node();
  Build(Root[0], 1, N);
  for (int i = 1; i <= N; ++i) {
    Root[i] = new Node();
    Update(Root[i - 1], Root[i], 1, N, i);
  }
  for (int i = 1; i <= Q; ++i) {
    //		cin>>Le>>Ri;
    //		Print(Root[Le-1],Root[Ri],1,N);
    cin >> Le >> Ri >> K;
    cout << A[Query(Root[Le - 1], Root[Ri], 1, N, K)].fs << "\n";
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
