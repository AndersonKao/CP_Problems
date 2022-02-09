#include <bits/stdc++.h>
using namespace std;

long long seq[200000];

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> seq[i];
    }
    long long ans = 0;
    for (int i = 1; i < N; i++){
        if(seq[i] < seq[i-1]){
            ans += seq[i - 1] - seq[i];
            seq[i] = seq[i - 1];
        }
    }
    cout << ans << endl;

    return 0;
}