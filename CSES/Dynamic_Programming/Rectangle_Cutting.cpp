#include <bits/stdc++.h>
using namespace std;
#define INF 1000000
int dp[501][501];
int main(){
    int a, b;
    cin >> a >> b;
    for (int i = 1; i <= a && i <= b; i++){
        dp[i][i] = 0;
    }
    for (int l = 1; l <= a; l++){
        for (int w = 1; w <= b; w++){
            if(l == w)
                continue;
            dp[l][w] = INF;
            for (int d_l = 1; d_l < l; d_l++){
                dp[l][w] = min(dp[l][w], dp[d_l][w] + dp[l - d_l][w] + 1);
            }
            for (int d_w = 1; d_w < w; d_w++){
                dp[l][w] = min(dp[l][w], dp[l][d_w] + dp[l][w - d_w] + 1);
            }
        }
    }
    cout << dp[a][b] << endl;

    return 0;
}