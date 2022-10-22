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

int up(int a, int n) {
	return (a + n) % n;
}

int main() {
	yccc;

	int n, idx = -1;
	cin >> n;

	bool good = true;

	vec<int> _list(n);
	vec<vec<int>> node(n);

	vec<p<int>> ans;
	set<int> prv, now;
	for (int i = 0; i < n; i++) {
		cin >> _list[i];
		if (_list[i] == 0) {
			if (idx != -1)
				good = false;
			idx = i;
		}

		if (_list[i] == 0) {
			prv.emplace(i);
		} else if (_list[i] == 1) {
			now.emplace(i);
		}

		node[_list[i]].eb(i);
	}
	
	if (!good or idx == -1) {
		cout << -1;
		return 0;
	}

	for (int i = 0; i < n; i++) {
		if (_list[i] == 1)
			ans.eb(idx, i);
	}

	for (int i = 2; i < n; i++) {
		// node[i]
		for (auto now_idx : node[i]) {
			if (now.empty()) {
				cout << -1 << endl;
				return 0;
			}

			bool lGood = true, rGood = true;
			auto left = now.lower_bound(now_idx), right = now.lower_bound(now_idx);
			
			if (left == now.begin())
				left = prev(now.end());
			else left = prev(left);

			if (right == now.end())
				right = now.begin();
			
			auto bLeft = prv.lower_bound(now_idx), bRight = prv.lower_bound(now_idx);	
			if (bLeft == prv.begin())
				bLeft = prev(prv.end());
			else bLeft = prev(bLeft);

			if (bRight == prv.end())
				bRight = prv.begin();

			//cout << now_idx << ' ' << *left << ' ' << *right << ' ' << *bLeft << ' ' << *bRight << endl;
			//cout << now.size() << endl;

			if (up(now_idx - *left, n) > up(now_idx - *bLeft, n)) lGood = false;
			if (up(*right - now_idx, n) > up(*bRight - now_idx, n)) rGood = false;

			if (!lGood and !rGood) {
				cout << -1 << endl;
				return 0;
			}

			if (lGood) {
				ans.eb(now_idx, *left);
			} else {
				ans.eb(now_idx, *right);
			}
		}
			
		for (auto z : now)
			prv.emplace(z);

		now.clear();
		for (auto now_idx : node[i]) {
			now.emplace(now_idx);
		}
	}

	// --------------
	for (auto &i : ans)
		cout << i.F+1 << ' ' << i.S+1 << endl;
}
