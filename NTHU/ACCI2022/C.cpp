#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
#define F first
#define S second
#define eb emplace_back
template <typename T>
using vec = vector<T>;
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;

int main(){
    int N, K;
    cin >> N >> K;
    vec<vec<pair<int, int>>> cla(K+1);
    REP(i, N){
        int l, r;
        cin >> l >> r;
        cla[l].eb(i, 1);
        cla[r].eb(i, 2);
    }
    vec<bool> unpin(N, true);
    set<int> myS;
    int ans = 0;
    for (int i = 1; i <= K; i++)
    {
        bool pin = false;
        for(auto &e: cla[i]){
            if(e.S == 1){
                myS.emplace(e.F);
            }
            else{
                auto it = myS.find(e.F);
                if(it != myS.end()){
                    pin = true;
                }
            }
        }
        if(pin){
            ans++;
            myS.clear();
        }
                
    }
    cout << ans << endl;
    return 0;
}