#include <bits/stdc++.h>
 int dp[6][10000] = {0}; // 放在全域變數以讓compile過
 
using namespace std;

int main(){
    int coins[] = {0,1,5,10,25,50};
   // [dp[i][j] repsents 用{ai,ai,ai}付出j元有多少方法
    dp[0][0] = 1;
    for(int i = 1;i<=5;++i){
        for(int j=0;j<10000;++j){
            dp[i][j] = dp[i - 1][j];
            if( j - coins[i] >=0) 
            dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]] ;
            
        }
    }
    int a;
    while(cin >> a)
        cout << dp[5][a] << endl;
}