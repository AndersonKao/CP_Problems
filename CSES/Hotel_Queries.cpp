// AC 2022-03-16 11:37:06
#include <bits/stdc++.h>
using namespace std;

#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define LC(i) (i * 2 + 1)
#define RC(i) (i * 2 + 2)
using ll = long long;
template<typename T> using vec = vector<T>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;


template<typename T>
struct segT{
	vec<T> seq;
	int n;
	void Build(vec<T>&data){
		n = data.size();
		seq.resize(n * 4);
		build(0, n-1, 0, data);
	}
	void build(int L, int R, int idx,vec<T> & data){
		if(L == R){
			seq[idx] = data[L];	
			return ;
		}
		int M = (L + R) >> 1;
		build(L, M, LC(idx), data);
		build(M + 1, R, RC(idx), data);
		seq[idx] = max(seq[LC(idx)], seq[RC(idx)]);
	}
	int Query(int val){
		if(seq[0] < val)
			return -1;
		return query(0, n-1, 0, val);
	}
	int query(int L, int R, int idx, int val){
		if(L == R){
			return L;
		}
		int M = (L + R) >> 1;
		if(seq[LC(idx)] >= val){
			return query(L, M, LC(idx), val);
		}else{
			return query(M+1, R, RC(idx), val);
		}
	}
	void Modify(int i, int val){
		modify(i, 0, n-1, 0, val);
	} 
	void modify(int i, int L, int R, int idx, int val){
		if(L == i && R == i){
			seq[idx] -= val;
			return ;
		}
		int M = (L + R) >> 1;
		if(i <= M){
			modify(i, L, M, LC(idx), val);
		}else{
			modify(i, M+1, R, RC(idx), val);
		}
		seq[idx] = max(seq[LC(idx)], seq[RC(idx)]);
	}

};

segT<int> mT;
vec<int> data;

int main(){

	int n, m;
	cin >> n >> m;
	data.resize(n);
	REP(i, n)
		cin >> data[i];
	mT.Build(data);
	int r;
	REP(i, m){
		cin >> r;
		int k= mT.Query(r);
		cout << k +1 << (i == m -1 ? "\n" : " ");
		if(k != -1)
			mT.Modify(k, r);
	}
	return 0;
}
