// AC Sep/04/2020 17:08UTC+8
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define MOD 100000000
int N[2];
int K[2];
long long whorse[400][400][15];
long long wfoot[400][400][15];
// last para 0 for footmen, 1 for horsemen 
int main(){
    cin >> N[0] >> N[1] >> K[0] >> K[1];
    // int reN[2] = {N[0], N[1]};
    // cout << N[0] << " " << N[1] << " " << K[0] << " " << K[1] << "\n";
    memset(whorse, 0, sizeof(whorse));
    memset(wfoot, 0, sizeof(wfoot));
    whorse[0][1][1] = wfoot[1][0][1] = 1;
    int Li = 0, Lj = 0;
    for (int limit = 1; limit <= N[0] + N[1]; limit++)
    {
        Li = 0, Lj = limit;
        for (; Li <= limit; Li++, Lj--){
            for (int k = 1; k <= min(N[0], K[0]); k++)
            {
                wfoot[Li + 1][Lj][k + 1] += wfoot[Li][Lj][k];
                wfoot[Li + 1][Lj][k + 1] %= MOD;
                whorse[Li][Lj + 1][1] += wfoot[Li][Lj][k];
                whorse[Li][Lj + 1][1] %= MOD;
            }
            // place horsemen
            for (int k = 1; k <= min(N[1], K[1]); k++)
            {
                whorse[Li][Lj + 1][k + 1] += whorse[Li][Lj][k];
                wfoot[Li + 1][Lj][1] += whorse[Li][Lj][k];
                whorse[Li][Lj + 1][k + 1] %= MOD;
                wfoot[Li + 1][Lj][1] %= MOD;
            }
        }
    }
    // cout << "footmen:\n";
    // for (int i = 0; i <= N[0]; i++){
    //     for (int j = 0; j <= N[1]; j++){
    //         cout << "{";
    //         for (int k = 1; k <= min(N[0], K[0]); k++){
    //             cout << wfoot[i][j][k] << (k == min(N[0], K[0]) ? "} " : ", ");
    //         }
    //     }
    //     cout << endl;
    // }
    // cout << "horsemen:\n";
    // for (int i = 0; i <= N[0]; i++){
    //     for (int j = 0; j <= N[1]; j++){
    //         cout << "{";
    //         for (int k = 1; k <= min(N[1], K[1]); k++){
    //             cout << whorse[i][j][k] << (k == min(N[1], K[1]) ? "} " : ", ");
    //         }
    //     }
    //     cout << endl;
    // }
        long long ans = 0;
    
    for (int i = 1; i <= min(N[0], K[0]); i++){
        ans += wfoot[N[0]][N[1]][i];
        ans %= MOD;
    }
    for (int i = 1; i <= min(N[1], K[1]); i++){
        ans += whorse[N[0]][N[1]][i];
        ans %= MOD;
    }
    cout << ans % MOD << endl;
    return 0;
}