#include <bits/stdc++.h>
using namespace std;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false);
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
#define F first
#define S second
template <typename T>
using vec = vector<T>;
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << " := " << x << endl;
#define eb emplace_back
using pii = pair<int, int>;
#define depii(x) cout << "(" << x.first << ", " << x.second << endl;
int main()
{
    yccc;
    int Bnum = 1;
    int n;
    while(cin >> n){
        if(n == 0)
            break;
        vec<pii> soli;
        REP(i, n){
            int r, c;
            cin >> r >> c;
            r--, c--;
            soli.eb(r, c);
        }


        // row
        vec<pii> ansV(n);
        int best = numeric_limits<int>::max();
        vec<int> dp((1 << n), 100000000);
        for (int solr = 0; solr < n; solr++)
        {
            int c= 0;
            for (pii &e : ansV)
            {
                e.first = solr;
                e.second = c++;
            }
            #ifdef DEBUG
            for (int i = 0; i < n;i++){
                depii(ansV[i]);
            }
            #endif
            fill(al(dp), 100000000);
            dp[0] = 0;
            for (int i = 1; i < (1 << n); i++)
            {
                int numofi = 0;
                for (int k = 0; k < n; k++)
                    if(((1 << k) & i) != 0)
                        numofi++;
                for (int k = 0; k < n; k++)
                {
                    if(((1 << k) & i) != 0 ){
                        int id = i - (1 << k);
                        int cost = abs(soli[numofi-1].F - ansV[k].F) + abs(soli[numofi-1].S -ansV[k].S);
                        dp[i] = min(dp[i], dp[id] + cost);
                    }
                }
            }
            #ifdef DEBUG
            if(best > dp[(1 << n) - 1])
                cout << "renew to " << dp[(1 << n) - 1] << endl;
            #endif
            best = min(best, dp[(1 << n) - 1]);
        }
        for (int solc = 0; solc < n; solc++)
        {
            int r= 0;
            for (pii &e : ansV)
            {
                e.second= solc;
                e.first= r++;
            }
            #ifdef DEBUG
            for (int i = 0; i < n;i++){
                depii(ansV[i]);
            }
            #endif
            fill(al(dp), 100000000);
            dp[0] = 0;
            for (int i = 1; i < (1 << n); i++)
            {
                int numofi = 0;
                for (int k = 0; k < n; k++)
                    if(((1 << k) & i) != 0)
                        numofi++;
                for (int k = 0; k < n; k++)
                {
                    if(((1 << k) & i) != 0 ){
                        int id = i - (1 << k);
                        int cost = abs(soli[numofi-1].F - ansV[k].F) + abs(soli[numofi-1].S -ansV[k].S);
                        dp[i] = min(dp[i], dp[id] + cost);
                    }
                }
            }
            #ifdef DEBUG
            if(best > dp[(1 << n) - 1])
                cout << "renew to " << dp[(1 << n) - 1] << endl;
            #endif
            best = min(best, dp[(1 << n) - 1]);
        }
        int r= 0;
        for (pii &e : ansV)
        {
            e.first= r;
            e.second= r++;
        }
        #ifdef DEBUG
        for (int i = 0; i < n;i++){
            depii(ansV[i]);
        }
        #endif
        fill(al(dp), 100000000);
        dp[0] = 0;
        for (int i = 1; i < (1 << n); i++)
        {
            int numofi = 0;
            for (int k = 0; k < n; k++)
                if(((1 << k) & i) != 0)
                    numofi++;
            for (int k = 0; k < n; k++)
            {
                if(((1 << k) & i) != 0 ){
                    int id = i - (1 << k);
                    int cost = abs(soli[numofi-1].F - ansV[k].F) + abs(soli[numofi-1].S -ansV[k].S);
                    dp[i] = min(dp[i], dp[id] + cost);
                }
            }
        }
        #ifdef DEBUG
        if(best > dp[(1 << n) - 1])
            cout << "renew to " << dp[(1 << n) - 1] << endl;
        #endif
        best = min(best, dp[(1 << n) - 1]);
        r = 0;
        for (pii &e : ansV)
        {
            e.first = r;
            e.second = n-r-1;
            r++;
        }
        #ifdef DEBUG
        for (int i = 0; i < n;i++){
            depii(ansV[i]);
        }
        #endif
        fill(al(dp), 100000000);
        dp[0] = 0;
        for (int i = 1; i < (1 << n); i++)
        {
            int numofi = 0;
            for (int k = 0; k < n; k++)
                if(((1 << k) & i) != 0)
                    numofi++;
            for (int k = 0; k < n; k++)
            {
                if(((1 << k) & i) != 0 ){
                    int id = i - (1 << k);
                    int cost = abs(soli[numofi-1].F - ansV[k].F) + abs(soli[numofi-1].S -ansV[k].S);
                    dp[i] = min(dp[i], dp[id] + cost);
                }
            }
        }
        #ifdef DEBUG
        if(best > dp[(1 << n) - 1])
            cout << "renew to " << dp[(1 << n) - 1] << endl;
        #endif
        best = min(best, dp[(1 << n) - 1]);
        cout << "Board " << Bnum++ << ": " << best << " moves required.\n";
        cout << endl;
    }
    return 0;
}