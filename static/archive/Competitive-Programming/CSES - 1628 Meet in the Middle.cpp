#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, x;
    cin >> n >> x;

    vector<int> t(n);
    for(int i = 0; i < n; ++i){
        cin >> t[i];
    }

    int half = n / 2;
    vector<int> s1, s2;
    for(int i = 0; i < (1 << half); ++i){
        int sum = 0;
        for(int j = 0; j < half; ++j){
            if(sum > 1e9) break;
            if(i & (1 << j)) sum += t[j];
        }
        if(sum > 1e9) continue;
        s1.push_back(sum);
    }
    for(int i = 0; i < (1 << (n - half)); ++i){
        int sum = 0;
        for(int j = 0; j < n - half; ++j){
            if(sum > 1e9) break;
            if(i & (1 << j)) sum += t[half + j];
        }
        if(sum > 1e9) continue;
        s2.push_back(sum);
    }
    sort(s2.begin(), s2.end());
    long long ans = 0;
    for(int i = 0; i < s1.size(); ++i){
        int le, ri, mid, mid1 = -1, mid2 = -1;
        le = 0;
        ri = (int)s2.size() - 1;
        while(le <= ri){
            mid = (le + ri) / 2;
            if(s1[i] + s2[mid] == x){
                mid1 = mid;
                ri = mid - 1;
            } else if(s1[i] + s2[mid] < x){
                le = mid + 1;
            } else {
                ri = mid - 1;
            }
        }
        le = 0;
        ri = (int)s2.size() - 1;
        while(le <= ri){
            mid = (le + ri) / 2;
            if(s1[i] + s2[mid] == x){
                mid2 = mid;
                le = mid + 1;
            } else if(s1[i] + s2[mid] < x){
                le = mid + 1;
            } else {
                ri = mid - 1;
            }
        }
        if(mid1 != -1 && mid2 != -1){
            ans += (mid2 - mid1 + 1);
        }
    }
    cout << ans << endl;
}