#include <bits/stdc++.h>
using namespace std;

int T;
using Iter = vector<int>::iterator;

vector<int> ANS;

int seq[100000];

// combine dynamic programming & binary search

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;

    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> seq[i];
    }
    ANS.emplace_back(seq[0]);
// 1 2 4 3 8 5 10 12 7
// 1 2 3 8 10 12 
// 1 2 3 5 7 10 12
// ANS : 1 2 3 4 5 10 12
    for (int i = 1; i < N; i++){
        if(seq[i] > ANS.back()){
            ANS.emplace_back(seq[i]);
        }else{
            Iter it = lower_bound(ANS.begin(), ANS.end(), seq[i]);
            if(seq[i] < *it)
                *it = seq[i];
        }
    }
    cout << ANS.size() << endl;

    return 0;
}