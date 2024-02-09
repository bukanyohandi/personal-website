#include <bits/stdc++.h>
using namespace std;
int n;
string data;
char x;
bool isfirst = true, found, again;
bool check(int pos, string x) {
  int tmp, piv, piv2;
  // row
  tmp = (pos / (n * n)) * (n * n);
  for (int i = 0; i < n * n; ++i) {
    if ((tmp + i) == pos)
      continue;
    if (x[tmp + i] == x[pos])
      return false;
  }
  // column
  tmp = pos % (n * n);
  for (; tmp < (n * n * n * n); tmp += n * n) {
    if (tmp == pos)
      continue;
    if (x[tmp] == x[pos])
      return false;
  }
  // block
  piv = (pos / (n * n * n)) * n * n * n;
  tmp = ((pos % (n * n)) / n) * n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      piv2 = piv + (i * n * n) + (tmp + j);
      if (piv2 == pos)
        continue;
      if (x[piv2] == x[pos])
        return false;
    }
  }
  return true;
}
void solve(int pos, string x) {
  //	for(int i=0;i<data.length();++i){
  //		cout<<data[i];
  //		if((i+1)%(n*n)==0) cout<<endl;
  //		else cout<<" ";
  //	}
  //	getchar();
  //	for(int i=0;i<=8;++i) cout<<x[i];
  //	cout<<endl;
  if (found)
    return;
  if (pos >= (n * n * n * n)) {
    found = true;
    data = x;
    return;
  } else if (x[pos] != '0')
    solve(pos + 1, x);
  else {
    for (int i = 1; i <= n * n; ++i) {
      x[pos] = i + '0';
      if (check(pos, x))
        solve(pos + 1, x);
      x[pos] = '0';
    }
  }
  return;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  while (cin >> n) {
    again = false;
    found = false;
    data = "";
    if (!isfirst)
      cout << endl;
    else
      isfirst = false;
    for (int i = 0; i < n * n; ++i) {
      for (int j = 0; j < n * n; ++j) {
        cin >> x;
        data += x;
      }
    }
    solve(0, data);
    for (int i = 0; i < data.length(); ++i) {
      if (data[i] == '0' || !check(i, data)) {
        cout << "NO SOLUTION" << endl;
        again = true;
        break;
      }
    }
    if (again)
      continue;
    for (int i = 0; i < data.length(); ++i) {
      cout << data[i];
      if ((i + 1) % (n * n) == 0)
        cout << endl;
      else
        cout << " ";
    }
  }
}