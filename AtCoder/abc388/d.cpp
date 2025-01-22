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
	vector<int> C(n);
	for(int &a: C){
		cin >> a;
	}
	vector<int> events(n, 0); // hom many end here;
	int addstone = 0;
	vector<int> ans(n, 0);
	for(int i = 0; i < n; i++){
		int curstone = C[i] + addstone;
		if(curstone < n - i - 1){
			events[i + curstone]++;
		}
		else{
			ans[i] = curstone - (n - i - 1);
		}
		addstone++;
		addstone -= events[i];
	}
	for(int i = 0; i < n; i++){
		cout << ans[i] << (i == n - 1 ? '\n' : ' ');
	}

	return 0;
}

