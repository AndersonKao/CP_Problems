#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL cost[100000];
LL dp[100000][2];
string str[100000];
int main(){

    int N;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> cost[i];
    }
    for (int i = 0; i < N; i++){
        cin >> str[i];
    }
    dp[0][0] = 0;
    dp[0][1] = cost[0];

    for (int i = 1; i < N; i++){
        dp[i][1] = dp[i][0] = LLONG_MAX;
        bool valid0 = !(dp[i - 1][0] == LLONG_MAX);
        bool valid1 = !(dp[i - 1][1] == LLONG_MAX);
        if(valid0 && str[i] >= str[i-1]){
            dp[i][0] = min(dp[i][0], dp[i - 1][0]);
        }
        string Rev(str[i-1]);
        reverse(Rev.begin(), Rev.end());
        if(valid1 && str[i] >= Rev){
            dp[i][0] = min(dp[i][0], dp[i - 1][1]);
        }
        string RevI(str[i]);
        reverse(RevI.begin(), RevI.end());

        if(valid0 && RevI >= str[i-1]){
            dp[i][1] = min(dp[i][1], dp[i - 1][0] + cost[i]);
        }    
        if(valid1 && RevI >= Rev){
            dp[i][1] = min(dp[i][1], dp[i - 1][1] + cost[i]);
        }    
    }
    if(dp[N-1][0] == dp[N-1][1] && dp[N-1][0] == LLONG_MAX){
        cout << "-1\n";
    }else
        cout << min(dp[N - 1][0], dp[N - 1][1]);
    return 0;
}