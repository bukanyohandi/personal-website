#include <bits/stdc++.h>
using namespace std;
int t, n, k, a, b;
int arr[1000], p[1000], cnt[1000];
bool vis[1000];
vector<int> v[1000];
int find(int x) {
  if (p[x] == x)
    return x;
  return p[x] = find(p[x]);
}
int main() {
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
      p[i] = i, vis[i] = false, cnt[i] = 0, v[i].clear();
    for (int i = 0; i < n; ++i)
      cin >> arr[i];
    for (int i = 0; i < k; ++i) {
      cin >> a >> b;
      a--;
      b--;
      if (find(a) != find(b)) {
        p[find(a)] = find(b);
      }
    }
    for (int i = 0; i < n; ++i) {
      v[find(i)].push_back(arr[i]);
    }
    for (int i = 0; i < n; ++i) {
      sort(v[i].begin(), v[i].end());
    }
    for (int i = 0; i < n; ++i) {
      if (i != 0)
        cout << " ";
      int x = find(i);
      cout << v[x][cnt[x]++];
    }
    cout << endl;
  }
}