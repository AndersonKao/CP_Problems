#include <iostream>
using namespace std;

int d[2][505][505] = {1};// 前i個寫好j行且有k個bug
int a[505];
int main (){
    std::ios_base::sync_with_stdio(false);
    int n, m, b, mod;
    cin >> n >> m >> b >> mod;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    d[0][0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= m; j++){
            for(int k = 0; k <= b; k++){
                if(j && k >= a[i])
                    d[i&1][j][k] = (d[(i&1)][j - 1][k - a[i]] + d[!(i&1)][j][k]) % mod;
                else
                    d[i&1][j][k] = d[!(i&1)][j][k] % mod;
            }
        }
    }
    int z = 0;
    for(int i = 0; i <= b; i++)
        z = (z + d[n & 1][m][i]) % mod;
    cout << z << "\n";
    return 0;
}