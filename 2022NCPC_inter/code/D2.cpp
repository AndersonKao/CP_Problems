#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
// O(log(min(a, b)))
// returns gcd and one solution to a*x+b*y=gcd(a,b)
ll ext_gcd(ll a, ll b, ll& x, ll & y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
        ll d = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
ll a[3], m[3], t[3];
int main(){
        yccc;
        int T;
        cin >> T;
        while(T--){
                ll M = 1;
                ll X = 0;
                REP(i, 3){
                        cin >> m[i] >> a[i];
                        M *= m[i];
                }
                REP(i, 3){
                        ll x, y;
                        ll g = ext_gcd(M / m[i], m[i], x, y);
                        t[i] = x / g;
                        X += a[i] * t[i] * (M / m[i]);
                }
                X = ((X % M) + M) % M;

                cout << X << endl;
        }
        return 0;
}
