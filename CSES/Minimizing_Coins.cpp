// AC 2022-02-10 11:29:51
#include <bits/stdc++.h>
#define INF (INT_MAX-1)
using namespace std;
int T;
vector<int> C;
int dp[1000001];
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    int desire;
    cin >> N >> desire;
    C.resize(N);
    for (int i = 0; i < N; i++){
        cin >> C[i];
    }
    fill(dp, dp + desire + 1, INF);
    dp[0] = 0;
    for (int coin: C){
        for (int j = coin; j <= desire; j++){
            dp[j] = min(dp[j - coin] + 1, dp[j]);
        }
    }
    cout << (dp[desire] != INF ? dp[desire] : -1)  << endl;
    return 0;
}