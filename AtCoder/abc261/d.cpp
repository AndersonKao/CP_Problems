#include<bits/stdc++.h>
using namespace std;
using ll = long long;
map<int, ll> Y;

int main(){
    int N;
    int M;
    cin >> N >> M;
    vector<ll> Vs(N);
    for (int i = 0; i < N; i++)
        cin >> Vs[i];
    for (int i = 0; i < M; i++){
        int c;
        ll y;
        cin >> c >> y;
        Y[c] += y;
    }
    vector<vector<ll>> dp(N, vector<ll>(N + 1, 0));
    dp[0][0] = 0;
    dp[0][1] = Vs[0] + Y[1];
    for (int r = 1; r < N; r++)
    {
        ll maxD = 0;
        for (int i = 1; i <= N; i++)
        {
            if(dp[r-1][i-1] != 0)
                dp[r][i] = dp[r - 1][i - 1] + Vs[r] + Y[i];
            maxD = max(maxD, dp[r - 1][i]);
        }
        dp[r][0] = max(dp[r - 1][0], maxD);
    }
    ll ans = 0;
    for(ll&e: dp[N-1]){
        ans = max(ans, e);
    }
    cout << ans << endl;
    return 0;
}