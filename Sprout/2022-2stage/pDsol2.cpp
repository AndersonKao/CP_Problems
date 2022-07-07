#include <bits/stdc++.h>
using namespace std;

template <typename T>
using vec = vector<T>;
#define al(x) x.begin(), x.end()

int main(){
    
    int N, Q;
    cin >> N >> Q;
    vec<int> seq(N);
    for(int&e: seq)
        cin >> e;
    sort(al(seq));
    while(Q--){
        int ql, qr;
        cin >> ql >> qr;
        cout << distance(lower_bound(al(seq), ql), upper_bound(al(seq), qr)) << endl;
    }

    return 0;
}