#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(ll i = 0; i < (ll)n; i++)
#define REP1(i, n) for(ll i = 1; i <= (ll)n; i++)
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
using pii = pair<ll, ll>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const ll MAX = 3000005;
const ll mod = 998244353LL;

ll fact[MAX], tcaf[MAX]; // tcaf[a] = fact[a]^-1 mod n

ll binpow(ll x, long long d, ll m = mod) {
    if (d < 0) d += m - 1;

    ll y = 1;
    do{
        if (d & 1) (y *= x) %= m ;
        (x *= x) %= m ;
    } while (d >>= 1);

    return y;
}

// Call this first.
void init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = (ll)(1LL * i * fact[i - 1] % mod);
    for (int i = n; i >= 0; --i)
        tcaf[i] = binpow(fact[i], -1);
}

// Invoke nCr via this.
ll nCr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * tcaf[r] % mod * tcaf[n - r] % mod ;
}

// O(log(min(a, b)))
// returns gcd and one solution to a*x+b*y=gcd(a,b)
ll ext_gcd(ll a, ll b, ll & x, ll & y) {
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


ll generator (ll p = mod) {
    vector<ll> fact;
    ll phi = p-1,  n = phi;
    for (ll i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (ll res=2; res<=p; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= binpow (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}

//* compute the coefficients modulo some prime number p.

ll inverse(ll a, ll m){ // returns a^-1 mod m, 0 if not found
    ll x, y;
    ll g = ext_gcd(a, m, x, y);
    if (g != 1) {
        return 0;
    }
    else {
        x = (x % m + m) % m;
        return x;
    }

}
// p = c * 2^k + 1  always exits the 2^k-th root
// g ^ c is such a 2^k-th root of unity, where g is primitive_root of p 
const ll proot = generator(mod);
const ll const_c = 
const ll root = binpow(proot, 119);
const ll root_1 = inverse(root, mod);
const ll root_pw = 1 << 23;

void fft(vector<ll> & a, bool invert) {
    ll n = a.size();

    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (ll len = 2; len <= n; len <<= 1) {
        ll wlen = invert ? root_1 : root;
        for (ll i = len; i < root_pw; i <<= 1)
            wlen = (ll)(1LL * wlen * wlen % mod);

        for (ll i = 0; i < n; i += len) {
            ll w = 1;
            for (ll j = 0; j < len / 2; j++) {
                ll u = a[i+j], v = (ll)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (ll)(1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        ll n_1 = inverse(n, mod);
        for (ll& x : a)
            x = (ll)(1LL * x * n_1 % mod);
    }
}

vec<ll> multiply(vec<ll> const& a, vec<ll> const& b) {
    vec<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    ll n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n, 0);
    fb.resize(n, 0);

    fft(fa, false);
    fft(fb, false);
    for (ll i = 0; i < n; i++)
        fa[i] = (ll)(1LL * fa[i] * fb[i] % mod);
    fft(fa, true);

    vec<ll> result(n);
    for (ll i = 0; i < n; i++)
        result[i] = fa[i];
    
    //* if multiplying two number
    /*
    ll carry = 0;
    for (ll i = 0; i < n; i++) {
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }
    */
        
    return result;
}


int main(){
	yccc;		
	/*
	debug(root);
	debug(root_1);*/
	init(200000);
	ll n;
	cin >> n;
	vec<p<ll>> events;
	for(ll i = 0 ; i < n; i++){
		ll l, r;
		cin >> l >> r;
		events.eb(l, 0), events.eb(r, 1);
	}
	sort(al(events));
	ll cur = 0;
	vec<ll> cnt(n, 0);
	for(p<ll> &e: events){
		if(e.S == 0){
			cnt[cur]++;
			cur++;
		}
		else{
			cur--;
		}
	}

	/*
	for(ll i = 0; i < n; i++){
		cout << cnt[i] << (i == n-1 ? "\n" : " ");
	}*/

	/*
	for(ll i = 0; i < n; i++){
		cout << fact[i] << (i == n-1 ? "\n" : " ");
	}*/
	vec<ll> fa(n, 0), fb(n, 0);
//	cout << "fa: ";
	for(ll i = 0; i < n; i++){
		fa[i] = (ll)(1LL * cnt[i] * fact[i]) % mod;
//		cout << fa[i] << (i == n-1 ? "\n" : " ");
	}
//	cout << "fb: ";
	for(ll i = 0; i < n; i++){
		fb[i] = tcaf[n - 1 - i];	
		cout << fb[i] << (i == n-1 ? "\n" : " ");
	}
	
	vec<ll> fk = multiply(fa, fb);
	/*
	for(ll k = 0; k < fk.size(); k++){
		cout << fk[k] << (k == fk.size()-1 ? "\n" : " ");
	}*/
	for(ll k = 0; k < n ; k++){
		cout << (fk[n + k - 1] * tcaf[k]) % mod << (k == n-1?"\n":" ");
	}


	return 0;
}

