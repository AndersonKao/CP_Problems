#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, treeorder_statistics_node_update>;
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
ll cnt[1000006];
ll ncnt[1000006];
int n, m;
ll psum[200001];
ll d[200001];

ll dis(int i, int j){
	if(i < j){
		return psum[j-1] - psum[i-1];
	}
	return psum[n] - psum[i-1] + psum[i-1];
}

int main(){
	yccc;		
	cin >> n >> m;
	ll cyclelen = 0;
	for(int i = 1; i <= n; i++){
		cin >> d[i];
		cyclelen+=d[i];
	}
	
	ll ans = 0;
	ll prefix = 0;
	for(int i = 1; i < n; i++){
//		cout << "from " << i + 1 << endl;
		prefix += d[i];
		ll k = (m - (cyclelen - prefix) % m) % m;
		ans += cnt[k];
		cnt[prefix % m]++;

		if((cyclelen - prefix) % m == 0){
			ans++;
		}
	}

	ll rem = 0;

	for(int i = 1; i < n; i++){
//		cout << "from " << i << endl;
		ans += cnt[rem];
		rem = (rem + d[i]) % m;
		cnt[rem]--;
	}

	cout << ans << endl;


	return 0;
}

