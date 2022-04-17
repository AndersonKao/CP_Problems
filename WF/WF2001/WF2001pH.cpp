
#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;
#define REP(i, n) for(int i=0;i<n;i++)
#define REP1(i, n) for(int i=1;i<=n;i++)
#define F first
#define S second
int n, k;
struct CPR{
    int layer;
    int x, y;
};
vector<CPR> cpr;
vector<int> app;
vector<int> cur;
bool cmp_cpr(CPR& a, CPR& b){
    return a.layer < b.layer;
}

void init(){

    cpr.resize(k);
    app.resize(n);
    fill(app.begin(), app.end(), 0);
    cur.resize(n);
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int cnt = 1;
    while(cin >> n >> k){
        if(n == 0 && k == 0)
            break;
        init();
        int a, b;
        int units = 0;
        REP(i, k){
            cin >> a >> b;
            a--, b--;
            cpr[i].x = a, cpr[i].y = b;
            cpr[i].layer = max(app[a], app[b]);
            units = max(units, cpr[i].layer + 1);
            app[a] = app[b] = cpr[i].layer + 1;
        }
        sort(cpr.begin(), cpr.end(), cmp_cpr);
        int limit = 1 << n;
        bool sol = true;
        REP(test, limit){
            REP(i, n){
                cur[i] = (test & (1 << i) ? 1 : 0);
            }
            for(auto& c: cpr){
                a = cur[c.x];
                b = cur[c.y];
                cur[c.x] = min(a, b);
                cur[c.y] = max(a, b);
            }
            REP(i, n-1){
                if(cur[i] > cur[i+1]){
                    sol = false;
                    break;
                }
            }
            if(!sol)
                break;
        }
        cout << "Case " << cnt++ << " is ";
        if(!sol)
            cout << "not ";
            
        cout << "a sorting network and operates in " << units << " time units.\n";
#ifndef ONLINE_JUDGE
cout << "tsetjhoht\n";
#endif
    
    
    }

    return 0;
}
