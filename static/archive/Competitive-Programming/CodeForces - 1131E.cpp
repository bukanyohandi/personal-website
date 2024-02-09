#include <bits/stdc++.h>
using namespace std;
int N, Ans, Piv, Piv2;
int Pre[26], Count[26];
int DP[100001][26];
string S;
int main() {
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> S;
    memset(Count, 0, sizeof(Count));
    memset(Pre, 0, sizeof(Pre));
    Count[S[0] - 'a'] = 1;
    Pre[S[0] - 'a'] = 1;
    for (int j = 1; j < S.length(); ++j) {
      if (S[j] == S[j - 1]) {
        Count[S[j] - 'a']++;
      } else {
        Count[S[j] - 'a'] = 1;
      }
      Pre[S[j] - 'a'] = max(Pre[S[j] - 'a'], Count[S[j] - 'a']);
    }
    for (int j = 0; j < 26; ++j) {
      DP[i][j] = Pre[j];
      for (Piv = 0; Piv < S.length() && S[Piv] == (char)('a' + j); Piv++)
        ;
      for (Piv2 = S.length() - 1; Piv2 > Piv && S[Piv2] == (char)('a' + j);
           Piv2--)
        ;
      if (Piv == S.length()) {
        DP[i][j] =
            max(DP[i][j], (DP[i - 1][j] + 1) * ((int)S.length() + 1) - 1);
      } else if (DP[i - 1][j] != 0) {
        DP[i][j] = max(DP[i][j], Piv - Piv2 + (int)S.length());
      }
    }
  }
  for (int i = 0; i < 26; ++i)
    Ans = max(Ans, DP[N][i]);
  cout << Ans << endl;
}