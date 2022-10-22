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

struct city {
	string name;
	ll a, b, c, d, e;
	int count;
	double val;

	city() { count = 0; }
};

int main() {
	yccc;	

	int n;
	cin >> n;

	vec<city> _list(6);
	for (auto &i : _list) {
		cin >> i.name >> i.a >> i.b >> i.c >> i.d >> i.e;
	}

	for (int i = 0; i < 6; i++) {
		_list[i].val = 0.56 * _list[i].d + 0.24 * _list[i].c + 0.14 * _list[i].b + 0.06 * _list[i].a + 0.3 * _list[i].e;
	}

	auto cmp = [] (city& a, city& b) {
		return a.val > b.val;
	};

	sort(al(_list), cmp);

	int idx = 0;
	for (int i = 0; i < n; i++) {
		_list[idx].count++;

		(idx += 1) %= 6;
	}

	for (int i = 0; i < n; i++) {
		if (_list[i].name == "Taiwan") {
			cout << _list[i].count << endl;
			return 0;
		}
	}
}
