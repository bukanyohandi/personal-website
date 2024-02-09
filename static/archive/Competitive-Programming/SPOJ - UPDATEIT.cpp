#include <bits/stdc++.h>
#define fs first
#define sc second
using namespace std;
int T, N, P, Q, L, R, Val, Arr[10005], Arr2[10005];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> N >> P;
    memset(Arr2, 0, sizeof(Arr2));
    memset(Arr, 0, sizeof(Arr));
    for (int i = 1; i <= P; ++i) {
      cin >> L >> R >> Val;
      Arr[L] += Val;
      Arr[R + 1] -= Val;
    }
    Arr2[0] = Arr[0];
    for (int i = 1; i < N; ++i)
      Arr2[i] = Arr[i] + Arr2[i - 1];
    cin >> Q;
    for (int i = 1; i <= Q; ++i) {
      cin >> Val;
      cout << Arr2[Val] << '\n';
    }
  }
}