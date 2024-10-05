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

int n;
vec<ll> seq;
ll ans = LLONG_MAX;
void dfs(int d, ll A, ll B){
	if(d == n){
		ans = min(ans, max(A, B));
		return;
	}
	dfs(d+1, A + seq[d], B);
	dfs(d+1, A, B + seq[d]);
}

int main(){
	yccc;		
	cin >> n;
	seq.resize(n);
	for(int i = 0; i < n; i++){
		cin >> seq[i];
	}
	sort(al(seq));
	dfs(0, 0, 0);
	cout << ans << endl;

	return 0;
}

