#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define F first
#define S second
using pii = pair<int, int>;
int main()
{
    int N, C;
    cin >> N >> C;
    vector<pii> ops;
    for (int i = 0; i < N; i++)
    {
        int type, v;
        cin >> type >> v;
        ops.emplace_back(type, v);
    }
    int val = (1LL << 31) - 1;
    int val2 = 0;
    vector<pii> Vs(N);
    for (int i = 0; i < N; i++){
        int &type = ops[i].F;
        if (type == 1)
        {
            val = Vs[i].F = (val & ops[i].S);
            val2 = Vs[i].S = (val2 & ops[i].S);
        }
        else if(type == 2){
            val = Vs[i].F = (val | ops[i].S);
            val2 = Vs[i].S = (val2 | ops[i].S);
        }
        else if(type == 3){
            val = Vs[i].F = (val ^ ops[i].S);
            val2 = Vs[i].S = (val2 ^ ops[i].S);
        }
    }
    for (int i = 0; i < N; i++)
    {
        int ans = 0;
        for (int j = 0; j < 30;j++){
            int bitmask = (1 << j);
            if (C & (bitmask))
            {
                ans += Vs[i].F & bitmask;
            }
            else{
                ans += Vs[i].S & bitmask;
            }
        }
        C = ans;
        cout << ans << endl;
    }

        return 0;
}