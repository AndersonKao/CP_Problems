#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;

#define eb emplace_back
#define F first
#define S second
#define mp make_pair
using pii = pair<int, int>;
auto cmp = [](const pii&a, const pii&b){
	if(a.F != b.F)
		return a.F < b.F; // pos
	else{
		return a.S > b.S; // time
	}
};
using ordered_set = tree<
pair<int, int>,
null_type,
decltype(cmp),
rb_tree_tag,
tree_order_statistics_node_update>;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using p = pair<T, T>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> V(m);
	vector<int> ans(m, 0);
	for(int&v: V)
		cin >>v;
	ordered_set mS(cmp);
	for(int i = V.size() -1; i>= 0; i--){
		pii cur = mp(V[i], i);
		auto it = mS.lower_bound(mp(V[i], n));
		int l = min((int)mS.order_of_key(*it), V[i]-1);
		ans[i] = mS.order_of_key(cur) - l;
		mS.insert(cur);
	}
	for(int i = 0; i < m; i++){
		cout << min(ans[i]+1, n - V[i]+1) << (i == m-1 ? "\n" : " ");
	}
}
