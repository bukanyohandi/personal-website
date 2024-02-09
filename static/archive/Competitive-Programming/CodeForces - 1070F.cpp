#include <bits/stdc++.h>
#define pb push_back
#define pob pop_back
using namespace std;
int i, N, X, Ans, Size, Piv;
string S;
map<string, vector<int>> Arr;
priority_queue<int> pq;
int main() {
  cin >> N;
  for (i = 1; i <= N; ++i) {
    cin >> S >> X;
    if (S == "11") {
      Ans += X;
      Size++;
    } else
      Arr[S].pb(X);
  }
  //	cerr<<Ans<<endl;
  sort(Arr["01"].begin(), Arr["01"].end());
  sort(Arr["10"].begin(), Arr["10"].end());
  Piv = min(Arr["01"].size(), Arr["10"].size());
  for (int i = 0; i < Piv; ++i) {
    Ans += Arr["01"][Arr["01"].size() - 1];
    Ans += Arr["10"][Arr["10"].size() - 1];
    //		cerr<<i+1<<" "<<Ans<<endl;
    Arr["01"].pob();
    Arr["10"].pob();
  }
  while (!Arr["00"].empty()) {
    pq.push(Arr["00"][Arr["00"].size() - 1]);
    Arr["00"].pob();
  }
  while (!Arr["01"].empty()) {
    pq.push(Arr["01"][Arr["01"].size() - 1]);
    Arr["01"].pob();
  }
  while (!Arr["10"].empty()) {
    pq.push(Arr["10"][Arr["10"].size() - 1]);
    Arr["10"].pob();
  }
  //	cerr<<Ans<<endl;
  while (!pq.empty() && Size) {
    Ans += pq.top();
    pq.pop();
    Size--;
  }
  cout << Ans << endl;
}