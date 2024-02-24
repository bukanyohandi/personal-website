/*
    Author: Yohandi - 120040025
*/

#include <bits/stdc++.h>
using namespace std;

struct Trie{
    int cnt = 0;
    Trie *next[26];
} *root;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, q, ans;
    string s;
    
    root = new Trie();

    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> s;
        Trie *cur = root;
        for(int j = 0; j < s.size(); ++j){
            if(cur -> next[s[j] - 'a'] == NULL){
                cur -> next[s[j] - 'a'] = new Trie();
            }
            cur = cur -> next[s[j] - 'a'];
            cur -> cnt += 1;
        }
    }

    cin >> q;
    for(int i = 0; i < q; ++i){
        cin >> s;
        Trie *cur = root;

        ans = 0;

        for(int j = 0; j < s.size(); ++j){
            if(cur -> next[s[j] - 'a'] == NULL){
                break;
            }
            cur = cur -> next[s[j] - 'a'];

            if(j + 1 == s.size()){
                ans = cur -> cnt;
            }
        }

        cout << ans << endl;
    }
}