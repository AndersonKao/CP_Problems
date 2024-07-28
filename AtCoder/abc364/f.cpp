
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
	int n, q;
	cin >> n >> q;
	ll ans = 0;
	vec<tuple<ll, int, int>> V;
	for(int i = 0; i < q; i++){
		int L, R; ll C;
		cin >> L >> R >> C;
		V.eb(C, L, R);
	}
	sort(al(V));
	set<int> conn;
	for(int i = 2; i <= n; i++){
		conn.emplace(i);
	}
	for(int i = 0; i < q; i++){
		int L, R; ll C;
		tie(C, L, R) = V[i];
		ans += C;
		auto it = conn.upper_bound(L);
		while(it != conn.end() && *it <= R){
			ans += C;
			auto to_remove = it;
			it++;
			conn.erase(to_remove);
		}
	}
	if(conn.size() != 0){
		cout << -1 << endl;
	}
	else{
		cout << ans << endl;
	}
	return 0;
}
