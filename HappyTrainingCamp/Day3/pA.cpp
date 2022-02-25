#include <bits/stdc++.h>
using namespace std;

long long dp[2][3];
int main(){
    int N;
    cin >> N;
    int a, b, c;
    int r = 0;
    for (int i = 1; i <= N; i++){
        cin >> a >> b >> c;
        dp[r][0] = max(dp[r^1][1], dp[r^1][2]) + a;
        dp[r][1] = max(dp[r^1][0], dp[r^1][2]) + b;
        dp[r][2] = max(dp[r^1][0], dp[r^1][1]) + c;
        r ^= 1;
    }
    cout << max(dp[r^1][0], max(dp[r^1][1], dp[r^1][2])) << endl;
}