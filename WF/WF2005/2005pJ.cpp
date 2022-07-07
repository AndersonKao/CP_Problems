#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
#define F first
#define S second
template <typename T>
using vec = vector<T>;
#define eb emplace_back
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << " := " << x << endl;

using ll = long long;
int main()
{
    int n, k;
    int caseN = 1;
    while (cin >> n >> k)
    {
        if(n == 0 && k == 0)
            break;
        vec<ll> cover((1 << n));
        REP(i, n)
            cin >> cover[(1 << i)];
        int m;
        cin >> m;
        vec<int> exist;
        REP(i, m)
        {
            int t;
            cin >> t;
            int id = 0;
            REP(j, t)
            {
                int val;
                cin >> val;
                val--;
                id += (1 << val);
            }
            cin >> cover[id];
            REP(j, n){
                if(((1 << j) & id) != 0){
                    cover[(1 << j)] -= cover[id];
                }
            }
            exist.eb(id);
        }
        #ifdef DEBUG
        for (int i = 0; i < (1 << n); i++){
            for (int j = 0; j < n; j++)
            {
                if((1 << j) & i)
                    cout << "1";
                else
                    cout << "0";
            }
            cout << ": " << cover[i] << endl;
        }
        #endif
        int ans = 0;
        vec<int> ansV(k);
        for (int i = 0; i < (1 << n); i++)
        {
            int cnt = __builtin_ctz(i);
            int cur = 0;
            //debug(cnt);
            if (cnt != k)
                continue;
            //cout << "go for check\n";
            REP(j, n)
            {
                if(((1 << j) & i) != 0){
                    cur += cover[(1 << j)];
                }
            }
            REP(j, m){
                if((exist[j] & i) != 0){
                    cur += cover[exist[j]];
                }
            }
            if(cur > ans){
                ans = cur;
                ansV.clear();
                REP(j, n)
                {
                    if((1 << j) & i)
                        ansV.eb(j);
                }
            }else if(cur == ans){
                vec<int> newA;
                REP(j, n)
                {
                    if((1 << j) & i)
                        newA.eb(j);
                }
                bool replace = false;
                REP(j, n)
                {
                    if(newA[j] != ansV[j]){
                        if(newA[j] < ansV[j])
                            replace = true;
                        break;
                    }
                }
                if(replace)
                    ansV = newA;
            }
        }
        cout << "Case Number  " << caseN++ << endl;
        cout << "Number of Customers: " << ans << endl;
        cout << "Locations recommended:";
        for(int& a: ansV)
            cout << " " << a + 1;
        cout << endl;
        cout << endl;
    }
    return 0;
}