// AC 2022-03-16 10:57:57
#include <bits/stdc++.h>
using namespace std;

#define LC(i) (i * 2 + 1)
#define RC(i) (i * 2 + 2)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define REP(i, n) for(int i = 0; i < n; i++)

using ll = long long;
template<typename T> using vec = vector<T>;

template<typename T>
struct segT{
	vec<T> seq;
	vec<T> tag;
	int n;
	void Build(vec<T> & data){
		n = data.size();
		seq.resize(4*n);
		tag.resize(4*n, 0);
		build(0, n-1, 0, data);
	}
	void build(int l, int r, int idx, vec<T>& data){
		if(l == r){
			seq[idx] = data[l];
			return;
		}
		int M = (l + r) >> 1;
		build(l, M, LC(idx), data);
		build(M+1, r, RC(idx), data);
	}
	ll Query(int i){
		return query(i, 0, n-1, 0);
	}
	ll query(int i, int L, int R, int idx){
		if(i == L && i == R){
			return seq[idx] + tag[idx];
		}
		push(idx);
		int M = (L + R) >> 1;
		if(i <= M){
			return query(i, L, M, LC(idx));
		}else{
			return query(i, M+1, R, RC(idx));
		}
	}
	void push(int idx){
		if(tag[idx] != 0){
			tag[LC(idx)] += tag[idx];
			tag[RC(idx)] += tag[idx];
			tag[idx] = 0;
		}
	}
	void Modify(int l, int r, ll val){
		modify(l, r, 0, n-1, 0, val);
	}

	void modify(int l, int r, int L, int R, int idx, ll val){
		if(l <= L && r >= R){
			tag[idx] += val;
			return ;	
		}
		if(r < L || l > R)
			return; 
		push(idx);
		int M = (L + R) >> 1;
		modify(l, r, L, M, LC(idx), val);
		modify(l, r, M+1, R, RC(idx), val);
	}
};


segT<ll> mT;
vec<ll> data;

int main(){
	yccc;
	int n, q;
	cin >> n >> q;
	data.resize(n);
	REP(i, n){
		cin >> data[i];
	}
	mT.Build(data);
	REP(i, q){
		int type;
		cin >> type;
		if(type == 1){
			int a, b;
			ll u;
			cin >> a >> b >> u;
			a--, b--;

			mT.Modify(a, b, u);
			
		}else{
			int k;
			cin >> k;
			k--;
			cout << mT.Query(k) << endl;

		}

	}
	


}
