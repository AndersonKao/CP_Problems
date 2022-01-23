#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int T;
long long N;

void solve(long long N){
    long long limit = (long long)sqrt(N);
    // cout << limit << endl;
    long long MAX = 0;
    long long Ori, b;
    long long ansA = 0, ansB = INT32_MAX;
    for(long long i = 2; i <= limit; i++){
        if( N % i == 0){
            b = N-i;
            ansA = N / i;
            ansB = N - ansA;
            break;
        }
    }   
    if(ansA != 0)
        cout << ansA << ' ' << ansB << '\n';
    else
        cout << "1 " << N-1 << '\n';
}
int main(){
    cin >> T;
    while(T--){
        cin >> N;
        if(N&1){
            solve(N);
        }else{
            cout << N/2 << ' ' << N/2 << '\n';
        }
    }

    return 0;
}