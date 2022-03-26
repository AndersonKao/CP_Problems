// AC 2022-03-16 10:38:36
// WA n should be size() rather than size() - 1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define REP(i, n) for(int i = 0; i < n; i++)
#define RC(i) (i * 2)
#define LC(i) (i * 2 + 1)


template<typename T>
struct segT{
	vector<T> seq;
	size_t n;

	void Build(vector<T>& data){
		n = data.size();
		seq.resize(4 * n);
		build(0, n-1, 1, data);
	}
	void build(int l, int r, int index, vector<T>& data){
		if(l == r){
			seq[index] = data[l];	
			return ;
		}
		int M = (l + r) >> 1;
		build(l, M, LC(index), data); 
		build(M+1, r, RC(index), data); 
		seq[index] = min(seq[LC(index)], seq[RC(index)]);
	}
	int Query(int l, int r){
		return query(l, r, 0, n-1, 1);
	}
	int query(int l, int r, int L, int R, int index){
		if(l <= L && R <= r){
			return seq[index];
		}

		if(r < L || l > R){
			return numeric_limits<int>::max();
		}
		int M = (L + R) >> 1;
		return min(query(l, r,L, M, LC(index)), query(l, r,M + 1, R, RC(index))); 
	}
	void Modify(int i, int val){
		modify(i, 0, n-1, 1, val);	
	}
	void modify(int i, int L, int R, int index, int val){
		if(i == L && i == R){
			seq[index] = val;
			return ;
		}
		if(i < L || i > R){
			return ;
		}
		int M = (L + R) >> 1;
		modify(i, L, M, LC(index), val);
		modify(i, M+1, R, RC(index), val);
		seq[index] = min(seq[LC(index)], seq[RC(index)]);		
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
