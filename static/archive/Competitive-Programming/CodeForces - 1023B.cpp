#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, k;
  cin >> n >> k;
  if (k <= 2)
    cout << 0 << endl;
  else
    cout << max(0LL, min((k - 1) / 2, (n * 2 - k + 1) / 2)) << endl;
}