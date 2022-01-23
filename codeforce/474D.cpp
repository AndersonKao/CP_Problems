// AC Jul/08/2020 17:27UTC+8
#include <iostream>
using namespace std;

int T, K, qL, qR;

const long long mod = 1000000007;
long long ansseq[100005];
long long precal[100005] = {0};
int main(){
    cin >> T >> K;

    for(int i = 1; i < 100005; i++){
        if(i < K)
            ansseq[i] = 1;
        else if(i == K)
            ansseq[i] = 2;
        else{
            ansseq[i] = ansseq[i-1] % mod + ansseq[i - K] % mod;
        }
        precal[i] = precal[i-1] + ansseq[i];    
    }


    while(T--){
        cin >> qL >> qR;
        cout << (precal[qR] - precal[qL-1]) % mod << '\n';
    }

    return 0;
}