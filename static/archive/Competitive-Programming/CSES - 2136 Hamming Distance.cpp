#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, k;
    cin >> n >> k;

    vector<int> v(n, 0);
    for(int i = 0; i < n; ++i){
        string s;
        cin >> s;
        for(int j = 0; j < k; ++j){
            if(s[j] == '1'){
                v[i] += 1 << (k - j - 1);
            }
        }
    }
    int ans = k;
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            ans = min(ans, __builtin_popcount(v[i] ^ v[j]));
        }
    }
    cout << ans << endl;
}