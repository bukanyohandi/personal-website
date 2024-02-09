#include <bits/stdc++.h>
#define fs first
#define sc second
using namespace std;
int N, A, B;
long long Ans;
set<pair<int, int>> Paths;
vector<int> Edges[300003], Consider[300003];
bool Tag[300003];
// map<int,bool> Tag;
int main() {
  cin >> N;
  vector<pair<int, int>> Pathss;
  for (int i = 1; i <= N - 1; ++i) {
    cin >> A >> B;
    if (A > B)
      swap(A, B);
    Pathss.push_back(make_pair(A, B));
    Paths.insert({min(A, B), max(A, B)});
  }
  for (auto i : Paths) {
    Edges[i.fs].push_back(i.sc);
    Edges[i.sc].push_back(i.fs);
  }
  for (auto i : Paths) {
    int U = i.fs;
    int V = i.sc;
    if (Edges[U].size() < Edges[V].size())
      swap(U, V);
    else if (Edges[U].size() == Edges[V].size() && U < V)
      swap(U, V);
    Consider[U].push_back(V);
  }
  for (int i = 1; i <= N; ++i) {
    if (Edges[i].size() > 0)
      Ans += (long long)Edges[i].size() * (Edges[i].size() - 1);
    if (!Consider[i].empty()) {
      // cout<<i<<endl;
      for (auto j : Edges[i])
        Tag[j] = 1;
      // Tag[i]=0;
      // cout<<
      // for(auto j:Tag) cout<<j.fs<<endl;
      for (auto j : Consider[i]) {
        for (auto k : Edges[j]) {
          // cout<<j<<" : "<<k<<" = "<<Tag[k]<<endl;
          // if(Tag[j]) Ans--;
          Ans -= 2 * Tag[k];
        }
      }
    }
    for (auto j : Edges[i])
      Tag[j] = 0;
    // Tag.clear();
  }
  cout << Ans << endl;
}
