#include <bits/stdc++.h>
using namespace std;

int T;
long long target;

long long seq[200000];
long long prefix[200000];
int counts[200000];
map<long long, int> M;
using Iter = map<long long, int>::iterator;
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N >> target;
    fill(counts, counts + N, 0);
    for (int i = 0; i < N; i++)
        cin >> seq[i];
    for (int i = 0; i < N;i++){
        if(i == 0)
            prefix[i] = seq[i];
        else
            prefix[i] = prefix[i - 1] + seq[i];
    }

    long long curTarget;
    long long ans = 0;
    int used = 0;
    for (int i = N - 1; i >= 0; i--){
        curTarget = target + prefix[i];
        Iter it = M.find(curTarget);
        if(it != M.end()){
            ans += counts[it->second];
        }
        it = M.find(prefix[i]);
        // insert;
        if(it == M.end()){
            M.emplace(prefix[i], used);
            counts[used]++;
            used++;
        }else{
            counts[it->second]++;
        }
    }

    Iter it = M.find(target);
    if(it != M.end())
        ans += counts[it->second];
    cout << ans << endl;

    return 0;
}