#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < n; i++)
#define F first
#define S second
using ll = long long;
using pii = pair<int ,int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
inline int LC(int idx){
	return idx* 2 + 1;
}
inline int RC(int idx){
	return idx* 2 + 2;
}
const ll minS = numeric_limits<ll>::min() /5;

struct segT{
	struct Node{
		ll sum, ans;
	};
	int n;	
	vec<Node> seq;
	void Build(vec<int> & data){
		n = data.size();
		seq.resize(4*n);
		build(0, n-1, 0, data);
	}
	void build(int l, int r, int idx, vec<int>& data){
		if(l == r){
			seq[idx].sum = data[l]; 
			seq[idx].ans = max(0,  data[l]); 
			return ;
		}
		int M = (l + r) >> 1;
		build(l, M, LC(idx), data);
		build(M+1, r, RC(idx), data);
		seq[idx].sum = seq[LC(idx)].sum + seq[RC(idx)].sum;
		seq[idx].ans = max(seq[LC(idx)].sum + seq[RC(idx)].ans, seq[LC(idx)].ans);
	}
	void Modify(int pos, int val){
		modify(pos, 0, n-1, 0, val);
	}
	void modify(int pos, int l, int r, int idx, int val){
		if(l == pos && r == pos){
			seq[idx].sum = val;
			seq[idx].ans = max(0, val); 
			return ;
		}
		int M = (l + r) >> 1;
		if(pos <= M)
			modify(pos, l, M, LC(idx), val);
		else
			modify(pos, M+1, r, RC(idx), val);
		seq[idx].sum = seq[LC(idx)].sum + seq[RC(idx)].sum;
		seq[idx].ans = max(seq[LC(idx)].sum + seq[RC(idx)].ans, seq[LC(idx)].ans);
//		cout << "From " << l << " to " << r << endl;
//		cout << "sum: " << seq[idx].sum << " ans : " << seq[idx].ans << endl;
	}
	ll Query(int l, int r){
//		cout << "Query-----------------\n";
		return query(l, r, 0, n-1, 0).S;	
	}
	pll query(int l, int r, int L, int R, int idx){
		if(l > R || r < L)
			return pll(0, 0);
		if(l <= L && r >= R){
//			cout << "From " << l << " to " << r << " at " << "From " << L << " to " << R << endl;
//			cout << "seq[idx].sum: " << seq[idx].sum<< endl;
			return pll(seq[idx].sum, seq[idx].ans);
		}
		int M = (L + R) >> 1;
		pll ans (0, 0);	
		pll pLC = query(l, r, L, M, LC(idx)); 
		pll pRC= query(l, r, M + 1, R, RC(idx));
		ans = pll(pLC.F + pRC.F, max(pLC.F + pRC.S, pLC.S));	
		return ans;
	}
};

segT mT;
vec<int> data;
int main(){
	int n, q;
	cin >> n >> q;
	data.resize(n);
	REP(i, n){
		cin >> data[i];
	}
	mT.Build(data);
	int type, a, b;
	REP(i, q){
		cin >> type >> a >> b;
		if(type == 1){
			a--;
			mT.Modify(a, b);
		}
		else{
			a--, b--;
			cout << mT.Query(a, b) << endl;
		}
	}
	return 0;
}	

