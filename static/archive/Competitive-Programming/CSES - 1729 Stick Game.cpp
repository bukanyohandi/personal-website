#include <bits/stdc++.h>
using namespace std;

int n, k;
int p[1000000 + 5];
int dp[1000000 + 5];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    for(int i = 1; i <= k; ++i){
        cin >> p[i];
        dp[p[i]] = 1;
    }

    for(int i = 1; i <= n; ++i){
        if(dp[i] == 0){
            for(int j = 1; j <= k; ++j){
                if(i - p[j] >= 1 && dp[i - p[j]] == 0){
                    dp[i] = 1;
                    break;
                }
            }
        }
        if(dp[i] == 1){
            cout << "W";
        } else {
            cout << "L";
        }
    }
    cout << endl;
}