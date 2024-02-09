#include <bits/stdc++.h>
using namespace std;
int data[100005], data2[100005];
int main() {
  int n, g = 0, tmp;
  cin >> n;
  tmp = 1;
  for (int i = 0; i < n; ++i) {
    cin >> data[i];
    if (data[i] == tmp) {
      data2[g]++;
    } else {
      tmp = data[i];
      g++;
      data2[g]++;
    }
  }
  int a, best = 0;
  if (data[0] == 2) {
    a = 1;
  } else {
    a = 0;
  }
  for (int i = a; i < g; ++i) {
    best = max(best, min(data2[i + 1], data2[i]));
  }
  cout << best + best << endl;
  return 0;
}