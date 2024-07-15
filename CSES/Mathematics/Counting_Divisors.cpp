
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;

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
	int n, val;
	cin >> n;
	while(n--){
		cin >> val;
		int ans = 0;
		for(int i = 1; i * i <= val; i++){
			if((val / i) * i == val){
				ans += 2;
			}
			if(i * i == val){
				ans -= 1;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
