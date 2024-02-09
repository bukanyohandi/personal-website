#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  string S, T;

  cin >> S;
  cin >> T;
  N = (int)S.length();
  M = (int)T.length();

  string cur = "";
  for (int i = N - M; i < N; ++i) {
    cur.push_back(S[i]);
  }

  int matches = 0;
  for (int i = 0; i < M; ++i) {
    if (cur[i] == T[i] || cur[i] == '?' || T[i] == '?') {
      matches++;
    }
  }

  if (matches == M) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }

  for (int i = 0; i < M; ++i) {
    if (cur[i] == T[i] || cur[i] == '?' || T[i] == '?') {
      matches--;
    }
    cur[i] = S[i];
    if (cur[i] == T[i] || cur[i] == '?' || T[i] == '?') {
      matches++;
    }

    if (matches == M) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}