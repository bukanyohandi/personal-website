#include <bits/stdc++.h>
using namespace std;

struct node {
  node *next[26];
  int val;
};

node *root;

void push(string &S) {
  node *cur = root;

  for (int i = 0; i < (int)S.length(); ++i) {
    if (cur->next[S[i] - 'a'] == NULL) {
      cur->next[S[i] - 'a'] = new node();
      cur->next[S[i] - 'a']->val = 0;
    }
    cur = cur->next[S[i] - 'a'];
    cur->val++;
  }
}

int findLongest(string &S) {
  node *cur = root;

  for (int i = 0; i < (int)S.length(); ++i) {
    if (cur->next[S[i] - 'a']->val > 1) {
      cur = cur->next[S[i] - 'a'];
    } else {
      return i;
    }
  }

  return (int)S.length();
}

int main() {
  root = new node();

  int N;
  cin >> N;

  vector<string> S;
  S.resize(N);

  for (int i = 0; i < N; ++i) {
    cin >> S[i];
    push(S[i]);
  }

  for (int i = 0; i < N; ++i) {
    cout << findLongest(S[i]) << endl;
  }
}