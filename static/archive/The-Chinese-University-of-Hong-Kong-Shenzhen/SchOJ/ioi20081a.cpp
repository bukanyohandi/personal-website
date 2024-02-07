#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  struct node {
    int val = 0;
    node *index[26];
  };

  node *root = new node();

  function<void(string)> fill = [&](string word) {
    node *cur = root;
    for (char c : word) {
      if (cur->index[c - 'a'] == NULL)
        cur->index[c - 'a'] = new node();
      cur = cur->index[c - 'a'];
    }
    cur->val = 1;
    return;
  };

  int n;
  cin >> n;

  int m = 0;
  string longest_word;
  vector<string> words(n);
  for (int i = 0; i < n; ++i) {
    cin >> words[i];
    fill(words[i]);

    if (m < (int)words[i].length()) {
      m = (int)words[i].length();
      longest_word = words[i];
    }
  }

  int printed = 0;
  vector<char> operations;
  function<void(node *, int)> dfs = [&](node *cur, int depth) {
    if (cur->val == 1) {
      operations.push_back('P');
      printed++;
    }

    if (depth == m)
      return;

    function<void(int, int)> relax = [&](int le, int ri) {
      for (int i = le; i < ri; ++i) {
        if (cur->index[i] == NULL)
          continue;
        operations.push_back((char)('a' + i));
        dfs(cur->index[i], depth + 1);
        if (printed == n) {
          return;
        }
        operations.push_back('-');
      }
    };

    int divider = (int)(longest_word[depth] - 'a');
    relax(0, divider);
    relax(divider + 1, 26);
    relax(divider, divider + 1);

    return;
  };

  dfs(root, 0);

  cout << (int)operations.size() << "\n";
  for (auto operation : operations) {
    cout << operation << "\n";
  }

  return 0;
}
