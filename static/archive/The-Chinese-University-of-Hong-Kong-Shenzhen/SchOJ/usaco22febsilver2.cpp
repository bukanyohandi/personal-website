#include <bits/stdc++.h>
using namespace std;

#define int long long

const double PI = acos(-1);

void fft(vector<complex<double>> &a, bool invert) {
  int n = a.size();
  if (n == 1)
    return;

  vector<complex<double>> a0(n / 2), a1(n / 2);
  for (int i = 0; 2 * i < n; i++) {
    a0[i] = a[2 * i];
    a1[i] = a[2 * i + 1];
  }

  fft(a0, invert);
  fft(a1, invert);

  double ang = 2 * PI / n * (invert ? -1 : 1);
  complex<double> w(1), wn(cos(ang), sin(ang));
  for (int i = 0; 2 * i < n; i++) {
    a[i] = a0[i] + w * a1[i];
    a[i + n / 2] = a0[i] - w * a1[i];
    if (invert) {
      a[i] /= 2;
      a[i + n / 2] /= 2;
    }
    w *= wn;
  }
}

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
  vector<complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < a.size() + b.size())
    n <<= 1;
  fa.resize(n);
  fb.resize(n);

  fft(fa, false);
  fft(fb, false);
  for (int i = 0; i < n; i++)
    fa[i] *= fb[i];
  fft(fa, true);

  vector<int> result(n);
  for (int i = 0; i < n; i++)
    result[i] = round(fa[i].real());
  return result;
}

signed main() {
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 g(seed);

  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int N;
  cin >> N;

  int x, y;
  cin >> x >> y;

  int k = 2e9;

  vector<pair<int, int>> p(N);
  for (auto &e : p) {
    cin >> e.first >> e.second;
  }
  std::shuffle(p.begin(), p.end(), g);

  auto brute = [&](unordered_map<int, vector<int>> &umap, int l, int r) {
    int x = 1e9, y = 1e9;
    function<void(int, int)> all_possibilities = [&](int index, int bits) {
      if (index == r) {
        if (umap.find(x * k + y) == umap.end()) {
          umap[x * k + y] = vector<int>(r - l + 1, 0);
        }
        umap[x * k + y][bits]++;
        return;
      }

      all_possibilities(index + 1, bits);
      x += p[index].first;
      y += p[index].second;
      all_possibilities(index + 1, bits + 1);
      x -= p[index].first;
      y -= p[index].second;
      return;
    };

    all_possibilities(l, 0);

    return;
  };

  unordered_map<int, vector<int>> umap_1, umap_2;
  brute(umap_1, 0, N / 2);
  brute(umap_2, N / 2, N);

  vector<int> ans(N + 1, 0);
  for (auto e : umap_1) {
    int px = e.first / k - 1e9;
    int py = e.first % k - 1e9;

    int hx, hy;

    hx = (x - px);
    hx += 1e9;
    hy = (y - py);
    hy += 1e9;

    if (umap_2.find(hx * k + hy) == umap_2.end())
      continue;
    vector<int> cnt_2 = umap_2[hx * k + hy];
    vector<int> cnt_1 = e.second;
    vector<int> result = multiply(cnt_1, cnt_2);
    for (int i = 0; i < (int)result.size(); ++i) {
      ans[i] += result[i];
    }
  }

  for (int i = 1; i <= N; ++i) {
    cout << ans[i] << endl;
  }

  return 0;
}
