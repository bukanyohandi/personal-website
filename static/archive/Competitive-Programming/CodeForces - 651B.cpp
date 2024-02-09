#include <bits/stdc++.h>
using namespace std;
int data[1005];
int main() {
  int x, n, modus = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x;
    data[x]++;
    modus = max(modus, data[x]);
  }
  cout << n - modus << endl;
}