#include <bits/stdc++.h>
using namespace std;

int main() {
  int A, B;
  cin >> A >> B;
  int freq[4];
  memset(freq, 0, sizeof(freq));
  freq[A]++;
  freq[B]++;
  for (int i = 1; i <= 3; ++i) {
    if (freq[i] == 0) {
      cout << i << endl;
      return 0;
    }
  }
}