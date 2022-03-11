#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
int ans[1000001];

int recur(int n){
    if(n < 0)
        return 0;
    if(ans[n])
        return ans[n];
    if(n == 0)
        return ans[n] = 1;
    ans[n] = 0;
    for (int i = 1; i <= 6; i++){
        ans[n] = (ans[n] + recur(n - i) % MOD) % MOD;
    }
    return ans[n];
}

int main(){
    int n;
    cin >> n;
    fill(ans, ans + n + 1, 0);
    recur(n);
    cout << ans[n];
    return 0;
}