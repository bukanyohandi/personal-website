#include <bits/stdc++.h>
using namespace std;
pair<string, int> per[100005];
int n, piv = 1, th;
int binser(string s) {
  int le = 0, ri = n - 1, save;
  while (le <= ri) {
    int mid = (le + ri) / 2;
    if (per[mid].first == s) {
      save = mid;
    }
    if (per[mid].first < s) {
      le = mid + 1;
    } else {
      ri = mid - 1;
    }
  }
  return save;
}
int main() {
  string s;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> s >> th;
    per[i].first = s;
    per[i].second = th;
  }
  sort(per, per + n);
  int k, save;
  cin >> k;
  for (int i = 0; i < k; ++i) {
    cin >> s >> th;
    cout << per[binser(s) + th - 1].second << endl;
  }
}