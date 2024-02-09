#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct Matrix{
    long long val[2][2];
    Matrix(){
        for(int i = 0; i < 2; ++i){
            for(int j = 0; j < 2; ++j){
                val[i][j] = 0;
            }
        }
    }
};

Matrix mult(Matrix A, Matrix B){
    Matrix C = Matrix();
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < 2; ++j){
            for(int k = 0; k < 2; ++k){
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

    if(B == 0){
        cout << 0 << endl;
    } else {
        Matrix M = Matrix();
        M.val[0][0] = 1;
        M.val[0][1] = 1;
        M.val[1][0] = 1;

        cout << pow(M, B).val[1][0] << endl;
    }
}