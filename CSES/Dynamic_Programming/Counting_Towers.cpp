#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
template <typename T>
using vec = vector<T>;
using ll = long long;
const ll MOD = 1e9 + 7;
int main()
{
    int t;
    cin >> t;
    vec<int> _list;
    int limit = 0;
    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;
        _list.eb(n);
        limit = max(limit, n);
    }
    vec<vec<ll>> f(limit, vec<ll>(2));
    f[0][0] = f[0][1] = 1;
    for (int i = 1; i < limit; i++)
    {
        f[i][0] = (f[i - 1][0] * 4 + f[i - 1][1]) %MOD;
        f[i][1] = (f[i - 1][0] + f[i - 1][1] * 2)%MOD;
    }
    for(int&a: _list){
        cout << (f[a - 1][0] + f[a - 1][1]) % MOD << endl;
    }
        return 0;
}