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
		ll x1, x2, x3, x4;
		ll y1, y2, y3, y4;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

		ll val1 = (x4 - x3) * (y1 - y3) - (x1 - x3) * (y4 - y3);
		ll val2 = (x4 - x3) * (y2 - y3) - (x2 - x3) * (y4 - y3);
		ll val3 = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
		ll val4 = (x2 - x1) * (y4 - y1) - (x4 - x1) * (y2 - y1);

		if(val1 == 0 || val2 == 0 || val3 == 0 || val4 == 0 || (val1 != val2) && (val3 != val4)){
			cout << "YES";
		}
		else{
			cout << "NO";
		}
		cout << endl;
	}
	return 0;
}
