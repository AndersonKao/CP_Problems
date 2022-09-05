#include <bits/stdc++.h>
using namespace std;
const int MAX = 3000005;
const ll MOD = 998244353;

ll fact[MAX], tcaf[MAX];

ll deg(ll x, ll d) {
    if (d < 0) d += MOD - 1;
    ll y = 1;
    while (d) {
        if (d & 1) (y *= x) %= MOD;
        d /= 2;
        (x *= x) %= MOD;
    }
    return y;
}

// Call this first.
void init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = i * fact[i - 1] % MOD;
    for (int i = n; i >= 0; --i)
        tcaf[i] = deg(fact[i], -1);
}

// Invoke nCr via this.
ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * tcaf[r] % MOD * tcaf[n - r] % MOD;
}

int main(){
	init(MAXN);
	int T;
	cin >> T;

	while(T--){
		int n, k;
	}
	return 0;
}
