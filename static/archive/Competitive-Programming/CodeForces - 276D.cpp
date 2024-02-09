// C/C++ program to get maximum xor value
// of two numbers in a range
#include <bits/stdc++.h>
using namespace std;

// method to get maximum xor value in range [L, R]
long long maxXORInRange(long long L, long long R) {
  // get xor of limits
  long long LXR = L ^ R;

  //  loop to get msb position of L^R
  long long msbPos = 0;
  while (LXR) {
    msbPos++;
    LXR >>= 1;
  }

  // construct result by adding 1,
  // msbPos times
  long long maxXOR = 0;
  long long two = 1;
  while (msbPos--) {
    maxXOR += two;
    two <<= 1;
  }

  return maxXOR;
}

//  Driver code to test above methods
int main() {
  long long L, R;
  cin >> L >> R;
  cout << maxXORInRange(L, R) << endl;
  return 0;
}