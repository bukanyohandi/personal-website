#include <iostream>
using namespace std;

int T, N;
int B[16384];

bool solve() {
  for (int i = 0; i < N; ++i) {
    if ((i + 1) % B[i] != 0) {
      return false;
    }
  }

  return true;
}

int main() {
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> N;
    for (int i = 0; i < N; ++i) {
      cin >> B[i];
    }
    cout << (solve() ? "YES" : "NO") << endl;
  }
}