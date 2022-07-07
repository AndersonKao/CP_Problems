#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;
inline ll mod(ll a){
    return (a % MOD + MOD) % MOD;
}
inline ll mul(ll a, ll b){
    ll ans = 0;
    ll res = a;
    while (b > 0)
    {
        if(b & 1)
            ans = mod(ans + res);
        res = mod(res + res);
        b >>= 1;
    }
    return ans;
}
pair<ll, ll>fib(ll n) // f(n, n+1)
{
    if(n == 0){
        return {0, 1};
    }
    pair<ll, ll> p = fib(n >> 1);
    ll c = mul(p.first, mod(p.second * 2 - p.first));
    ll d = mod(mul(p.first, p.first)+ mul(p.second, p.second));
    if(n & 1){
        return {d, mod(c + d)};
    }
    return {c, d};
}

int main()
{

    int T;
    cin >> T;
    while(T--){
        ll n;
        cin >> n;
        if(n == 0){
            cout << 0 << endl;
            continue;
        }
        else if(n == 1){

            cout << 2 << endl;
            continue;
        }
            pair<ll, ll> ans = fib(n+1);
            cout << mod(ans.first + ans.second) << endl;
    }
    return 0;
}