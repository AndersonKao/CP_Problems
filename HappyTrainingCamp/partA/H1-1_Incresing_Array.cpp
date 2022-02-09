#include <bits/stdc++.h>
using namespace std;

unsigned N;
unsigned seq[200000];
int main(){
    cin >> N;
    for (unsigned i = 0; i < N; i++){
        cin >> seq[i];
    }
    unsigned long long ans = 0;
    for (unsigned i = 1; i < N; i++){
        if(seq[i] < seq[i-1]){
            ans += (seq[i - 1] - seq[i]);
            seq[i] = seq[i - 1];
        }
    }
    cout << ans << "\n";
    return 0;
}