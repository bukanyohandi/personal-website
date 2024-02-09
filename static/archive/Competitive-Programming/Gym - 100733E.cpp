#include <bits/stdc++.h>
using namespace std;
int data[1000005];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> data[i];
  sort(data + 1, data + 1 + n);
  cout << data[m] << endl;
}