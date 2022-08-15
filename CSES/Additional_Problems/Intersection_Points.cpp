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
	friend ostream& operator<<(ostream& os, const event& e);
};
ostream& operator<<(ostream& os, const event& e){
	return (os << e.type << ", " << e.r << ", " << e.c << ", " << e.len);
}
struct segT{
	vector<int> seq;
//	vector<int> tag;
	int N;
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
	int Query(int l, int r){
		return query(0, N-1, l, r,0);
	}
	int query(int L ,int R, int l, int r, int idx){
		if(L > r || R < l)
			return -1;
#ifdef DsegT
		cout << "query " << L << ", " << R << endl;
#endif
		if(L == R)
			return L;
		int M = (L+R)>>1;
		int li = LC(idx), ri = RC(idx);
		int ans = -1;
		if(seq[li] > 0){
			ans = query(L, M, l, r, li);
		}
		if(ans == -1 && seq[ri] >= 0){
			ans = query(M+1, R, l, r, ri);
		}
		return ans;
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
int main(){
	int n;
	cin >> n;
	vector<event>;
	for(int i = 0; i < n; i++){
		cin >> x1 >> y1 >> x2 >> y2;
		
		if(y1 == y2){ // -------
			
		}
	}

				Es[0].eb(0, e.st.r, e.st.c, -1);	
				Es[0].eb(1, e.ed.r, e.ed.c, -1);	
			}
			else{
				Es[1].eb(2, e.st.r + 1, e.st.c, e.ed.r - e.st.r - 2);
			}
		}	
		for(auto&e: Detector){ // redline
			if(e.st.r == e.ed.r){ // -------
				Es[1].eb(0, e.st.r, e.st.c, -1);	
				Es[1].eb(1, e.ed.r, e.ed.c, -1);	
			}
			else{
				Es[0].eb(2, e.st.r + 1, e.st.c, e.ed.r - e.st.r - 2);
			}
		}	
		auto ecmp = [](const event& lhs, const event&rhs){
			return (lhs.c == rhs.c ? (lhs.type < rhs.type) : (lhs.c < rhs.c));
		};	
		for(int i = 0; i < 2; i++)
			sort(al(Es[i]), ecmp);
		segT mT;
		int ans = 0;
		point apt(2*R, 2*C);
		for(int j = 0; j < 2; j++){
//			cout << "round " << j << "------------------------\n";
			mT.Build(R+2);
			for(int i = 0; i < Es[j].size(); i++){
				event& e = Es[j][i];
//				cout << "event: " << e << endl;
				if(e.type == 0){
					mT.Modify(e.r, 1);
				}
				else if(e.type == 1){
					mT.Modify(e.r, -1);
				}
				else {
					int itsc = mT.RangeS(e.r, e.r + e.len);
					ans += itsc;
					if(itsc > 0){
//						cout << "get inter \n";
						int rpos = mT.Query(e.r, e.r+e.len);	
//						debug(rpos);
						if(rpos < apt.r){
							apt.r = rpos;
							apt.c = e.c;
#ifdef DsegT
							cout << "0: " << apt << endl;
#endif
						}
						else if(rpos == apt.r && e.c < apt.c){
							apt.c = e.c;	
#ifdef DsegT
							cout << "1: " << apt << endl;
#endif
						}
					}
				}
#ifdef DsegT
				mT.Print();
#endif
			}
		}
		cout << "Case " << caseN++ << ": ";
		if(ans == 0){
			cout << "impossible";
		}
		else{
			cout << ans << " " << apt.r << " " << apt.c;
		}
		cout << endl;

	}	

	return 0;
}
