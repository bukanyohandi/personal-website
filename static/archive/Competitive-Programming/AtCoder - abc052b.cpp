#include <iostream>
using namespace std;
int main() {
  int N, best = 0, cur = 0;
  string X;
  cin >> N;
  cin >> X;
  for (int i = 0; i < N; ++i) {
    if (X[i] == 'I')
      cur++;
    else
      cur--;
    best = max(best, cur);
  }
  cout << best << endl;
}