#include <bits/stdc++.h>
using namespace std;

int T;

void solve(){

}

int a[100], b[100];
bool solved = false;
int N, X;
void recur(int cur, int j){

    if(cur > X || solved)
        return;
    if(j == N){
        if(X == cur)
            solved = true;
        return ;
    }
    recur(cur + a[j], j+1);
    recur(cur + b[j], j+1);
}
bool dp[100][10001] = {false};
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N >> X;
    for (int i = 0; i < N;i++){
        cin >> a[i] >> b[i];
    }
    dp[0][a[0]] = dp[0][b[0]] = true;
    for (int i = 1; i < N; i++){
        int limit = min(a[i], b[i]);
        for (int j = 10000; j >= limit; j--){
            if(j - a[i] >= 0){
                dp[i][j] = dp[i - 1][j - a[i]];
            }
            if(j - b[i] >= 0){
                dp[i][j] = dp[i][j] || dp[i - 1][j - b[i]];
            }
        }
    }

    cout << (dp[N - 1][X] ? "Yes\n" : "No\n");

    return 0;
}