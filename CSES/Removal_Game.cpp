// AC 2022-02-11 05:16:39
#include <iostream>
using namespace std;
long long dp[5000][5000];
long long prefix[5001];
int main(){

    int N;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> dp[i][i];
        prefix[i + 1] = prefix[i] + dp[i][i];
    }
    for (int k = 1; k < N; k++){
        for (int i = 0; i + k < N; i++){
            dp[i][i + k] = prefix[i + k + 1] - prefix[i] - min(dp[i][i + k - 1], dp[i + 1][i + k]);
        }
    }
    cout << dp[0][N - 1] << endl;
    return 0;
}