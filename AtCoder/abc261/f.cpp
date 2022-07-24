#include <bits/stdc++.h>

using namespace std;

vector<int> BIT;
int BITN;
int N;
using ll = long long;
#define al(x) x.begin(), x.end()
void modify(int i, int v)
{
    int res = i;
    while(res <= BITN){
        BIT[res] += v;
        res += (res) & (-res);
    }
}
int query(int i){
    int ans = 0;
    while(i > 0){
        ans += BIT[i];
        i -= (i) & (-i);
    }
    return ans;
}
using pii = pair<int, int>;
int main()
{
    cin >> N;
    vector<int> C(N);
    vector<int> X(N);
    vector<vector<int>> XbyC(N+1);
    vector<vector<int>> XibyC(N+1);
    BIT.resize(N + 1, 0);
    BITN = N+1;
    for (int i = 0; i < N; i++)
        cin >> C[i];
    for (int i = 0; i < N; i++){
        cin >> X[i];
        XbyC[C[i]].emplace_back(X[i]);
        XibyC[C[i]].emplace_back(i);
    }
    vector<int> un(N);
    for (int i = N-1; i >= 0; i--){
        un[i] = query(X[i]-1);
        modify(X[i], 1);
    }
    ll ans = 0;
    for (int i = 1; i <= N; i++)
    {
        vector<int> &Vc = XbyC[i];
        vector<int> Vco = Vc;
        sort(al(Vco));
        Vco.resize(distance(Vco.begin(), unique(al(Vco))));
        for(int&e: Vc){
            e = (lower_bound(al(Vco), e) - Vco.begin()) + 1;
        }
        vector<int> loun(Vc.size(), 0);
        BITN = Vc.size() + 1;
        fill(BIT.begin(), BIT.begin() + BITN, 0);
        for (int j = Vc.size() - 1; j >= 0; j--)
        {
            int q = query(Vc[j]-1);
            modify(Vc[j], 1);
            ans += (un[XibyC[i][j]] - q);
        }
    }
    cout << ans << endl;
    return 0;
}