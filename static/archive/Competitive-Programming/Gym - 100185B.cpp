#include <bits/stdc++.h>
using namespace std;
string x;
int sum, data[26];
int main() {
  cin >> x;
  for (int i = 0; i < x.length(); ++i)
    data[x[i] - 'a']++;
  for (int i = 0; i < 26; ++i)
    sum += data[i] % 2;
  cout << max(0, sum - 1) << endl;
}