#include <bits/stdc++.h>
using namespace std;

#pragma GCC target("popcnt")

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    vector<bitset<3000>> grid(n);
    for(auto &i: grid){
        cin >> i;
    }
    long long ans = 0;
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            long long c2 = (long long)(grid[i] & grid[j]).count(); 
            ans += c2 * (c2 - 1) / 2;
        }
    }
    cout << ans << endl;
}