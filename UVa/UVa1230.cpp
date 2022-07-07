// AC 2022-06-24 00:24:22
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int mulModn(int x, int y, int n){
    int tmp = x;
    ll ans = 1;
    while(y){
        if(y &1){
            ans *= tmp;
            ans %= n;
        }
        tmp = tmp * tmp %n;
        y >>= 1;
    }
    return ans;
}
int main(){
    int T;
    cin >> T;
    while(T--){
        int x, y, n;
        cin >> x >> y >> n;
        //cout << x << y << n << endl;
        cout << mulModn(x, y, n) << endl;
    }
    cin >> T;
    return 0;
}