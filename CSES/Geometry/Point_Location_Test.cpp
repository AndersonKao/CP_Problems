
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(), a.end()
#define eb emplace_back
#define F first
#define S second

int main() {
	yccc;
	int t;
	cin >> t;
	while(t--){
		ll x1, x2, x3;
		ll y1, y2, y3;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

		ll val = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);

		if(val > 0){
			cout << "LEFT";
		}
		else if(val == 0){
			cout << "TOUCH";
		}
		else{
			cout << "RIGHT";
		}
		cout << endl;
	}
	return 0;
}
