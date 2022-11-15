#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define endl '\n'
#define yccc ios_base::sync_with_stdio(false);
#define F first
#define S second
#define eb emplace_back
#define al(a) a.begin(),a.end()
const int maxn = 10000;
//int _list[maxn][maxn];
int main() {
	yccc;

	int t;
	cin >> t;
	vec<vec<int>> _list(maxn, vec<int>(maxn, 0));
	while (t--) {
		ll n, k;
		cin >> n >> k;
		for (int i = 0; i < n; i++) {
			fill(_list[i], _list[i] + i+1, 0);
		}

		_list[0][0] = k;
		for (int i = 1; i < n; i++) {
			for (int k = 0; k < i; k++) {
				_list[i][k] += ((_list[i-1][k] + 1) >> 1);
				_list[i][k+1] += (_list[i-1][k] >> 1);
			}
		}

		int i = 0, K = 0;
		while (i != n-1) {
			if (_list[i][K] & 1) {
				i++;
			} else {
				i++, K++;
			}
		}

		cout << K << endl;
	}
}
