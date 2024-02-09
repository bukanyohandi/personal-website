#include <bits/stdc++.h>
using namespace std;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

int k;
double ans[8][8], p[101][8][8];

bool inRange(int x, int y){
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

int main(){
    cin >> k;

    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            ans[i][j] = 1.0;
        }
    }

    for(int x = 0; x < 8; ++x) for(int y = 0; y < 8; ++y){
        memset(p, 0, sizeof(p));
        p[0][x][y] = 1.0;

        for(int kk = 1; kk <= k; ++kk){
            for(int i = 0; i < 8; ++i){
                for(int j = 0; j < 8; ++j){
                    vector<pair<int, int>> v;
                    for(int l = 0; l < 4; ++l){
                        if(inRange(i + dx[l], j + dy[l])){
                            v.push_back({i + dx[l], j + dy[l]});
                        }
                    }
                    for(pair<int, int> xy: v){
                        p[kk][xy.first][xy.second] += (double)p[kk - 1][i][j] / v.size();
                    }
                }
            }
        }

        for(int i = 0; i < 8; ++i){
            for(int j = 0; j < 8; ++j){
                ans[i][j] *= 1 - p[k][i][j];
            }
        }
    }

    double sum_ans = 0;
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            sum_ans += ans[i][j];
            // if(j != 0) cout << " ";
            // cout << fixed << setprecision(4) << ans[i][j];
        }
        // cout << endl;
    }
    cout << fixed << setprecision(6) << sum_ans << endl;
}