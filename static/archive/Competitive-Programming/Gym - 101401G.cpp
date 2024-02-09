#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
long long A, Bb, N, Q, R, G, B, p[200005];
bool visited[200005];
string s;
inline long long par(long long X) {
  if (p[X] == X)
    return X;
  return p[X] = par(p[X]);
}
inline void chn(long long idx) {
  if (s[idx - 1] == 'R')
    R--, B++;
  if (s[idx - 1] == 'G')
    G--, R++;
  if (s[idx - 1] == 'B')
    B--, G++;
  return;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> Q;
  cin >> s;
  p[N + 1] = N + 1;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == 'R')
      R++;
    if (s[i] == 'G')
      G++;
    if (s[i] == 'B')
      B++;
    p[i + 1] = i + 1;
    visited[i + 1] = false;
  }
  for (int i = 0; i < Q; ++i) {
    cin >> A >> Bb;
    while (A <= Bb) {
      if (!visited[A]) {
        visited[A] = true;
        chn(A);
        p[A] = p[A + 1];
        A++;
      } else {
        A = par(A);
      }
    }
    cout << R << " " << G << " " << B << endl;
  }
}