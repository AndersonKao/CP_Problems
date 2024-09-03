#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, treeorder_statistics_node_update>;
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

const int MAX = 3000005;
const ll mod = 1000000007LL;

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
const int maxn = 1000000;
int cnt[26];

int main(){
	yccc;		
	init(maxn);
	string str;
	cin >> str;
	for(size_t i = 0; i < str.length(); i++){
		cnt[str[i] - 'a']++;
	}
	size_t n = str.length();
	ll ans = fact[n];
	for(size_t ch = 0; ch < 26; ch++){
		if(cnt[ch] > 0) ans = (ans * tcaf[cnt[ch]]) % mod;
	}
	cout << ans << endl;

	return 0;
}

