#include <iostream>
#include <vector>
#define pb push_back
using namespace std;
int tmp, i, j, N, M, piv, piv1, piv2, piv3;
string x, data[5000];
bool found;
vector<int> vec[5000][26];
inline bool available() {
  if (vec[j][piv1].size() && vec[j][piv2].size() && vec[j][piv3].size())
    return true;
  return false;
}
inline void clean() {
  piv1 = x[0] - 'A';
  piv2 = x[1] - 'A';
  piv3 = x[2] - 'A';
  found = false;
  return;
}
inline int find(int letter) {
  int left = 0, right = vec[j][letter].size() - 1, mid, save = -1;
  while (left <= right) {
    mid = (left + right) / 2;
    if (vec[j][letter][mid] > piv)
      save = mid, right = mid - 1;
    else {
      left = mid + 1;
    }
  }
  if (save == -1)
    return -1;
  return vec[j][letter][save];
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> M;
  for (i = 0; i < N; ++i) {
    cin >> data[i];
    for (j = 0; j < data[i].length(); ++j)
      vec[i][data[i][j] - 'a'].pb(j);
  }
  for (i = 0; i < M; ++i) {
    cin >> x;
    clean();
    for (j = 0; j < N && !found; ++j) {
      if (!available())
        continue;
      piv = vec[j][piv1][0];
      tmp = find(piv2);
      if (tmp == -1)
        continue;
      piv = tmp;
      tmp = find(piv3);
      if (tmp == -1)
        continue;
      cout << data[j] << '\n';
      found = true;
    }
    if (found)
      continue;
    cout << "No valid word\n";
  }
}