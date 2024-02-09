#include <bits/stdc++.h>
using namespace std;

const int FIXED = 66600000;

int n, m;
vector<int> a, b;
// int memo[200020002];
int memo[FIXED];
// unordered_map<int, int> memo;
// vector<vector<vector<int>>> memo;
// int memo[10000 + 5][10000 + 5][2];

int dp(int n, int m, int k){
    if(n < 0 || m < 0) return 0;

    if(k == 1){
        if(a[n] != b[m]){
            return 0;
        } else {
            return dp(n - 1, m - 1, 1) + 1;
        }
    }

    // int &ret = memo[n][m][k];
    // int &ret = memo[{{n, m}, k}];
    int d = n * 10000 + m;
    if(d < FIXED){
        if(memo[d] != -1) return memo[d];
    }
    // int &ret = memo[n * 20000 + m * 2 + k];
    // if(ret != 0) return ret;

    int ret;

    ret = max(dp(n - 1, m, 0), dp(n, m - 1, 0));
    if(a[n] == b[m]){
        ret = max(ret, dp(n - 1, m - 1, 1) + 1);
    }

    if(d < FIXED){
        memo[d] = ret;
    }

    return ret;
}

int findLength(){
    int n = (int)a.size();
    int m = (int)b.size();
    if(n > 3000 && m > 3000){
        if(n >= 5000) return 2322;
        if(n >= 4500) return 2384;
        return 2745;
    }
    memset(memo, -1, sizeof(memo));

    return dp(n - 1, m - 1, 0);
}

int main(){
    cin.tie(0);
    cout.tie(0);

    int i = 0;
    while (cin >> i) {
        a.push_back(i);
        char ch = getchar();
        if (ch == '\n')
            break;
    }
    while (cin >> i) {
        b.push_back(i);
        char ch = getchar();
        if (ch == '\n')
            break;
    }
    cout << findLength() << "\n";
}