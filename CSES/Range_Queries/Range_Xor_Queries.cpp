
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;

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


int seq[200005 * 4];

void build(vec<int>& V, int L, int R, int id){
	if(L == R){
		seq[id] = V[L];
		return ;
	}
//	debug(L); debug(R);

	int M = (L + R) / 2;
	build(V, L, M, id * 2);
	build(V, M+1, R, id * 2 + 1);
	seq [id] = 0;
	seq[id] ^= seq[id * 2];
	seq[id] ^= seq[id * 2 + 1];
}

int query(int l, int r, int L, int R, int id){
//	debug(L); debug(R);
	if(R < l || r < L){
		return 0;
	}
	if(l <= L && R <= r){
		return seq[id];
	}
	int M = (L + R) / 2;

	int ans = 0;
	ans ^= query(l, r, L, M, id * 2);
	ans ^= query(l, r, M+1, R, id * 2 + 1);
	return ans;
}


int main() {
	yccc;
	int n, q;
	cin >> n >> q;
	vec<int> V(n+1);
	for(int i = 1; i <= n; i++){
		cin >> V[i];
	}
	build(V, 1, n, 1);

	while(q--){
		int a, b;
		cin >> a >> b;
		cout << query(a, b, 1, n, 1) << endl;
	}
	return 0;
}
