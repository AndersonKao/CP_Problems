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

int main(){
	yccc;		

	long long n;
	cin >> n;
	int sz = 1;
	while((1LL << sz) <= 2*n){
		sz++;
	}
	vector<long long> dp(sz, 0);
	dp[0] = 1;

	for(int i = 1; i < sz; i++){
		dp[i] = dp[i-1] * 2 + (1LL << i);
		//cout << i << ": " << dp[i] << endl;
	}
	long long one_cnt = 0;
	for(int i = 0; (1LL << i) <= n; i++){
		if(n & (1LL << i)){
			one_cnt++;
		}
	}
	long long res = one_cnt;
	for(int i = 0; (1LL << i) <= n; i++){
		if(n & (1LL << i)){
			one_cnt--;
			res += one_cnt * (1LL << i);
			if(i > 0){
				res += dp[i-1];
			}
		}
	}

	cout << res << endl;
	
	return 0;
}

