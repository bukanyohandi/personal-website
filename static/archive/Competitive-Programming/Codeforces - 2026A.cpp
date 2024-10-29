#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int x, y, k;
    cin >> x >> y >> k;
    int tmp = min(x, y);
    cout << "0 0 " << tmp << " " << tmp << endl;
    cout << "0 " << tmp << " " << tmp << " 0" << endl;
  }
}