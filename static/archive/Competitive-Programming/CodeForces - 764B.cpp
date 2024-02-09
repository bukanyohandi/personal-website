#include <bits/stdc++.h>
using namespace std;
int data[200005];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> data[i];
  }
  for (int i = 1; i <= n / 2; ++i) {
    if (i % 2 == 1) {
      swap(data[i], data[n - i + 1]);
    }
  }
  for (int i = 1; i < n; ++i) {
    cout << data[i] << " ";
  }
  cout << data[n] << endl;
}