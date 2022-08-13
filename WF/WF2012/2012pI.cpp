// first narrow range should be
// L = V[0] / 1.05 * 0.95, R = V[0] / 0.95 * 1.05
// range case can be 0. (>= 0 will causes error
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
int R, C, M, N;
struct mirror{
	int r, c;
	int type; /* 0 for / 1 for \ */
	mirror(){}
	mirror(int r, int c, int t): r(r), c(c), type(t){}
	bool operator<(const mirror rhs){
		return (this->r == rhs.r ? (this->c < rhs.c) : (this->r < rhs.r));
	}
};
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
		return (lhs->r == rhs.r ? (lhs->c < rhs.c) : (lhs->r < rhs.r));
}
void genSegments(vector<segment>& base, int pr, int pc, int d){
	mirror cur(pr, pc, -1);
	if(d == 0){
		iter nxt = ub(al(mRow[pr]), cur);
		if(nxt != mRow[pr].end()){
			base.eb(pr, pc, nxt->r, nxt->c);	
			if(nxt->type == 0)
				genSegments(base, nxt->r, nxt->c, 2);
			else
				genSegments(base, nxt->r, nxt->c, 3);
		}
		else{
			base.eb(pr, pc, pr, C+1);
			return ;
		}
	}	
	else if(d == 1){
		iter nxt = lb(al(mRow[pr]), cur);
		if(nxt != mRow[pr].begin()){
			nxt--;
//			base.eb(pr, pc, nxt->r, nxt->c);	
			base.eb(nxt->r, nxt->c, pr, pc);	
			if(nxt->type == 0)
				genSegments(base, nxt->r, nxt->c, 3);
			else
				genSegments(base, nxt->r, nxt->c, 2);
		}
		else{
			base.eb(pr, pc, pr, 0);
			return ;
		}
	}
	else if(d == 3){
		iter nxt = ub(al(mCol[pr]), cur);
		if(nxt != mCol[pr].end()){
			base.eb(pr, pc, nxt->r, nxt->c);	
			if(nxt->type == 0)
				genSegments(base, nxt->r, nxt->c, 1);
			else
				genSegments(base, nxt->r, nxt->c, 0);
		}
		else{
			base.eb(pr, pc, R+1 , pc);
			return ;
		}
	}	
	else if(d == 2){
		iter nxt = lb(al(mCol[pr]), cur);
		if(nxt != mCol[pr].begin()){
			nxt--;
//			base.eb(pr, pc, nxt->r, nxt->c);	
			base.eb(nxt->r, nxt->c, pr, pc);	
			if(nxt->type == 0)
				genSegments(base, nxt->r, nxt->c, 0);
			else
				genSegments(base, nxt->r, nxt->c, 1);
		}
		else{
			base.eb(pr, pc, 0, pc);
			return ;
		}
	}
};
int main(){
	while(cin >> R >> C >> M >> N){
		mRow.clear();
		mRow.resize(R+2);
		mCol.clear();
		mCol.resize(C + 2);
		for(int i = 0; i < M; i++){
			int r, c;		
			cin >> r >> c;
			mRow[r].eb(r, c, 0);
			mCol[c].eb(r, c, 0);
		}
		for(int i = 0; i < M; i++){
			int r, c;		
			cin >> r >> c;
			mRow[r].eb(r, c, 1);
			mCol[c].eb(r, c, 1);
		}
//		mRow[0].eb(1, 0, 2);
//		mRow[R-1].eb(R, C+1, 2);
		for(int i = 0; i < R; i++){
			sort(al(mRow[i]));
		}
		for(int i = 0; i < C; i++){
			sort(al(mCol[i]));
		}
		vector<segment> Laser;	
		genSegments(Laser, 0, 0, 0);
		for(auto &e: Laser){
			cout << e << endl;
		}
	}	

	return 0;
}
