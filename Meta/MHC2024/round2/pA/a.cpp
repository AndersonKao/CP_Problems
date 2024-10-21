#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
*/
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define ln '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
long long enu(int len, ll A, ll B,ll M){
	ll ans = 0;
	for(int base = 1; base <= 9; base++){
		ll res = 0;
		int b = base;
		for(int i = 0; i < len; i++){
			res *= 10;
			res += b;
			b++;
		}
		if(b > 9)
			return ans;
		res *= 10;
		res += b;
		for(int i = 0; i < len; i++){
			b--;
			res *= 10;
			res += b;
		}
		//debug(res);
		if(res % M == 0 && A <= res && res <= B){
			//ebug(res);
			ans++;
		}
	}
	return ans;
}
void solve(int ca){
	long long A, B, M;
	cin >> A >> B >> M;
	ll ans = 0;
	for(int i = 0; 2*i+1 <= 18; i++){
		ans += enu(i, A, B, M);		
	}

	cout << "Case #" << ca << ": " << ans << endl;
}

int main(){
	//yccc;		
	int t;
	cin >> t;
	for(int i = 1; i <= t; i++){
		solve(i);
	}
	return 0;
}

