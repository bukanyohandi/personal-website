#include <bits/stdc++.h>
#define oo 381654729
using namespace std;
int N;
long long K;
int A[222222], Tag[222222];

int main() {
  // cout<<727202214173249351%3<<endl;
  cin >> N >> K;
  for (int i = 1; i <= N; ++i)
    cin >> A[i];
  set<int> Set;
  Set.insert(1);
  int idx = 1;
  int skrg = 1;
  int itung = 0;
  int ukur = 1;
  bool ok = 0;
  vector<int> putar;
  while (idx <= N) {
    if (idx <= K || idx >= K + 2) {
      if (Set.count(A[skrg])) {
        ukur = Set.size();
        break;
      }
    } else {
      cout << skrg << endl;
      return 0;
    }
    skrg = A[skrg];
    itung++;
    Set.insert(skrg);
    ++idx;
  }
  idx = 1;
  itung++;
  K -= itung;
  int tmp = A[skrg];
  skrg = 1;
  while (idx <= N) {
    if (skrg == tmp && !ok)
      ok = 1;
    else if (skrg == tmp && ok)
      break;
    if (ok) {
      putar.push_back(skrg);
    }
    skrg = A[skrg];
    ++idx;
  }
  // while()
  // while(true){
  // 	if(Tag[Now]) break;
  // 	Tag[Now]=Piv;
  // 	Now=A[Now];
  // 	Piv++;
  // }
  // Piv-=Tag[Now];
  // K%=Piv;
  // while(K<=N) K+=Piv;
  // Now=1;
  // while(K--){
  // 	Now=A[Now];
  // }
  cout << putar[K % putar.size()] << endl;
}