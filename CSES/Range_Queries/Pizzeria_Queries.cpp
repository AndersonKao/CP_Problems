#include <bits/stdc++.h>
using namespace std;
int LC(int x){
	return 2 * x + 1;
}
int RC(int x){
	return 2 * x + 2;
}
#define REP(i, n) for(int i = 0; i < n; i++)
using ll = long long;
template<typename T> using vec = vector<T>;

template <typename T>
struct segT{
	vec<T> seq;
	int n;

	void Build(vec<T>& data){
		n = data.size();
		seq.resize(4*n);
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
		seq[idx] = min(seq[LC(idx)], seq[RC(idx)]);
	}
	T Query(int l, int r){
		return query(l, r, 0, n-1, 0);
	}
	T query(int l, int r, int L, int R, int idx){
		if(l <= L && r >= R)
			return seq[idx];
		if(l > R || r < L)
			return numeric_limits<ll>::max();
		int M = (L + R) >> 1;
		return min(query(l, r, L, M, LC(idx)), query(l, r, M+1, R, RC(idx)));
	}
	void Modify(int i, T val){

		modify(i, 0, n-1, 0, val);
	}
	void modify(int i, int L, int R, int idx, T val){
		if(i == L && i == R){
			seq[idx] = val;
			return;
		}
		int M = (L + R) >> 1;
		if(i <= M)
			modify(i, L, M, LC(idx), val);	
		else
			modify(i, M+1, R, RC(idx), val);	
		seq[idx] = min(seq[LC(idx)], seq[RC(idx)]);
	}
};
vec<ll> data;
segT<ll>dT, uT; // downward, upward

int main(){
	int n, q;
	cin >> n >> q;
	data.resize(n);
	
	REP(i, n){
		cin >> data[i];
		data[i] -= i;
	}
	dT.Build(data);
	REP(i, n){
		data[i] += 2 * i;
	}
	uT.Build(data);
	int type;
	REP(i, q){
		int k, x;
		cin >> type >> k;
		k--;
		if(type == 1){
			cin  >> x;
			dT.Modify(k, x - k);
			uT.Modify(k, x + k);
		}
		else{
			cout << min(dT.Query(0, k) + k, uT.Query(k, n-1) - k) << endl;
		}
	}	
	

	return 0;
}
