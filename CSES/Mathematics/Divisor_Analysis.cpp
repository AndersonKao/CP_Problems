#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
*/
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define ln '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int MAX = 300005;
const ll mod = 1000000007;

ll fact[MAX], tcaf[MAX]; // tcaf[a] = fact[a]^-1 mod n

ll binpow(ll x, ll d, ll  = mod) {
    if (d < 0) d += mod - 1;

    ll y = 1;
    do{
        if (d & 1) (y *= x) %= mod;
        (x *= x) %= mod;
    } while (d >>= 1);

    return y;
}

// Call this first.
void init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = i * fact[i - 1] % mod;
    for (int i = n; i >= 0; --i)
        tcaf[i] = binpow(fact[i], -1);
}

// Invoke nCr via this.
ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * tcaf[r] % mod * tcaf[n - r] % mod;
}
int main(){
	yccc;		
	int n;
	cin >> n;
	ll x[MAX], k[MAX];
	for(int i = 0; i < n; i++){
		cin >> x[i] >> k[i];
	}
	ll ndiv = 1;
	ll sumdiv = 0;
	ll prodiv = 1;
	for(int i = 0; i < n; i++){
		ndiv *= (k[i] + 1);
		ndiv %= mod;
	}
	for(int i = 0; i < n; i++){
		// sumdiv (x^k+x^(k-1)+...+x+1) = (x^(k+1)-1) / (x-1)
		ll s = ((binpow(x[i], k[i]) - 1) * binpow(x[i] - 1, -1)) % mod;
		s = (s * ndiv) % mod;
		s = (s * binpow(k[i]+1, -1)) % mod;
		sumdiv = (sumdiv + s) % mod;

		// prodiv x_i^{ (0+1+2+...+k) * #num / (k+1) }
		ll q = binpow(x[i], -1);
		ll arithemic_sum = ((k[i] + 1) * k[i] / 2) % q;
		ll num_of_x = arithemic_sum * (ndiv * binpow(k[i] + 1, -1, q) % q) % q;
		ll p = binpow(x[i], num_of_x)  % mod;
		prodiv = (prodiv * p) % mod;
	}
	cout << ndiv << " " << sumdiv << " " << prodiv << endl;

	return 0;
}

