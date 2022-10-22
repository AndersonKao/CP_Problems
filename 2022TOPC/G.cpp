#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template <typename T> using vec = vector<T>;
template <typename T> using deq = deque<T>;
template <typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0);
#define endl '\n'
#define eb emplace_back
#define F first
#define S second
#define al(a) a.begin(),a.end()

int main() {
	yccc;
	
	int n, m;
	cin >> n >> m;

	vec<p<int>> _list(n);
	for (auto &i : _list)
		cin >> i.F;
	for (auto &i : _list)
		cin >> i.S;

	auto cmp = [](p<int>& a, p<int>& b) {
		return a.F < b.F;
	};
	
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			ll last = m - min(min(k, n-k), min(i, n-i)) - ((k - i + n) % n), sum = 0;

//			cout << i << ' ' << k << ' ' << last << ' ';

			priority_queue<p<int>, vec<p<int>>, decltype(cmp)> pq(cmp);
			for (int z = i;; z = (z+1) % n) {
				pq.emplace(_list[z].F, z);

				if (z == k) break;
			}

			while (last > 0) {
				auto now = pq.top();
				pq.pop();
				
				if (now.F < 0) break;

				sum += now.F;

				pq.emplace(now.F - _list[now.S].S, now.S);
				last--;
			}

//			cout << sum << endl;

			ans = max(ans, sum);
		}
	}

	cout << ans << endl;
}
