// AC 2022-03-16 17:06:39
// WA
// remember to reset the child's increment tag even when push
// when set value, the increment tag need to be deleted.
#include <bits/stdc++.h>
using namespace std;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define REP(i, n) for(int i = 0; i < n; i++)
#define LC(i) (2 * i + 1)
#define RC(i) (2 * i + 2)
using ll = long long;
template<typename T> using vec = vector<T>;

struct segT{
	struct seg{
		ll Inctag;
		ll settag;
		ll val;
	};
	vec<seg> seq;
	int n;

	void Build(vec<int>& data){
		n = data.size();
		seq.resize(4 *n);	
		build(0, n-1, 0, data);
	}
	void build(int l, int r, int idx, vec<int>& data){
		if(l == r){
			seq[idx].Inctag = seq[idx].settag = 0;
			seq[idx].val = data[l];	
			return;
		}
		int M = (l + r) >> 1;
		build(l, M, LC(idx), data);
		build(M+1, r, RC(idx), data);
		seq[idx].Inctag = seq[idx].settag = 0;
		seq[idx].val = seq[LC(idx)].val + seq[RC(idx)].val;
	}
	void Incre(int l, int r, int x){
		incre(l, r, 0, n-1, 0, x);	
	}
	void incre(int l, int r, int L, int R, int idx, int x){
		if(l <= L && r >= R){
			seq[idx].Inctag += x;	
			return ;
		}
		if(l > R || r < L)
			return ;
		push(L, R, idx);
		int M = (L + R) >> 1;
		incre(l, r, L, M, LC(idx), x);
		incre(l, r, M+1, R, RC(idx), x);
		pull(L, R, idx);
	}
	void Setval(int l, int r, int x){
		setval(l, r, 0, n-1, 0, x);	
	}
	void setval(int l, int r, int L, int R, int idx, int x){
		if(l <= L && r >= R){
			seq[idx].settag = x;	
			seq[idx].Inctag = 0;
			return ;
		}
		if(l > R || r < L)
			return ;
		push(L, R, idx);
		int M = (L + R) >> 1;
		setval(l, r, L, M, LC(idx), x);
		setval(l, r, M+1, R, RC(idx), x);
		pull(L, R, idx);
	}
	void push(int L, int R, int idx){
		ll x;
		if((x = seq[idx].settag)){
			seq[LC(idx)].settag = x;
			seq[RC(idx)].settag = x;
			seq[LC(idx)].Inctag = 0;
			seq[RC(idx)].Inctag = 0;
			seq[idx].settag = 0;
			seq[idx].val = x * (R-L + 1);
		}
		if((x = seq[idx].Inctag)){
			seq[LC(idx)].Inctag += x;
			seq[RC(idx)].Inctag += x;
			seq[idx].Inctag = 0;
			seq[idx].val += x * (R-L + 1);
		}
	}
	void pull(int L, int R, int idx){
		seq[idx].val = 0;
		int M = (L + R) >> 1;
		if(seq[LC(idx)].settag){
			seq[idx].val += (seq[LC(idx)].settag + seq[LC(idx)].Inctag) * (M - L + 1);
		}else{
			seq[idx].val += seq[LC(idx)].val + (seq[LC(idx)].Inctag) * (M - L + 1);
		}
		if(seq[RC(idx)].settag){
			seq[idx].val += (seq[RC(idx)].settag + seq[RC(idx)].Inctag) * (R - M);
		}else{
			seq[idx].val += seq[RC(idx)].val + (seq[RC(idx)].Inctag) * (R - M);
		}
	}
	ll Query(int l, int r){
		return query(l, r, 0, n-1, 0);
	}
	ll query(int l, int r, int L, int R, int idx){
		if(l <= L && r >= R){
			if(seq[idx].settag){
				return (seq[idx].settag + seq[idx].Inctag) * (R - L + 1);
			}else{
				return seq[idx].val + seq[idx].Inctag * (R- L +1);
			}
		}
		if(l > R || r < L)
			return 0;
		push(L, R, idx);
		int M = (L + R) >> 1;
		
		ll ans = query(l, r, L, M, LC(idx)) + query(l, r, M+1, R, RC(idx));
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
	int type, a, b, x;
	REP(i, q){
		cin >> type >> a >> b;
		a--, b--;
		if(type == 1){
			cin >> x;
			mT.Incre(a, b, x);
		}
		else if(type == 2){
			cin >> x;
			mT.Setval(a, b, x);
		}
		else if(type == 3){
			cout << mT.Query(a, b) << endl;
		}

	}


	return 0;
}
