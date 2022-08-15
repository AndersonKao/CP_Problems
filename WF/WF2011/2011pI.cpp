#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define debug(x) cout << #x << ": " << x << endl;
#define al(x) x.begin(), x.end()
#define F first
#define S second
#define depii(x) cout << "(" << x.first << ", " << x.second << ")" << endl;
#define debug(x) cout << #x << ": " << x << endl;
using pii = pair<int, int>;
const int uB = 1000003;
int N;
struct point{
	int x, y;
	point(){}
	point(int x, int y):x(x), y(y){}
};
struct event{
	int type;
	int x, y;
	int id;
	event(){} // 0 for in , 1 for out
	event(int t, int x, int y, int id):type(t), x(x), y(y), id(id){}
	bool operator<(const event & rhs){
		if(x == rhs.x){
			return y < rhs.y;
		}
		return x < rhs.x;
	}
};
vector<point> mummies;
vector<int> validm;
bool check(int W){
	int hL = -W;
	int hR = +W;
	vector<event> eQ;
	for(int i = 0; i < mummies.size(); i++){
		point&m = mummies[i];
		eQ.eb(0, m.x - W, m.y, i);	
		eQ.eb(1, m.x + W + 1, m.y, i);	
	}
	eQ.eb(2, hL, 0, -1);
	eQ.eb(2, hR, 0, -1);
	sort(al(eQ));
//	fill(al(validm), 0);
//	segT mT;
//	mT.Build(2 * uB);
	priority_queue<pii, vector<pii>, greater<pii>> upQ;
	priority_queue<pii> downQ;
	for(int i = 0; i < eQ.size(); i++){
		event& e = eQ[i];
		if(e.x >= W+1)
			return true;
		if(e.type == 0){
			if(e.y >= 0){
				upQ.emplace(e.y, e.id); 
			}
			if(e.y <= 0){
				downQ.emplace(e.y, e.id);
			}
			validm[e.id] = 1;
		}
		else if(e.type == 1){
			validm[e.id] = 0;
		}
		while(upQ.size() && validm[upQ.top().S] == 0){
			upQ.pop();	
		}
		while(downQ.size() && validm[downQ.top().S] == 0){
			downQ.pop();	
		}
		if(i == eQ.size() - 1 || (eQ[i+1].x != e.x)){
			if(e.x >= hL && e.x <= hR){
				int uc = uB, dc = -uB;
				if(upQ.size())
					uc = upQ.top().F - W;
				if(downQ.size())
					dc = downQ.top().F + W;
				if(uc == uB && dc < W){
					return false;
				}
				else if(dc == -uB && uc > -W){
					return false;
				}
				else if(uc > dc + 1){
					return false;
				}
			}
		}
	}
	return true;
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int caseN = 1;	
	while(cin >> N){
		if(N == -1) break;
		if(N == 0){
			cout<< "Case " << caseN++ << ": never\n";
			continue;
		}
		mummies.clear();
		for(int i = 0; i < N; i++){
			int x, y;
			cin >> x >> y;
			mummies.eb(x, y);
		}
		validm.resize(mummies.size());
		if(check(1000000) == false){
			cout<< "Case " << caseN++ << ": never\n";
			continue;
		}
		int L = 1, B = uB;
		while(L < B){
			int M = (L+B) >> 1;
			if(check(M)){
				B = M;
			}
			else{
				L = M + 1;
			}
		}
		cout << "Case " << caseN++ << ": ";
		if(L == uB){
			cout << "never";
		}
		else 
			cout << L;
		cout << endl;
	}
	return 0;
}
