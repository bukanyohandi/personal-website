/*
    Author: Yohandi
    Problem Title: The Secret Key of the Ancient Ruins
    Problem Link: http://oj.cuhk.edu.cn/problem/dda6050a4q12023fall
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> LPS(string &str) {
  int n = (int)str.length();
  int len = 0;

  vector<int> lps(n);
  lps[0] = 0;

  int i = 1;
  while (i < n) {
    if (str[i] == str[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if (len != 0) {
        len = lps[len - 1];
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }

  return lps;
}

string findSecretKey(string &T) {
  int n = (int)T.length();
  vector<int> lps = LPS(T);

  vector<bool> occured(n, false);
  for (int i = 1; i < n - 1; ++i) {
    int cur = i;
    while (lps[cur] > 0) {
      if (occured[lps[cur]])
        break;
      if (lps[cur] > lps[n - 1]) {
        cur = lps[cur] - 1;

        continue;
      }
      if (i > 0 && i < n - 1)
        occured[lps[cur]] = true;

      cur = lps[cur] - 1;
    }
  }

  int i = lps[n - 1];
  while (i >= 1) {
    if (occured[i]) {
      return T.substr(0, i);
    }
    i = lps[i - 1];
  }

  return "Just a legend";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  string T;
  cin >> T;

  cout << findSecretKey(T) << endl;

  return 0;
}