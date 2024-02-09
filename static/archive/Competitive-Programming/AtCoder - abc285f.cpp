#include <bits/stdc++.h>
using namespace std;

int N, Q;
int freq[26];
string S;

struct node {
  int freq[26];
  char leftmost, rightmost;
  bool isSorted;
} tree[400005];

node merge(node le, node ri) {
  node ret;
  ret.leftmost = le.leftmost;
  ret.rightmost = ri.rightmost;
  ret.isSorted = le.isSorted && ri.isSorted && le.rightmost <= ri.rightmost;
  for (int i = 0; i < 26; ++i) {
    ret.freq[i] = le.freq[i] + ri.freq[i];
  }
  return ret;
}

void build(int low, int high, int pos) {
  if (low == high) {
    tree[pos].leftmost = S[low - 1];
    tree[pos].rightmost = S[low - 1];
    tree[pos].isSorted = true;
    for (int i = 0; i < 26; ++i) {
      tree[pos].freq[i] = 0;
    }
    tree[pos].freq[S[low - 1] - 'a'] = 1;
    return;
  }

  int mid = (low + high) / 2;
  build(low, mid, 2 * pos);
  build(mid + 1, high, 2 * pos + 1);

  tree[pos] = merge(tree[2 * pos], tree[2 * pos + 1]);
  return;
}

void update(int low, int high, int pos, int x) {
  if (low == high) {
    tree[pos].leftmost = S[low - 1];
    tree[pos].rightmost = S[low - 1];
    tree[pos].isSorted = true;
    for (int i = 0; i < 26; ++i) {
      tree[pos].freq[i] = 0;
    }
    tree[pos].freq[S[low - 1] - 'a'] = 1;
    return;
  }

  int mid = (low + high) / 2;
  if (x <= mid) {
    update(low, mid, 2 * pos, x);
  } else {
    update(mid + 1, high, 2 * pos + 1, x);
  }

  tree[pos] = merge(tree[2 * pos], tree[2 * pos + 1]);
  return;
}

node query(int low, int high, int pos, int ql, int qr) {
  node ret;
  ret.leftmost = '?';
  if (high < ql || low > qr) {
    return ret;
  }
  if (ql <= low && high <= qr) {
    return tree[pos];
  }

  int mid = (low + high) / 2;
  node leftchild, rightchild;
  leftchild = query(low, mid, 2 * pos, ql, qr);
  rightchild = query(mid + 1, high, 2 * pos + 1, ql, qr);

  if (leftchild.leftmost == '?' && rightchild.leftmost == '?') {

  } else if (leftchild.leftmost == '?') {
    ret = rightchild;
  } else if (rightchild.leftmost == '?') {
    ret = leftchild;
  } else {
    ret = merge(leftchild, rightchild);
  }

  return ret;
}

int main() {
  cin >> N;
  cin >> S;
  for (int i = 0; i < N; ++i) {
    freq[S[i] - 'a']++;
  }
  build(1, N, 1);

  cin >> Q;
  for (int i = 0; i < Q; ++i) {
    int op;
    cin >> op;
    if (op == 1) {
      int x;
      char c;
      cin >> x >> c;

      freq[S[x - 1] - 'a']--;
      S[x - 1] = c;
      freq[S[x - 1] - 'a']++;
      update(1, N, 1, x);
    } else {
      int l, r;
      cin >> l >> r;

      node result = query(1, N, 1, l, r);
      bool ans = result.isSorted;
      char from = result.leftmost - 'a';
      char to = result.rightmost - 'a';
      for (int i = from + 1; i <= to - 1; ++i) {
        if (result.freq[i] != freq[i]) {
          ans = false;
        }
      }

      if (ans == true) {
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    }
  }
}