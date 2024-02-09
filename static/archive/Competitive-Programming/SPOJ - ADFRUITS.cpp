#include <bits/stdc++.h>
using namespace std;
int DP[101][101], Piv;
string S, T, Ans;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  while (cin >> S >> T) {
    memset(DP, 0, sizeof(DP));
    Ans.clear();
    for (int i = 0; i <= S.length(); ++i) {
      for (int j = 0; j <= T.length(); ++j) {
        if (i == 0)
          DP[i][j] = j;
        else if (j == 0)
          DP[i][j] = i;
        else if (S[i - 1] == T[j - 1])
          DP[i][j] = 1 + DP[i - 1][j - 1];
        else
          DP[i][j] = 1 + min(DP[i - 1][j], DP[i][j - 1]);
      }
    }
    Piv = DP[S.length()][T.length()];
    int i = S.length(), j = T.length();
    for (; i && j;) {
      if (S[i - 1] == T[j - 1]) {
        Ans += S[i - 1];
        i--;
        j--;
        Piv--;
      } else if (DP[i - 1][j] > DP[i][j - 1]) {
        Ans += T[j - 1];
        j--;
        Piv--;
      } else {
        Ans += S[i - 1];
        i--;
        Piv--;
      }
    }
    while (i) {
      Ans += S[i - 1];
      i--;
    }
    while (j) {
      Ans += T[j - 1];
      j--;
    }
    reverse(Ans.begin(), Ans.end());
    cout << Ans << '\n';
  }
}