#include <iostream>
#include <numeric>
#include <string.h>
using namespace std;

int T, N;
int A[131072], arr[131072];

int solve() {
  memset(arr, 0, sizeof(arr));

  for (int i = 1; i < N; ++i) {
    if (A[i] != A[i - 1]) {
      arr[i] = 1;
      arr[i - 1] = 1;
    }
  }

  return accumulate(arr, arr + N, 0);
}

int main() {
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> N;
    for (int i = 0; i < N; ++i) {
      cin >> A[i];
    }
    cout << solve() << endl;
  }
}