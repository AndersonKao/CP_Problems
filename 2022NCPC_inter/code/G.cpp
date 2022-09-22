#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define F first
#define S second

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using p = pair<T, T>;

ll avail = 0, total = 0;

int now[6] = {1};

const ll MOD = 998244353;
ll binpow(ll a, ll b) {
	ll ret = 1;

	if (b < 0) b += MOD - 1;

	do {
		if (b % 2) (ret *= a) %= MOD;
		(a *= a) %= MOD;
	} while (b >>= 1);

	return ret;
}

ll fact[1000], tcaf[1000];
void init(int n) {
	fact[0] = 1;
	for (int i = 1; i <= n; i++) {
		fact[i] = i * fact[i - 1] % MOD;;
	}
	for (int i = n; i >= 0; --i) {
		tcaf[i] = binpow(fact[i], -1);
	}
}

ll nCr(int n, int r) {
	if (r < 0 or r > n) return 0;
	return fact[n] * tcaf[r] % MOD * tcaf[n-r] % MOD;
}

vec<int> cont(11), now_count(11);
void recur(int i) {
	if (i == 6) {
		ll sum = 0;

		fill(now_count.begin(), now_count.end(), 0);
		for (int k = 1; k <= 5; k++) {
			sum += now[k];
			now_count[now[k]]++;
		}
		
		ll ways = 1;
		
		if (now_count[0] != 0) return;
		for (int k = 1; k <= 10; k++) {
			if (cont[k] < now_count[k])
				return;

			ways *= nCr(cont[k], now_count[k]);
		}
/*
		for (int k = 1; k <= 10; k++)
			cout << cont[k] << ' ';
		cout << endl;
		for (int k = 1; k <= 10; k++)
			cout << now_count[k] << ' ' ;
		cout << endl;

		cout << "---> " << ways << endl << endl;
*/
		if (sum <= 21) {
			total += ways;
			avail += ways;
		} else {
			total += ways;
		}
		// do.
		return;
	}

	for (int k = now[i-1]; k <= 10; k++) {
		now[i] = k;
		recur(i+1);
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

	for (int i = 0; i < 52; i++) {
		int num;
		cin >> num;

		cont[num]++;
	}

	init(100);

	recur(1);
/*
	for (int i = 1; i <= 10; i++)
		cout << cont[i] << ' ';
	cout << endl;
	cout << avail << ' ' << total << endl;
*/
	if (avail == total) {
		cout << "QAQ";
	} else {
		ll GCD = __gcd(avail, total);
		cout << (total-avail) / GCD << '/' << total / GCD;
	}
}
