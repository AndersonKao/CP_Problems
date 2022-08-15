// AC
// WA
// intersection number may up to long long range
// RE
// recursion is too deep
// WA
// forget I have sort between [1, R], [1, C] rather than [0, R), [0, C)
// WA
// wrong generating laser
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
/*
#define Dgen
#define Dround
#define DsegT
#define Devent
*/
using ll = long long;
using pii = pair<int ,int>;
int R, C, M, N;
struct mirror{
	int r, c;
	int type; /* 0 for / 1 for \ */
	mirror(){}
	mirror(int r, int c, int t): r(r), c(c), type(t){}
	bool operator<(const mirror& rhs){
		return (r == rhs.r ? (c < rhs.c) : (r < rhs.r));
	}
	friend ostream& operator<<(ostream& os, const mirror& rhs);
};
ostream& operator<<(ostream& os, const mirror& rhs){
	return (os << "(" << rhs.r << ", " << rhs.c << ")");
}
struct event{
	int type; // 0 for in, 1 for out, 2 for query
	int r, c;
	int len = 0;
	event(){}
	event(int t, int r, int c):type(t), r(r), c(c){};
	event(int t, int r, int c, int len):type(t), r(r), c(c), len(len){};
	friend ostream& operator<<(ostream& os, const event& e);
};
ostream& operator<<(ostream& os, const event& e){
	return (os << e.type << ", " << e.r << ", " << e.c << ", " << e.len);
}

struct point{
	int r, c;	
	point(){}
	point(int r, int c):r(r), c(c){}
	
	bool operator<(const point& rhs){
		return (this->r == rhs.r ? (this->c < rhs.c) : (this->r < rhs.r));
	}
	friend ostream& operator<<(ostream& os, const point& rhs);
};
ostream& operator<<(ostream& os, const point& rhs){
	return (os << "(" << rhs.r << ", " << rhs.c << ")");
}
point dir[4]= {
	point(0, 1),
	point(0, -1),
	point(-1, 0),
	point(1, 0),
};
struct segment{
	point st, ed;
	segment(){}
	segment(int r1, int c1, int r2, int c2): st(r1,c1), ed(r2,c2){}
	friend ostream& operator<<(ostream& os, const segment& rhs);
};
ostream& operator<<(ostream& os, const segment& rhs){
	return (os << "from " << rhs.st << " to " << rhs.ed);
}
vector<vector<mirror>> mRow;
vector<vector<mirror>> mCol;
using iter = vector<mirror>::iterator;
auto mcmp = [](const mirror& lhs, const mirror& rhs){
		return (lhs.r == rhs.r ? (lhs.c < rhs.c) : (lhs.r < rhs.r));
};
bool genSegments(vector<vector<event>>& Es, int pr, int pc, int d, int dt){
	mirror cur(pr, pc, -1);
	while(true){
		pr = cur.r, pc = cur.c;
#ifdef Dgen
	cout << (dt == 0 ? "Laser : " : "Detector : ");
	cout << "now " << cur.r << ", " << cur.c << ", " << d << endl;
#endif
		if(d == 0){
			iter nxt = ub(al(mRow[pr]), cur, mcmp);
			if(nxt != mRow[pr].end()){
	//			base.eb(pr, pc, nxt->r, nxt->c);	
				Es[dt].eb(0, pr, pc, -1);	
				Es[dt].eb(1, nxt->r, nxt->c, -1);	
				if(nxt->type == 0)
					d = 2;
	//				genSegments(Es, nxt->r, nxt->c, 2, dt);
				else
					d = 3;
//					genSegments(Es, nxt->r, nxt->c, 3, dt);
				cur = *nxt;
			}
			else{
	//			base.eb(pr, pc, pr, C+1);
#ifdef Dgen
	cout << (dt == 0 ? "Laser : " : "Detector : ");
	cout << "now " << pr << ", " << C+1 << ", " << d << endl;
#endif
				Es[dt].eb(0, pr, pc, -1);	
				Es[dt].eb(1, pr, C+1, -1);	
				if(dt == 0){
					if(pr == R){
						return true;
					}
				}
				return false;
			}
		}	
		else if(d == 1){
			iter nxt = lb(al(mRow[pr]), cur, mcmp);
			if(nxt != mRow[pr].begin()){
				nxt--;
	//			base.eb(nxt->r, nxt->c, pr, pc);	
				Es[dt].eb(0, nxt->r, nxt->c, -1);	
				Es[dt].eb(1, pr, pc, -1);	
				if(nxt->type == 0)
					d = 3;
//					genSegments(Es, nxt->r, nxt->c, 3, dt);
				else
					d = 2;
//					genSegments(Es, nxt->r, nxt->c, 2, dt);
				cur = *nxt;
			}
			else{
	//			base.eb(pr, 0, pr, pc);
				Es[dt].eb(0, pr, 0, -1);	
				Es[dt].eb(1, pr, pc, -1);	
#ifdef Dgen
	cout << (dt == 0 ? "Laser : " : "Detector : ");
	cout << "now " << pr << ", " << 0 << ", " << d << endl;
#endif
				return false;
			}
		}
		else if(d == 3){
			iter nxt = ub(al(mCol[pc]), cur, mcmp);
			if(nxt != mCol[pc].end()){
	//			base.eb(pr, pc, nxt->r, nxt->c);	
				Es[dt^1].eb(2, pr + 1, pc, nxt->r - pr - 2);
				if(nxt->type == 0)
					d = 1;
//					genSegments(Es, nxt->r, nxt->c, 1, dt);
				else
					d = 0;
//					genSegments(Es, nxt->r, nxt->c, 0, dt);
				cur = *nxt;
			}
			else{
	//			base.eb(pr, pc, R+1 , pc);
				Es[dt^1].eb(2, pr + 1, pc, R+1 - pr - 2);
#ifdef Dgen
	cout << (dt == 0 ? "Laser : " : "Detector : ");
	cout << "now " << R+1 << ", " << pc << ", " << d << endl;
#endif
				return false;
			}
		}	
		else if(d == 2){
			iter nxt = lb(al(mCol[pc]), cur, mcmp);
			if(nxt != mCol[pc].begin()){
				nxt--;
	//			base.eb(nxt->r, nxt->c, pr, pc);	
				Es[dt^1].eb(2, nxt->r + 1, nxt->c, pr - nxt->r - 2);
				if(nxt->type == 0)
					d = 0;
//					genSegments(Es, nxt->r, nxt->c, 0, dt);
				else
					d  = 1;
//					genSegments(Es, nxt->r, nxt->c, 1, dt);
					cur = *nxt;
			}
			else{
	//			base.eb(0, pc, pr, pc);
				Es[dt^1].eb(2, 1, pc, pr - 0 - 2);
#ifdef Dgen
	cout << (dt == 0 ? "Laser : " : "Detector : ");
	cout << "now " << 0 << ", " << pc << ", " << d << endl;
#endif
				return false;
			}
		}
	}
	return false;
};
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
#ifdef DsegT
		cout << L << " to " << R << ": " << seq[idx] << endl;
#endif 
		if(L == R)
			return;
		int M = (L+R)>>1;
		print(L, M, LC(idx));
		print(M+1, R, RC(idx));
	}
};
int main(){
	int caseN = 1;
	while(cin >> R >> C >> M >> N){
		mRow.clear();
		mRow.resize(R+2);
		mCol.clear();
		mCol.resize(C+2);
		for(int i = 0; i < M; i++){
			int r, c;		
			cin >> r >> c;
			mRow[r].eb(r, c, 0);
			mCol[c].eb(r, c, 0);
		}
		for(int i = 0; i < N; i++){
			int r, c;		
			cin >> r >> c;
			mRow[r].eb(r, c, 1);
			mCol[c].eb(r, c, 1);
		}
//		mRow[0].eb(1, 0, 2);
//		mRow[R-1].eb(R, C+1, 2);
		for(int i = 1; i <= R; i++){
			sort(al(mRow[i]));
		}
		for(int i = 1; i <= C; i++){
			sort(al(mCol[i]));
		}
#ifdef Dsort
		for(int i = 0; i < R; i++){
			if(mRow[i].size()){
				cout << "row " << i  << ": ";
				for(auto e : mRow[i]){
					cout << e << " ";
				}
				cout << endl;
			}
		}
		for(int i = 0; i < C; i++){
			if(mCol[i].size()){
				cout << "col " << i  << ": ";
				for(auto e : mCol[i]){
					cout << e << " ";
				}
				cout << endl;
			}
		}	
#endif
	/*
		vector<segment> Laser;	
		genSegments(Laser, 1, 0, 0);
#ifdef Dgen
		cout << "Laser:\n";
		for(auto &e: Laser){
			cout << e << endl;
		}
#endif
		if(Laser.back().ed.r == R && Laser.back().ed.c == C+1){
			cout << "Case " << caseN++ << ": 0\n";
			continue;
		}
		vector<segment> Detector;
		genSegments(Detector, R, C+1, 1);
#ifdef Dgen
		cout << "Detector:\n";
		for(auto &e: Detector){
			cout << e << endl;
		}
#endif
		*/
		vector<vector<event>> Es(2);
		if(genSegments(Es, 1, 0 ,0, false)){
			cout << "Case " << caseN++ << ": 0\n";
			continue;
		}
		genSegments(Es, R, C+1, 1, true);
		/*
		for(auto&e: Laser){ // blueline
			if(e.st.r == e.ed.r){ // -------
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
		*/
		auto ecmp = [](const event& lhs, const event&rhs){
			return (lhs.c == rhs.c ? (lhs.type < rhs.type) : (lhs.c < rhs.c));
		};	
		for(int i = 0; i < 2; i++)
			sort(al(Es[i]), ecmp);
		segT mT;
		ll ans = 0;
		point apt(2*R, 2*C);
		for(int j = 0; j < 2; j++){
#ifdef Dround
			cout << "round " << j << "------------------------\n";
#endif
			mT.Build(R+2);
			for(int i = 0; i < Es[j].size(); i++){
				event& e = Es[j][i];
#ifdef Devent
				cout << "event: " << e << endl;
#endif
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
						int rpos = mT.Query(e.r, e.r+e.len);	
#ifdef Dinter
						cout << "get inter \n";
						debug(rpos);
						debug(e.c);
#endif
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
