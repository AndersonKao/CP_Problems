#include <bits/stdc++.h>
using namespace std;

int cases[100];
int dp[101][3] = {0};
#define MAXT 200
int main(){
    int N;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> cases[i];
    }

    for (int i = 1; i <= N; i++){
        int type = cases[i - 1];
        for (int j = 0; j < 3; j++)
            dp[i][j] = MAXT;
        // case 0: take a reset
        for (int j = 0; j < 3; j++)
        {
            dp[i][0] = min(dp[i][0], dp[i - 1][j] + 1);
            // 0, 1, 2
        }   
        // case 1: write contest
        if(type == 1 || type == 3){
            dp[i][1] = min(dp[i-1][0], dp[i-1][2]);
        }
        // case 2: go to gym
        if(type == 2 || type == 3){
            dp[i][2] = min(dp[i-1][0], dp[i-1][1]);
        }
    }
    cout << min(dp[N][0], min(dp[N][1], dp[N][2])) << endl;

    return 0;
}