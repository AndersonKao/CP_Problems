#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
int modn[201][10];
int main() {
	int n, z;
	cin >> n >> z;

	vec<int> _list(n);
	for (auto &i : _list)
		cin >> i;
	
//	vec<vec<int>> modn(z, vec<int>(10));
	for (int i = 0; i < z; i++) {
		for (int k = 0; k < 10; k++) {
			modn[i][k] = (i * 10 + k) % z;
		}
	}

	ll MASK = (1<<n) - 1;
	vec<vec<ll>> dp(1<<n, vec<ll>(z));
	for (int i = 0; i < n; i++) {
		dp[1<<i][_list[i] % z] = _list[i];
	}

	for (int i = 0; i < (1<<n); i++) {
		for (int k = 0; k < z; k++) {
			if (dp[i][k] != 0) {
				ll valid = ~i & MASK, next;

				for (; valid; valid -= next) {
					next = valid & (~valid+1);
					int idx = __lg(next);

					ll mod = modn[k][_list[idx]];
					ll val = dp[i][k] * 10 + _list[idx];

					dp[i | next][mod] = max(dp[i | next][mod], val);
				}
			}
		}
	}

	for (int i = z-1; i >= 0; i--)
		if (dp[(1<<n)-1][i] != 0) {
			cout << dp[(1<<n)-1][i];
			return 0;
		}
}
