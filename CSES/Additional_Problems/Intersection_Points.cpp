// once AC 2022-08-20 07:17:08
#include <bits/stdc++.h>
using namespace std;
#define al(x) x.begin(), x.end()
#define eb emplace_back
#define F first
#define S second
#define LC(x) (x * 2 + 1)
#define RC(x) (x * 2 + 2)
#define debug(x) cout << #x << ": " << x << endl;
#define lb lower_bound
#define ub upper_bound
using ll = long long;
using pii = pair<int ,int>;
struct event{
	int type; // 0 for in, 1 for out, 2 for query
	int x, y;
	int len = 0;
	event(){}
	event(int t, int x, int y):type(t), x(x), y(y){};
	event(int t, int x, int y, int len):type(t), x(x), y(y), len(len){};
	int operator<(const event& e){
		return x < e.x;
	}
	friend ostream& operator<<(ostream& os, const event& e);
};
ostream& operator<<(ostream& os, const event& e){
	return (os << e.type << ", " << e.x << ", " << e.y << ", " << e.len);
}
struct segT{
	vector<int> seq;
//	vector<int> tag;
	int N;
	segT(){};
	segT(int n){
		this->Build(n);
	}
	void Build(int n){
		seq.clear();
		seq.resize(4*n, 0);
		this->N = n;
	}
	int RangeS(int l, int r){
		if(l > r)
			return 0;
		return rangeS(0, N-1, l ,r, 0);	
	}
	int rangeS(int L, int R, int l, int r, int idx){
		if(L > r || R < l)
			return 0;
		if(l <= L && R <= r){
			return seq[idx];
		}
		int M = (L+R)>>1;
		return rangeS(L, M, l, r, LC(idx)) + rangeS(M+1, R, l, r, RC(idx));
	}
	void Modify(int pos, int val){
		modify(0, N-1, 0, pos, val); 
	}
	void	modify(int L, int R, int idx, int pos, int val){
		if(L == R){
			seq[idx] += val;	
			return;
		}
		int M = (L+R)>>1;
		if(pos <= M){
			modify(L, M, LC(idx), pos, val);
		}
		else
			modify(M+1, R, RC(idx), pos, val);
		seq[idx] = seq[LC(idx)] + seq[RC(idx)];
	}
	void Print(){
		print(0, N-1, 0);
	}
	void print(int L, int R, int idx){
		cout << L << " to " << R << ": " << seq[idx] << endl;
		if(L == R)
			return;
		int M = (L+R)>>1;
		print(L, M, LC(idx));
		print(M+1, R, RC(idx));
	}
};
const int offset = 1000000;
int main(){
	int n;
	cin >> n;
	vector<event> eQ;
	int x1, y1, x2, y2;
	for(int i = 0; i < n; i++){
		cin >> x1 >> y1 >> x2 >> y2;
		
		if(y1 != y2){ // -------
			eQ.eb(2, x1, y1 + offset, y2 - y1);						
		}
		else{
			eQ.eb(0, x1, y1 + offset);
			eQ.eb(1, x2, y2 + offset);
		}
	}

	sort(al(eQ));
	segT mT(2000002);
	ll ans = 0;
	for(event& e: eQ){
//		cout << e << endl;
		if(e.type == 0){
			mT.Modify(e.y, 1);
		}	
		else if(e.type == 1){
			mT.Modify(e.y, -1);
		}
		else {
			ans += mT.RangeS(e.y, e.y + e.len);
		}
	}
	cout << ans << endl;
	return 0;
}
