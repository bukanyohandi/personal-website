#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct Matrix{
    long long val[6][6];
    Matrix(){
        for(int i = 0; i < 6; ++i){
            for(int j = 0; j < 6; ++j){
                val[i][j] = 0;
            }
        }
    }
};

Matrix mult(Matrix A, Matrix B){
    Matrix C = Matrix();
    for(int i = 0; i < 6; ++i){
        for(int j = 0; j < 6; ++j){
            for(int k = 0; k < 6; ++k){
                C.val[i][j] += A.val[i][k] * B.val[k][j];
                C.val[i][j] %= MOD;
            }
        }
    }
    return C;
}

Matrix pow(Matrix A, long long B){
    if(B == 1) return A;
    Matrix tmp = pow(A, B / 2);
    tmp = mult(tmp, tmp);
    if(B % 2 == 1) tmp = mult(tmp, A);
    return tmp;
}

int main(){
    long long B;
    cin >> B;

    if(B <= 6){
        int ans[] = {0, 1, 2, 4, 8, 16, 32};
        cout << ans[B] << endl;
    } else {
        Matrix M = Matrix();
        for(int i = 0; i < 6; ++i){
            M.val[0][i] = 1;
        }
        for(int i = 0; i < 5; ++i){
            M.val[i + 1][i] = 1;
        }

        cout << pow(M, B + 1).val[1][0] << endl;
    }
}