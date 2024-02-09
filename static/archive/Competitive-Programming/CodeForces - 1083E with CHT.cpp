// https://yohandi.me/blog/convex-hull-trick/

#include <bits/stdc++.h>
using namespace std;

struct Line {
  long long m, c;
  Line(long long m, long long c) : m(m), c(c) {}

  long long y(long long x) { return m * x + c; }
  double intersect(Line other) const {
    return (double)(c - other.c) / (double)(other.m - m);
  }
};

vector<Line> ch;

void addLine(Line line) {
  auto comp = [&](const Line &a, const Line &b, const Line &c) -> bool {
    return a.intersect(b) > b.intersect(c); // p_0 > p_1 > ... > p_{n - 2}
  };

  while (ch.size() >= 2 && !comp(ch[ch.size() - 2], ch.back(), line)) {
    ch.pop_back();
  }

  ch.push_back(line);
}

int optimalLine(long long x) {
  auto p = [&](const int i) -> double { return ch[i].intersect(ch[i + 1]); };

  return lower_bound(ch.begin(), ch.end() - 1, x,
                     [&](const Line &line, long long val) {
                       int idx = &line - &ch[0];
                       return p(idx) > val;
                     }) -
         ch.begin();
}

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

  addLine(Line(0, 0));
  for (int i = 0; i < N; ++i) {
    dp[i] = ch[optimalLine(y[i])].y(y[i]) + (x[i] * y[i] - A[i]);
    addLine(Line(-x[i], dp[i]));
    ans = max(ans, dp[i]);
  }

  cout << ans << endl;
  return 0;
}