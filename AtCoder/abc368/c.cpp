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

int main(){
	yccc;		
	int n = 0;
	cin >> n;
	vec<int> a(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];
	ll ans = 0;
	for(int i = 0; i < n; i++){
		ans += (a[i] / 5) * 3LL;
		a[i] %= 5;
		while(a[i] > 0){
			ans++;
			if(ans % 3 == 0){
				a[i] -= 3;
			}
			else{
				a[i] -= 1;
			}
		}
//		debug(ans);
	}
	cout << ans << endl;
	return 0;
}

