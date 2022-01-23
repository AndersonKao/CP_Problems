#include <iostream>
using namespace std;
#define MOD 1000000007
int N;
long long dpa[1000006];

int main(){
    cin >> N;
    long long todel = 1;
    long long ans = 1;
    for(int i = 1; i <= N; i++){
        if(i != N){
            todel *= 2;
            todel %= MOD;
        }
        ans *= i;
        // if(ans % MOD > todel)
            ans %= MOD;
    }
    // for(int i = 3; i <= N; i++){
    //     cout << dpa[i] << " ";
    //     if(i % 10 == 0)
    //         cout << '\n';
    // }
    if(ans < todel)
        ans += MOD;
    cout <<(ans - todel) % MOD << endl;
    return 0;
}