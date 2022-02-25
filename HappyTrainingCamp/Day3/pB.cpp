#include <bits/stdc++.h>
using namespace std;

int T;

using LL = long long;
LL dp[100001];
LL wei[100001];
LL v[100001];
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N, W;
    cin >> N >> W;
    for (int i = 0; i < N; i++){
        cin >> wei[i] >> v[i];
    }
    fill(dp, dp + W + 1, 0);
    for (int i = 0; i < N; i++){
        for (int w = W; w >= wei[i]; w--){
            dp[w] = max(dp[w], dp[w - wei[i]] + v[i]);
        }
    }
    cout << dp[W] << endl; 

    return 0;
}