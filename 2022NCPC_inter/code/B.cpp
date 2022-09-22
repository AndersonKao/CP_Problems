
#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define F first
#define S second

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using p = pair<T, T>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

	string str;
	cin >> str;

	vec<int> _list;
	
	int now = 0;
	for (int i = str.size()-1; i >= 0; i--) {
		if (str[i] == 'M') {
			_list.eb(now);
		} else {
			now += (str[i] == '+' ? 1 : -1);
		}
	}

	sort(_list.begin(), _list.end());

	ll ans = 0;
	for (int i = 0; i < _list.size() / 2; i++)
		ans -= _list[i];
	for (int i = _list.size() / 2; i < _list.size(); i++)
		ans += _list[i];
/*
	for (int i = 0; i < _list.size(); i++)
		cout << _list[i] << ' ';
	cout << endl;
	*/

	cout << ans;
}
