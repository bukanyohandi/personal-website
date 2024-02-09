// https://yohandi.me/blog/li-chao-tree/

#include <bits/stdc++.h>
using namespace std;

struct Line {
  long long m, c;
  Line(long long m, long long c) : m(m), c(c) {}
  long long y(long long x) { return m * x + c; }
};

struct Node {
  Line line;
  Node *left = nullptr;
  Node *right = nullptr;
  Node(Line l = {0, 0}) : line(l) {}
};

Node *root;
const int L = 1;
const int R = 1e9;

void addLine(Line new_line, Node *node, int l, int r) {
  if (!node)
    return;

  int m = (l + r) >> 1;
  bool left = new_line.y(l) > node->line.y(l);
  bool mid = new_line.y(m) > node->line.y(m);
  if (mid)
    swap(new_line, node->line);
  if (l == r - 1)
    return;
  if (left != mid) {
    if (!node->left)
      node->left = new Node();
    addLine(new_line, node->left, l, m);
  } else {
    if (!node->right)
      node->right = new Node();
    addLine(new_line, node->right, m, r);
  }
}
void addLine(Line new_line) { return addLine(new_line, root, L, R); }

long long query(int x, Node *node, int l, int r) {
  if (!node || l > x || r <= x)
    return 0;
  int m = (l + r) >> 1;
  if (x < m)
    return max(node->line.y(x), query(x, node->left, l, m));
  else
    return max(node->line.y(x), query(x, node->right, m, r));
}
long long query(int x) { return query(x, root, L, R); }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  struct InputFormat {
    long long x, y, A;
    bool operator<(const InputFormat &other) const {
      return tie(x, y, A) < tie(other.x, other.y, other.A);
    }
  };

  long long N, ans = 0;
  cin >> N;

  vector<InputFormat> arr(N);
  vector<long long> x(N), y(N), A(N), dp(N);

  for (auto &a : arr)
    cin >> a.x >> a.y >> a.A;
  sort(arr.begin(), arr.end());

  for (int i = 0; i < N; ++i) {
    tie(x[i], y[i], A[i]) = make_tuple(arr[i].x, arr[i].y, arr[i].A);
  }

  root = new Node();

  addLine(Line(0, 0));
  for (int i = 0; i < N; ++i) {
    dp[i] = query(y[i]) + (x[i] * y[i] - A[i]);

    addLine(Line(-x[i], dp[i]));
    ans = max(ans, dp[i]);
  }

  cout << ans << "\n";
  return 0;
}
