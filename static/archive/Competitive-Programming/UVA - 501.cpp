#include <bits/stdc++.h>
using namespace std;
int piv, piv2, tc, n, m, data[30005], moves[30005];
bool isfirst = true;
int main() {
  priority_queue<int> bawah, atas;
  cin >> tc;
  while (tc--) {
    if (isfirst)
      isfirst = false;
    else
      cout << endl;
    while (!bawah.empty())
      bawah.pop();
    while (!atas.empty())
      atas.pop();
    piv = piv2 = 1;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
      cin >> data[i];
    for (int i = 1; i <= m; ++i)
      cin >> moves[i];
    for (int i = 1; i <= m; ++i) {
      while (bawah.size() != moves[piv]) {
        bawah.push(data[piv2]);
        piv2++;
      }
      piv++;
      while (bawah.size() > i) {
        atas.push(bawah.top());
        bawah.pop();
      }
      cout << bawah.top() << endl;
      while (atas.size() > 0) {
        bawah.push(atas.top());
        atas.pop();
      }
    }
  }
}