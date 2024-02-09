#include <bits/stdc++.h>
using namespace std;
stack<int> idx;
long long kiri[100005], kanan[100005], tinggi[100005];
int main() {
  int n;
  long long luas;
  while (cin >> n) {
    if (n == 0)
      return 0;
    luas = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> tinggi[i];
    }
    int i = 1;
    while (i <= n) {
      if (idx.empty() || tinggi[i] >= tinggi[idx.top()]) {
        idx.push(i);
        i++;
      } else {
        kanan[idx.top()] = i - 1;
        idx.pop();
      }
    }
    while (!idx.empty()) {
      kanan[idx.top()] = n;
      idx.pop();
    }
    i = n;
    while (i >= 1) {
      if (idx.empty() || tinggi[i] >= tinggi[idx.top()]) {
        idx.push(i);
        i--;
      } else {
        kiri[idx.top()] = i + 1;
        idx.pop();
      }
    }
    while (!idx.empty()) {
      kiri[idx.top()] = 1;
      idx.pop();
    }
    long long cur;
    for (int i = 1; i <= n; ++i) {
      cur = (kanan[i] - kiri[i] + 1) * tinggi[i];
      luas = max(luas, cur);
    }
    cout << luas << endl;
  }
}