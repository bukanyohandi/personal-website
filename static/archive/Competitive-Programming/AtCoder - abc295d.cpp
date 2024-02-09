#include <bits/stdc++.h>
using namespace std;

int main() {
  string input;
  cin >> input;

  vector<long long> freq(1024, 0);
  freq[0] = 1;

  int bitmask = 0;
  long long substr_count = 0;

  for (char c : input) {
    bitmask ^= (1 << (c - '0'));
    substr_count += freq[bitmask];
    freq[bitmask]++;
  }

  cout << substr_count << "\n";
  return 0;
}
