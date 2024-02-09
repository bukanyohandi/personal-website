#include <bits/stdc++.h>
using namespace std;
int N, X, Low = INT_MAX, High = -1;
unordered_map<int, int> Count;
int main() {
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> X;
    Count[X]++;
    Low = min(Low, X);
    High = max(High, X);
  }
  cout << max(0, N - (Count[High] + Count[Low])) << endl;
}