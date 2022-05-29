// AC 2022-05-29 02:30:30
#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define al(x) x.begin(), x.end()
using ll = long long;
template<typename T>
using vec = vector<T>;
using pii = pair<int, int>;

#define debug(x) cout << #x << ": " << x << endl;

struct Fenwick{
	int n;
	vec<ll> seq;
	Fenwick(int N){
		n = N;
		seq.resize(n + 1, 0);
	}
	void modify(int pos, int val){
		int res = pos;
		while(res <= n){
			seq[res] += val;
			res += (res & -res);
		}
	}
	ll query(int pos){
		int res = pos;
		ll ans = 0;
		while(res >= 1){
			ans += seq[res];
			res -= (res & -res);
		}
		return ans;
	}
};

int main(){
	int N, M, Q;
	cin.tie(0), ios_base::sync_with_stdio(false);
	cin >> N >> M >> Q;
	vec<vec<pii>> queries(M+1); // t, r 
	vec<vec<pii>> op1(M+2); // t, x;
	vec<vec<pii>> op2(N+1); // t, x;
	vec<pair<int, ll>> ANS; // t, ans;
	queries.resize(M);
	for(int t = 1; t <= Q; t++){
		int op;
		cin >> op;
		if(op == 1){
			int l, r, x;
			cin >> l >> r >> x;
			op1[l].eb(t, x);
			op1[r + 1].eb(t, -x);
		}
		else if(op == 2){
			int r, x;
			cin >> r >> x;
			op2[r].eb(t, x);
		}
		else if(op == 3){
			int r, c;
			cin >> r >> c;
			queries[c].eb(t, r);	
		}
	}
	for(vec<pii>& v: op2){
		v.eb(0, 0);
		sort(al(v));
	}
	Fenwick mT(Q);
	for(int c = 1; c <= M; c++){
		for(auto [t, x]: op1[c]){
			mT.modify(t, x);	
		}		
		for(auto [tr, r]: queries[c]){
			vec<pii>& V = op2[r];
			auto it = lower_bound(al(V), pair(tr, 0));
			it--;
			int tl = it->F;
			ll val = it->S;	
			val += (mT.query(tr) - mT.query(tl));
			ANS.eb(tr, val);	
		}
	}
	sort(al(ANS));
	for(auto [t, ans]: ANS){
		cout << ans << endl;
	}
	return 0;
}
