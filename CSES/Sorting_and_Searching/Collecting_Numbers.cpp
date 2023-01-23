#include <bits/stdc++.h>
using namespace std;
 
unsigned seq[200000];
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    unsigned N;
    cin >> N;
 
    unsigned data;
    unsigned min = N + 1;
    unsigned ans = 0;
    for (unsigned i = 0; i < N; i++){
        cin >> data;
        seq[data - 1] = i + 1;
    }
    for (unsigned i = 1; i < N; i++){
        if(seq[i] < seq[i-1])
            ans++;
    }
    cout << ans + 1 << endl;
    return 0;
}
