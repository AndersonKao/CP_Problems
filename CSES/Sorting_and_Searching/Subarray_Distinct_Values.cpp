
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(), a.end()
#define eb emplace_back
#define F first
#define S second

int last[200005];

int main() {
	yccc;
	int n, k;
	cin >> n >> k;
	vec<int> V(n);
	for(int i = 0; i < n; i++){
		cin >> V[i];
	}
	vec<int> Va = V;
	sort(al(Va));
	auto it = unique(al(Va));
	for(int i = 0; i < n; i++){
		last[i] = -1;
		V[i] = (lower_bound(Va.begin(), it, V[i]) - Va.begin()) + 1;
		//cout << V[i] << (i == n-1 ? '\n' : ' ');
	}
	int p = 0, q = 0;
	ll ans = 1;
	int cur = 1;
	last[V[q]] = 0;
	while(++q < n){
		//cout << p << ", " << q << ", " << cur << endl;
		if(last[V[q]] == -1){
			cur++;
		}
		last[V[q]] = q;
		while(cur > k){
			if(last[V[p]] == p){
				//cout << "out " << V[p] << " at " << p <<endl;
				cur--;
				last[V[p]] = -1;
			}
			p++;
		}
		ans += q - p + 1;
		//cout << "incre: " << q - p + 1 << endl;
	}
	cout << ans << endl;
	return 0;
}
