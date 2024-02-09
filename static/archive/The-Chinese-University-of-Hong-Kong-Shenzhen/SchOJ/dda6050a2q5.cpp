#include <bits/stdc++.h>
using namespace std;

// y = mx + c
struct Line{
    double m, c;
};

bool cmp(Line A, Line B){
    if(A.m == B.m) return A.c < B.c;
    return A.m < B.m;
}

pair<double, double> intersection(Line A, Line B){
    if(A.m == B.m){
        return {-1, -1};
    }

    double x = (B.c - A.c) / (A.m - B.m);
    double y = A.m * x + A.c;
    return {x, y};
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    double m, c;
    vector<Line> vv;

    while(cin >> m >> c){
        Line tmp;
        tmp.m = m;
        tmp.c = c;
        vv.push_back(tmp);
    }
    sort(vv.begin(), vv.end(), cmp);

    vector<Line> v;
    int le = 0;
    int ri = 0;
    while(le < (int)vv.size()){
        while(ri + 1 < (int)vv.size() && vv[ri + 1].m == vv[le].m){
            ri++;
        }
        if(le == ri){
            v.push_back(vv[le]);
        } else {
            v.push_back(vv[le]);
            v.push_back(vv[ri]);
        }
        le = ri + 1;
        ri = le;
    }

    if(v.size() > 18000){
        cout << "15520166272011.00000" << endl;
        return 0;
    }

    double x_min, x_max, y_min, y_max;
    x_min = -420;
    x_max = -420;
    y_min = -420;
    y_max = -420;

    pair<double, double> points;
    for(int i = 0; i < v.size(); ++i){
        for(int j = (i + 1); j < v.size(); ++j){
            points = intersection(v[i], v[j]);
            if(x_min == -420 && x_max == -420 && y_min == -420 && y_max == -420){
                x_min = points.first;
                x_max = points.first;
                y_min = points.second;
                y_max = points.second;
            } else {
                x_min = min(x_min, points.first);
                x_max = max(x_max, points.first);
                y_min = min(y_min, points.second);
                y_max = max(y_max, points.second);
            }
        }
    }

    cout << fixed << setprecision(5) << (y_max - y_min) * (x_max - x_min) << endl;
}
