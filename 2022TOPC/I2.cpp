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
const int mod = 7340033;

int fact[MAX], tcaf[MAX]; // tcaf[a] = fact[a]^-1 mod n

int binpow(int x, int d, int m = mod) {
    if (d < 0) d += m - 1;

    int y = 1;
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
        fact[i] = (int)(1LL * i * fact[i - 1] % mod);
    for (int i = n; i >= 0; --i)
        tcaf[i] = binpow(fact[i], -1);
}

// Invoke nCr via this.
int nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * tcaf[r] % mod * tcaf[n - r] % mod ;
}

// O(log(min(a, b)))
// returns gcd and one solution to a*x+b*y=gcd(a,b)
int ext_gcd(int a, int b, int & x, int & y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}


int generator (int p = mod) {
    vector<int> fact;
    int phi = p-1,  n = phi;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (int res=2; res<=p; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= binpow (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}

//* compute the coefficients modulo some prime number p.

int inverse(int a, int m){ // returns a^-1 mod m, 0 if not found
    int x, y;
    int g = ext_gcd(a, m, x, y);
    if (g != 1) {
        return 0;
    }
    else {
        x = (x % m + m) % m;
        return x;
    }

}

const int root = 5;
const int root_1 = inverse(5, mod);
const int root_pw = 1 << 20;

void fft(vector<int> & a, bool invert) {
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
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        int n_1 = inverse(n, mod);
        for (int& x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}

vec<int> multiply(vec<int> const& a, vec<int> const& b) {
    vec<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n, 0);
    fb.resize(n, 0);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = (int)(1LL * fa[i] * fb[i] % mod);
    fft(fa, true);

    vec<int> result(n);
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
	debug(root);
	debug(root_1);
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

	for(int i = 0; i < n; i++){
		cout << cnt[i] << (i == n-1 ? "\n" : " ");
	}

	for(int i = 0; i < n; i++){
		cout << fact[i] << (i == n-1 ? "\n" : " ");
	}
	vec<int> fa(n, 0), fb(n, 0);
	cout << "fa: ";
	for(int i = 0; i < n; i++){
		fa[i] = (int)(1LL * cnt[i] * fact[i]) % mod;
		cout << fa[i] << (i == n-1 ? "\n" : " ");
	}
	cout << "fb: ";
	for(int i = 0; i < n; i++){
		fb[i] = i == 0 ? 1 : tcaf[n - 1 - i];	
		cout << fb[i] << (i == n-1 ? "\n" : " ");
	}
	vec<int> fk = multiply(fa, fb);
	for(int k = 0; k < fk.size(); k++){
		cout << fk[k] << (k == fk.size()-1 ? "\n" : " ");
	}
	for(int k = 0; k <n ; k++){
		cout << (fk[n + k - 1] * tcaf[k]) % mod << (k == n-1?"\n":" ");
	}

	return 0;
}

