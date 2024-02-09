#include <bits/stdc++.h>
using namespace std;
int mid, le = 1, ri = 1000000;
string res;
int main() {
  while (le + 1 <= ri) {
    mid = (le + ri + 1) / 2;
    cout << mid << endl;
    cin >> res;
    if (res == ">=") {
      le = mid;
    } else {
      ri = mid - 1;
    }
  }
  cout << "! " << le << endl;
}