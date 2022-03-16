// AC 2022-03-16 12:57:59
// negative ans case not well processed, line 43 need takes max
// WA we should collect allans rather thant ans for pans and sans
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
#define LC(i) (2 * i + 1)
#define RC(i) (2 * i + 2)
#define REP(i, n) for(int i = 0;i < n; i++)

template<typename T>
struct segT{
	struct seg{
		ll ans, pans, sans, allans;
		int plen, slen;
	};
	vec<seg> seq;
	int n;
	void Build(vec<T>& data){
		n = data.size();
		seq.resize(4*n);
		build(0, n-1, 0, data);
	}
	void build(int l, int r, int idx, vec<T>& data){
		if(l == r){
			seq[idx].ans = seq[idx].allans = seq[idx].pans =seq[idx].sans= data[l];	
			seq[idx].plen = seq[idx].slen = 1;
			return;
		}
		int M = (l + r) >> 1;
		build(l, M, LC(idx), data);
		build(M + 1, r, RC(idx), data);
		seg sL = seq[LC(idx)], sR = seq[RC(idx)];
		
		seq[idx].pans = max(sL.pans, sL.allans + sR.pans);
		seq[idx].sans = max(sR.sans, sR.allans + sL.sans);
		seq[idx].allans = sR.allans + sL.allans;
		seq[idx].ans = max(sL.sans + sR.pans, max(sL.ans, sR.ans)); 
	}
	ll Query(int l, int r){
		return max(0LL, query(l, r, 0, n-1, 0));
	}
	ll query(int l, int r, int L, int R,  int idx){
		if(l < L && r > R){
			return seq[idx].allans;
		}else if(l == L && r > R){
			return seq[idx].sans;
		}else if(l < L && r == R){
			return seq[idx].pans;
		}else if(l == L && r == R){
			return seq[idx].ans;	
		}
	
		if(l > R || r < L)
			return 0;	
		int M = (L + R) >> 1;
		ll ans = 0;
		ans = max(ans, query(l, M, L, M, LC(idx)));
		ans = max(ans, query(M + 1, r, M + 1, R, RC(idx)));
		ans = max(ans, query(l ,r, L, M, LC(idx)) + query(l, r, M + 1, R, RC(idx)));
		return ans;
	}
	void Modify(int i, ll val){
		modify(i, 0, n-1, 0, val);
	}
	void modify(int i, int L, int R, int idx, ll val){
		if(i == L && i == R){
			seq[idx].ans = seq[idx].allans = seq[idx].pans =seq[idx].sans= val;	
			seq[idx].plen = seq[idx].slen = 1;
			return;
		}

		int M = (L + R) >> 1;	
		if(i <= M)
			modify(i, L, M, LC(idx), val);	
		else
			modify(i, M+1, R, RC(idx), val);	
	
		seg sL = seq[LC(idx)], sR = seq[RC(idx)];
		
		seq[idx].pans = max(sL.pans, sL.allans + sR.pans);
		seq[idx].sans = max(sR.sans, sR.allans + sL.sans);
		seq[idx].allans = sR.allans + sL.allans;
		seq[idx].ans = max(sL.sans + sR.pans, max(sL.ans, sR.ans)); 
	}

};

vec<ll> data;
segT<ll> mT;

int main(){
	int n, m;
	cin >> n >> m;
	data.resize(n);

	REP(i, n){
		cin >> data[i];
	}
	mT.Build(data);
	REP(i, m){
		int k;
		ll x;
		cin >> k >> x;
		k--;
		mT.Modify(k, x);
		cout << mT.Query(0, n-1) << endl;
	}	


	


	return 0;
}
