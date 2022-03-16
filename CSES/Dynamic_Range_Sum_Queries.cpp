#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define REP(i, n) for(int i = 0; i < n; i++)
#define RC(i) (i * 2 + 1)
#define LC(i) (i * 2 + 2)


template<typename T>
struct segT{
	vector<T>  seq;
	int n;
	segT(){

	}
	void Build(vector<T>& data){
		n = data.size();
		seq.resize(data.size() * 4, 0);
		build(0, data.size() - 1, 0, data);
	};
	void build(int l, int r, int index, vector<T>& data){
		if(l == r){
			seq[index] = data[l];
			return;
		}

		int M = (l + r) >> 1;
		
		build(l, M, LC(index), data);
		build(M + 1, r, RC(index), data);
		seq[index] = (seq[LC(index)] + seq[RC(index)]);
	}
	ll Query(int l, int r){
		return query(l, r, 0, n-1, 0);
	}
	ll query(int l, int r, int L, int R, int index){
		if(l <= L && r >= R){
			return seq[index];
		}
		if(l > R || r < L)
			return 0;
		int M = (L + R) >> 1;

		return (query(l, r, L, M, LC(index))+ query(l, r, M+1,R, RC(index)));
	}
	void Modify(int i, ll val){
		modify(i, i, 0, n-1, 0, val);
	}
	void modify(int l, int r, int L, int R, int index, ll val){
		if(l == L && r == R){
			seq[index] = val;
			return ;
		}
		
		if(l > R || r < L)
			return ;
		int M = (L + R) >> 1;
		modify(l, r, L, M, LC(index), val);
		modify(l, r, M+1, R, RC(index), val);
		seq[index] = seq[LC(index)] + seq[RC(index)];
	}
};

segT<ll> mT;
vector<ll> data;


int main(){
	
//	yccc;
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
		if(type == 2){
			int qL, qR;
			cin >> qL >> qR;
			qL--, qR--;
			cout << mT.Query(qL, qR) << endl;
		}else{
			int k;
			ll u;
			cin >> k >> u;
			k--;
			mT.Modify(k, u);
		}
	}
	
	

	return 0;
}
