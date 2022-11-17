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
const int MAX = 3000005;
const int mod = 998244353;

ll fact[MAX], tcaf[MAX]; // tcaf[a] = fact[a]^-1 mod n

ll binpow(ll x, ll d, ll m = mod) {
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

// O(log(min(a, b)))
// returns gcd and one solution to a*x+b*y=gcd(a,b)
ll ext_gcd(ll a, ll b, ll& x, ll& y) {
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

//! compute the coefficients modulo some prime number p.
/*
|   p = a * 2^b + 1   | a   | b   | prime factor |
|:-------------------:| --- | --- |:------------:|
|          3          | 1   | 1   |      2       |
|          5          | 1   | 2   |      2       |
|         17          | 1   | 4   |      3       |
|         97          | 3   | 5   |      5       |
|         193         | 3   | 6   |      5       |
|         257         | 1   | 8   |      3       |
|        7681         | 15  | 9   |      17      |
|        12289        | 3   | 12  |      11      |
|        40961        | 5   | 13  |      3       |
|        65537        | 1   | 16  |      3       |
|       786433        | 3   | 18  |      10      |
|       5767169       | 11  | 19  |      3       |
|       7340033       | 7   | 20  |      3       |
|      23068673       | 11  | 21  |      3       |
|      104857601      | 25  | 22  |      3       |
|      167772161      | 5   | 25  |      3       |
|      469762049      | 7   | 26  |      3       |
|      998244353      | 119 | 23  |      3       |
|     1004535809      | 479 | 21  |      3       |
|     2013265921      | 15  | 27  |      3       |
|     2281701377      | 17  | 27  |      3       |
|     3221225473      | 3   | 30  |      5       |
|     75161927681     | 35  | 31  |      3       |
|     77309411329     | 9   | 33  |      7       |
|    206158430209     | 3   | 36  |      22      |
|    2061584302081    | 15  | 37  |      7       |
|    2748779069441    | 5   | 39  |      3       |
|    6597069766657    | 3   | 41  |      5       |
|   39582418599937    | 9   | 42  |      5       |
|   79164837199873    | 9   | 43  |      5       |
|   263882790666241   | 15  | 44  |      7       |
|  1231453023109121   | 35  | 45  |      3       |
|  1337006139375617   | 19  | 46  |      3       |
|  3799912185593857   | 27  | 47  |      5       |
|  4222124650659841   | 15  | 48  |      19      |
|  7881299347898369   | 7   | 50  |      6       |
|  31525197391593473  | 7   | 52  |      3       |
| 180143985094819841  | 5   | 55  |      6       |
| 1945555039024054273 | 27  | 56  |      5       |
| 4179340454199820289 | 29  | 57  |      3       |

*/

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
// const_a, root_pw, prime_factor need to adjust by prime number
const ll const_a = 119;
const ll root_pw = 1 << 23;
const ll prime_factor = 3; // or call generator(mod).
const ll root = binpow(prime_factor, const_a);
const ll root_1 = inverse(root, mod);

void fft(vector<ll> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        ll wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i+j], v = (1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        ll n_1 = inverse(n, mod);
        for (ll & x : a)
            x = (1LL * x * n_1 % mod);
    }
}

vec<ll> multiply(vec<ll> const& a, vec<ll> const& b) {
    vec<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n, 0);
    fb.resize(n, 0);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = (1LL * fa[i] * fb[i] % mod);
    fft(fa, true);

    vec<ll> result(n);
    for (int i = 0; i < n; i++)
        result[i] = fa[i];
    
    //* if multiplying two number
    /*
    int carry = 0;
    for (int i = 0; i < n; i++) {
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }
    */
        
    return result;
}


int main(){
	yccc;		
	init(200000);
	int n;
	cin >> n;
	vec<p<int>> events;
	for(int i = 0 ; i < n; i++){
		int l, r;
		cin >> l >> r;
		events.eb(l, 0), events.eb(r, 1);
	}
	sort(al(events));
	int cur = 0;
	vec<int> cnt(n, 0);
	for(p<int> &e: events){
		if(e.S == 0){
			cnt[cur]++;
			cur++;
		}
		else{
			cur--;
		}
	}

	vec<ll> fa(n, 0), fb(n, 0);
	for(int i = 0; i < n; i++){
		fa[i] = (ll)(1LL * cnt[i] * fact[i]) % mod;
	}
	for(int i = 0; i < n; i++){
		fb[i] = tcaf[n - 1 - i];	
	}

	vec<ll> fk = multiply(fa, fb);
	for(int k = 0; k <n ; k++){
		cout << (fk[n + k - 1] * tcaf[k]) % mod << (k == n-1?"\n":" ");
	}

	return 0;
}

