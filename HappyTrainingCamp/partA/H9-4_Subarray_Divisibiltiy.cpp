#include <bits/stdc++.h>
using namespace std;

int T;
long long target;

long long seq[200000];
long long pres[200000];
int counts[200000];
using Iter = map<long long, int>::iterator;
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N ;
    for (int i = 0; i < N; i++){
        cin >> seq[i];
        counts[i] = 0;
    }
    for (int i = 0; i < N; i++){
        if(i == 0)
            pres[0] = seq[0];
        else
            // how about 
            // pres[i] = pres[i-1] + seq[i]
            pres[i] = pres[i - 1] % N + seq[i] % N;
        pres[i] = (pres[i] >= 0 ? pres[i] % N : (N - (-pres[i]) % N));
//        cout << pres[i] << " ";
    }
 //   cout << "\n";
    long long curtarget;
    long long ans = 0;
    for (int i = N - 1; i >= 0; i--){
        curtarget = pres[i];
        ans += counts[curtarget];
        counts[curtarget]++;
    }
    // overall
    ans += counts[0];
    cout << ans << endl;

    return 0;
}