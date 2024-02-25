#include <bits/stdc++.h>
#include "matrix.hpp"
using namespace std;

bool compare(string filename_1, string filename_2){
    ifstream fin_1(filename_1.c_str());
    ifstream fin_2(filename_2.c_str());

    int cnt = 0;
    string s, t;
    while(getline(fin_1, s)){
        getline(fin_2, t);
        cnt++;

        if(s != t){
            cout << "[log] differences found in line " << cnt << ", where:\n          s = " << s << "\n          t = " << t << endl; 
            return false;
        }
    }
    if(getline(fin_2, t)){
        cout << "[log] t is larger than s" << endl;
        return false;
    }
    
    cout << "[log] " << cnt << " lines were compared" << endl;
    return true;
}

int main(){
    vector<string> filenames = {"matrices/result-locality.txt",
                                "matrices/result-simd.txt",
                                "matrices/result-openmp.txt",
                                "matrices/result-mpi.txt",
                                "matrices/result-cuda.txt"};

    for(auto filename: filenames){
        cout << "Comparing matrices/result-naive.txt and " << filename << "..." << endl;
        cout << (compare("matrices/result-naive.txt", filename) ? "Both files are identical" : "Both files are not identical") << endl << endl;
    }

    return 0;
}