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
	int n;
	cin >> n;
	vector<ll> A(n);
	for(ll &a: A){
		cin >> a;
	}
	int bt = 0;
	int bt2 = 0;
	ll ans = 0;
	vector<bool> used(n, false);
	for(int i = 0; i < A.size(); i++){
		while(bt < A.size() && (used[bt] || A[i]*2 > A[bt])){
			bt++;
		}
		if(bt >= A.size())
			break;
		if(used[i]){
			while(bt2 < A.size() && (used[bt2] || A[i]*2 > A[bt2])){
				bt2++;
			}
			if(bt2 < A.size()){
				used[bt] = used[bt2] = true;
				ans++;
				bt2++;
				bt++;
			}
		}
		else{
			used[i] = used[bt] = true;
			ans++;
			bt++;
		}
	}
  



	cout << ans << endl;
	return 0;
}

	
