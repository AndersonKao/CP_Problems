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

void solve(int ct){
	int n;
	cin >> n;
	double ansmax = 1e9, ansmin = 0.0;
	for(int i = 1; i <=n ; i++){
		double s, t;
		cin >> s >> t;
		double maxrate = ((double)t / i);
		double minrate = ((double)s / i);
		ansmax = min(ansmax, maxrate);
		ansmin = max(ansmin, minrate);
	}
	cout << "Case #" << ct << ": ";
	if(ansmin > ansmax){
		cout << -1 << endl;
	}	
	else{
		cout << 1 / ansmax << endl;
	}
	
}

int main(){
	yccc;		
	int t;
	cin >> t;
	cout << fixed << setprecision(7);
	for(int ct = 1; ct <= t; ct++){
		solve(ct);
	}
	return 0;
}
