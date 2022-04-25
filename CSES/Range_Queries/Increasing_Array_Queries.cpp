#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define al(a) a.begin(), a.end()
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define eb emplace_back
#define LC(x) (2 * x + 1)
#define RC(x) (2 * x + 2)

template<typename T>
using vec = vector<T>;
using pii = pair<int, int>;
using ll = long long;
vec<tuple<int, int, int>> queries;
vec<int> seq;
auto piicmp = [](const tuple<int, int, int> &a, const tuple<int,int,int> &b){
	return get<0>(a) > get<0>(b);
};

struct segT{
	vec<ll> seq, lz;
	int n;
	void Build(int n){
		seq.clear(), lz.clear();
		seq.resize(4*n, 0);	
		lz.resize(4*n, 0);	
		this->n = n;
	}
	ll Query(int l, int r){
		//cout << "Query l r = " << l << ", " << r << endl;
		return query( l, r, 0, n-1, 0);
	}
	ll query(int l, int r, int L, int R, int idx){
		if(l <= L && r >= R){
			return seq[idx] + lz[idx] * (R - L + 1);
		}
		if(l > R || r < L)
			return 0;
		push(idx);
		int M = (L + R) >> 1;
		ll ans = query(l, r, L, M, LC(idx)) + query(l, r, M + 1, R, RC(idx));
		pull(idx, L, R);
		return ans;
	}
	void Modify(int l, int r, int val){
		modify(l, r, 0, n-1, 0, val);
	}
	void modify(int l, int r, int L, int R, int idx, int val) {
		if(l <= L && r >= R){
			lz[idx] += val;	
			return;
		}
		if(l > R || r < L)
			return ;
		int M = (L + R) >> 1;
		push(idx);
		modify(l, r, L, M, LC(idx), val);
		modify(l, r, M + 1, R, RC(idx), val);
		pull(idx, L, R);
	}
	void push(int idx){
		int ldx = LC(idx);
		int rdx = RC(idx);
		lz[ldx] += lz[idx];	
		lz[rdx] += lz[idx];	
		lz[idx] = 0;
	}
	void pull(int idx, int L, int R){
		int ldx = LC(idx);
		int rdx = RC(idx);
		int M = (L + R) >> 1;
		seq[idx] = seq[ldx] + seq[rdx] + lz[ldx] * (M - L + 1) + lz[rdx] * (R - M);
	}
};

segT mT;
stack<pii> St;
vec<ll> ans;

int main(){
	yccc;
	int n, q;
	cin >> n >> q;
	seq.resize(n);
	mT.Build(n);
	ans.resize(q);
	REP(i, n){
		cin >> seq[i];
	}
	REP(i, q){
		int a, b;
		cin >> a >> b;
		a--, b--;
		queries.eb(a, b, i);
	}
	sort(al(queries), piicmp);
	/*
	for(auto & e: queries){
		cout << get<0>(e) << ", " << get<1>(e) << ", " << get<2>(e) << endl;
	}		
	*/
	int qid = 0;
	for(int i = n-1; i >= 0; i--){
		while(!St.empty() && St.top().F < seq[i]) {
			int  l = St.top().S, r = n;
			int val = seq[i] - St.top().F;
			St.pop();
			if(!St.empty())
				r = St.top().S;
			mT.Modify(l, r-1, val);
		}
		if(!St.empty() && St.top().F == seq[i])
			St.top().S = i;
		else
			St.emplace(seq[i], i);
		while(qid < q && get<0>(queries[qid]) == i){
			int l = get<0>(queries[qid]);
			int r = get<1>(queries[qid]);
			//cout << "qid: "  << qid << ": " << l << ", " << r << endl;
			ans[get<2>(queries[qid])] = mT.Query(l, r);	
			qid++;
		}
	}
	for(int i = 0; i < q; i++){
		cout << ans[i] << endl;
	}

	return 0;
}
