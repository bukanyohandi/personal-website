#include <bits/stdc++.h>
using namespace std;

struct Node {
  int Val;
  Node *Prev;
  Node *Next;
};

int N, Op, X;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  // T=1;
  //	cin>>T;
  // rep(t,1,T){
  cin >> N;
  Node *Root = new Node();
  Node *Now = Root;
  for (int i = 1; i <= N; ++i) {
    cin >> Op;
    if (Op == 1) {
      Now->Next = new Node();
      Now->Next->Prev = Now;
      Now = Now->Next;
      cin >> X;
      Now->Val = X;
    }
    if (Op == 2) {
      if (Now != Root)
        Now = Now->Prev;
    }
    if (Op == 3) {
      if (Now != Root)
        cout << Now->Val << "\n";
      else
        cout << "Empty!\n";
    }
  }
  // }
  return 0;
}
