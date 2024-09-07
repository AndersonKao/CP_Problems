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

int a[200000];

int main(){
	yccc;		
	int n;
	cin >> n;
	int M = 0;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		M = max(a[i], M);
	}
	ll ans = 0;
	for(int b = 0; (1 << b) <= M; b++){
		ll cnt = 0;
		int cur = 0;
		for(int i = 0; i < n; i++){
			if(a[i] & (1 << b)){
				cur++;
			}
			if(i > 0 && (cur & 1)){
				cnt++;
			}
		}
		for(int i = 0; i < n-1; i++){
			ans += (1 << b) * cnt;
			int p = (a[i] >> b) & (1 );
			int q = (a[i+1] >> b)& (1);
			if(p == 0 && q == 0){
				cnt = cnt;
			}
			if(p == 0 && q == 1){
				cnt = cnt - 1;
			}
			if(p == 1 && q == 0){
				cnt = cnt - 1;
				cnt = (n - i - 1) - 1 - cnt;
			}
			if(p == 1 && q == 1){
				cnt = (n - i - 1) - 1 - cnt;
			}
		}
	}
	cout << ans << endl;
	return 0;
}

