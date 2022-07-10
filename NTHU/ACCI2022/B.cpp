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
    int n, q;
    cin >> n >> q;
    vec<int> V(n);
    for(int &e: V){
        cin >> e;
    }

    int base = 100001;
    vec<vec<int>> f(n, vec<int>(200002, 0));
    f[0][base] = 1;
    f[0][base + V[0]] = 1;
    f[0][base - V[0]] = 1;
    for (int i = 1; i < n; i++)
    {
        for (int k = 0; k < 200002; k++){
            if(k - V[i] >= 0){
                f[i][k] = f[i-1][k - V[i]] | f[i][k];
            }
            f[i][k] |= f[i - 1][k];
            if(k + V[i] <= 200001)
                f[i][k] |= f[i - 1][k + V[i]];
        }
    }

    while (q--)
    {
        int m;
        cin >> m;
        if (f[n-1][base+m])
        {
            cout << "YES\n";
        }
        else
            cout << "NO\n";
    }

    return 0;
}