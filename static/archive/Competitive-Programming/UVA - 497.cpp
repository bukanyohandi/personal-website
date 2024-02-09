#include <bits/stdc++.h>
#define fs first
#define sc second
#define ll long long
using namespace std;
ll idx, tc, curlen, T[100005];
string tmp;
vector<pair<ll, ll>> vec;
vector<ll> ans;
bool first = true;
ll binser(ll ri, ll piv) {
  ll le = 0, mid, ln = ri;
  while (le <= ri) {
    mid = (le + ri) / 2;
    if (le < ln && vec[T[mid]].fs < piv && piv <= vec[T[mid + 1]].fs)
      return mid + 1;
    else if (vec[T[mid]].fs < piv)
      le = mid + 1;
    else
      ri = mid - 1;
  }
  return -1;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> tc;
  cin.ignore();
  getline(cin, tmp);
  while (tc--) {
    if (first)
      first = false;
    else
      cout << endl;
    vec.clear();
    ans.clear();
    while (getline(cin, tmp) && tmp != "")
      vec.push_back({stoll(tmp), -1});
    T[0] = curlen = 0;
    for (int i = 1; i < vec.size(); ++i) {
      if (vec[T[0]].fs > vec[i].fs)
        T[0] = i;
      else if (vec[T[curlen]].fs < vec[i].fs)
        curlen++, T[curlen] = i, vec[T[curlen]].sc = T[curlen - 1];
      else {
        idx = binser(curlen, vec[i].fs);
        T[idx] = i;
        vec[T[idx]].sc = T[idx - 1];
      }
    }
    cout << "Max hits: " << curlen + 1 << endl;
    idx = T[curlen];
    while (idx != -1)
      ans.push_back(vec[idx].fs), idx = vec[idx].sc;
    for (int i = ans.size() - 1; i >= 0; --i)
      cout << ans[i] << endl;
  }
}