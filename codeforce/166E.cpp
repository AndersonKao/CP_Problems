// AC Jul/08/2020 19:44UTC+8
#include <iostream>
using namespace std;

long long nDDDD;
long long nABC;
const long long mod = 1e9 + 7;
int main(){
    int N;
    cin >> N;
    nDDDD = 1;
    nABC = 0;
    for(int i = 1; i <= N; i++){
        long long nextD = ((nABC % mod) * 3);
        long long nextABC = ((nABC % mod) * 2 + nDDDD % mod);
        nDDDD = nextD % mod;
        nABC = nextABC % mod;
    }
    cout << nDDDD % mod << '\n';
    return 0;
}