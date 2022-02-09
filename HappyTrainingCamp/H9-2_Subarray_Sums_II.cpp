#include <bits/stdc++.h>
using namespace std;

int T;
long long target;

long long seq[200000];
long long pres[200000];
int counts[200000];
//map<long long, int> M;
using Iter = map<long long, int>::iterator;
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N >> target;
    for (int i = 0; i < N; i++){
        cin >> seq[i];
        counts[i] = 0;
    }
    pres[0] = seq[0];
    for (int i = 1; i < N; i++)
        pres[i] = pres[i - 1] + seq[i];
    int used = 0;
    long long curtarget;
    long long ans = 0;
    for (int i = N - 1; i >= 0; i--){
        curtarget = target + pres[i];
        Iter it = M.find(curtarget);
        if(it != M.end()){
            ans += counts[it->second];
        }
        it = M.find(pres[i]);
        if(it == M.end()){
            M.emplace(pres[i], used);
            counts[used]++;
            used++;
        }else{
            counts[it->second]++;
        }
    }
    // overall

    Iter it = M.find(target);
    if(it!= M.end()){
        ans += counts[it->second];
    }
    cout << ans << endl;

    return 0;
}