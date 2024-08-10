
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

ll table[101][101][101];
ll pre[101][101][101];

int main(){
	yccc;		
	int n, q;
	cin >> n;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			for(int k = 1; k <= n; k++){
				cin >> table[i][j][k];
			}
		}
	}

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			ll sum = 0;
			for(int k = 1; k <= n; k++){
				sum += table[i][j][k];
				pre[i][j][k] = pre[i][j-1][k] + sum;
//				debug(pre[i][j][k]);
//				debug(sum);
			}
		}
	}

	cin >> q;
	while(q--){
		int L1, R1, L2, R2, L3, R3;
		cin >> L1 >> R1 >> L2 >> R2 >> L3 >> R3;
		ll ans = 0;
		for(int i = L1; i <= R1; i++){
			ans += pre[i][R2][R3] - pre[i][L2-1][R3] - pre[i][R2][L3-1] + pre[i][L2-1][L3-1];	
//			debug(ans);
		}
		cout << ans << endl;
	}
	return 0;
}

