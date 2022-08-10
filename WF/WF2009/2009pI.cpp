// WA
// becare of long long
// WA
// shouldn't use double
#include <bits/stdc++.h>
using namespace std;
#define al(x) x.begin(), x.end()
#define eb emplace_back
#define Lc(x) (x * 2 + 1)
#define Rc(x) (x * 2 + 2)
#define debug(x) cout << #x << ": " << x << endl;
using ll = long long;
struct segT{
	vector<int> seq;
	vector<int> htag; // hastag
	int N;
	segT(int N){
		this->Build(N);
	}
	void Build(int N){
		this->N = N;
		seq.resize(4*N);	
		fill(al(seq), 0);
		htag.resize(4*N);	
		fill(al(htag), 1);
	}	
	void build(int L, int R,int idx){
		if(L == R){
			htag[idx] = true;
			return;
		}
		if(R < L)
			return;
		int M = (L+R) >> 1;
		build(L, M, Lc(idx));
		build(M+1, R, Rc(idx));
	}
	int Query(int l, int r){
		return query(l, r, 0, N-1, 0);	
	}
	int query(int l, int r, int L, int R, int idx){
		if(l <= L && R <= r && htag[idx]){
			return seq[idx];
		} 
		if(l > R || r < L){
			return -1;
		}

		int M = (L+R) >> 1;
		push(idx);
		int ans = max(query(l, r, L, M, Lc(idx)), query(l, r, M+1, R, Rc(idx)));
		return ans;
	}
	void Modify(int l, int r, int val){
		modify(l, r, 0, N-1, 0, val);
	}
	void modify(int l, int r, int L, int R, int idx, int val){
		if(l <= L && R <= r){
			seq[idx] = val;
			htag[idx] = true;
			return;
		} 
		if(l > R || r < L)
			return ;
		push(idx);
		int M = (L + R) >> 1;
		modify(l, r, L, M, Lc(idx), val);
		modify(l, r, M+1, R, Rc(idx), val);
		pull(idx);
	}
	void push(int idx){
		int l = Lc(idx), r = Rc(idx);
		if(htag[idx]){
			seq[l] = seq[r] = seq[idx];
			htag[l] = htag[r] = true;
		}
		htag[idx] = false;
	}
	void pull(int idx){
		int l = Lc(idx), r = Rc(idx);
		if(htag[l] && htag[r] && seq[l] == seq[r]){
			htag[idx] = true;
			seq[idx] = seq[l];
		}
	}
};
struct window{
	ll x,y;
	ll w, h;
	int vl, hl; // 0 for strut
	int t, b, l, r; // 1 for spring
	int id;
	window(){
		t = b = l = r = 0;
	}
	window(ll x, ll y, ll w, ll h):x(x), y(y), w(w), h(h){
		window();
	}
	bool operator<(const window& rhs){
		return (x != rhs.x ? x < rhs.x : id < rhs.id);
	}
	friend ostream& operator<<(ostream& os, const window& w);
};
	ostream& operator<<(ostream& os, const window& w){
		return (os << "Window " << w.id << ", x = " << w.x << ", y = " << w.y << ", width = " << w.w << ", height = " << w.h);
	}
struct event{
	int x;
	int ly, ry; 
	int id;
	int type; // 0 in, 1 out
	event(){
		type = x = ly = ry = id = 0;
	};
	event(int x, int ly, int ry, int id, int t):x(x), ly(ly), ry(ry), id(id), type(t){}
	bool operator<(const event& rhs){
		return (x != rhs.x ? x < rhs.x : id < rhs.id);
	}
	friend ostream& operator<<(ostream& os,const event & e);
};
ostream& operator<<(ostream& os,const event & e){
	return (os << e.x << ", " << e.ly << ", " << e.ry << ", " << e.type << ", " << e.id);
}

void BuildG(vector<event> & Events, vector<vector<int>>& G, int oh){
	vector<int> par(G.size(), 0);	
	segT myT(oh+1); // reserve for 0 
	for(event&e: Events){
//		cout << e << endl;
		if(e.type == 0){
			par[e.id] = myT.Query(e.ly, e.ry);
			myT.Modify(e.ly, e.ry, e.id);
		}
		else{
			myT.Modify(e.ly, e.ry, par[e.id]);
		}
	}
	for(int i = 0; i < par.size(); i++){
//		cout << i << ": " << par[i] << endl;
		if(par[i] >= 0 && i > 0)
			G[par[i]].eb(i);
	}
}
vector<window> wins;
vector<window> Rwins; //resized wins
void DFS(vector<vector<int>> &G, int u, int pa){
	window& Nwin = Rwins[u];	
	if(Nwin.vl == 0 && Nwin.l == 0 && Nwin.r == 0){
		Nwin.r = 1;
	}	
	if(Nwin.hl == 0 && Nwin.t == 0 && Nwin.b == 0){
		Nwin.t = 1;
	}	
	ll xdiff = wins[u].x - wins[pa].x;
	ll ydiff = wins[u].y - wins[pa].y;
	ll hlen = 0, vlen = 0;
	if(Nwin.l == 0)
		hlen += xdiff;
	if(Nwin.vl == 0)
		hlen += wins[u].w;
	if(Nwin.r == 0)
		hlen += (wins[pa].w - xdiff - wins[u].w);
	if(Nwin.t == 0)
		vlen += ydiff;
	if(Nwin.hl == 0)
		vlen += wins[u].h;
	if(Nwin.b == 0)
		vlen += (wins[pa].h - ydiff - wins[u].h);
	
	ll hrate1 = (Rwins[pa].w - hlen) ;
	ll hrate2 = (wins[pa].w - hlen);
	ll vrate1 = (Rwins[pa].h - vlen) ;
	ll vrate2 = (wins[pa].h - vlen);
#ifdef Dresize
	debug(u);
	debug(hlen);
	debug(vlen);
	debug(hrate);
	debug(vrate);
#endif

	if(Nwin.l == 1){
		Nwin.x = Rwins[pa].x + (xdiff * hrate1) / hrate2;
	}
	else{
		Nwin.x = Rwins[pa].x + xdiff;
	}
	if(Nwin.vl == 1){
		Nwin.w = (Rwins[u].w * hrate1)/ hrate2;
	}
	if(Nwin.t == 1){
		Nwin.y = Rwins[pa].y + (ydiff * vrate1) / vrate2;
	}
	else{
		Nwin.y = Rwins[pa].y + ydiff;
	}
	if(Nwin.hl == 1){
		Nwin.h = (Rwins[u].h * vrate1) / vrate2;
	}
	for(int v: G[u]){
		DFS(G, v, u);
	}	
}

int main(){
	int caseN = 1;
	int nwin, nresize, owidth, oheight;
	while(cin >> nwin >> nresize >> owidth >> oheight){
		if(nwin == 0 && nresize == 0 && owidth == 0 && oheight == 0){
			break;
		}
		wins.resize(nwin+1);
		vector<int> onlyY;
		vector<event> Events;
		wins[0].x = 0, wins[0].y = 0, wins[0].w = owidth, wins[0].h = oheight;
		wins[0].vl = wins[0].hl = wins[0].t = wins[0].b = wins[0].l = wins[0].r = -1;
		for(int i = 1; i <= nwin; i++){
			cin >> wins[i].x >> wins[i].y >> wins[i].w >> wins[i].h >> wins[i].vl >> wins[i].hl >> wins[i].t >> wins[i].b >> wins[i].l >> wins[i].r;
			wins[i].id = i;
int y = wins[i].y, x = wins[i].x, w = wins[i].w, h = wins[i].h;
			onlyY.eb(y);
			onlyY.eb(y+h);
			Events.eb(x, y, y + h,i , 0);
			Events.eb(x + w, y, y + h, i, 1);
		}
		onlyY.eb(0);
		onlyY.eb(oheight);
		sort(al(onlyY));
		onlyY.resize(distance(onlyY.begin(), unique(al(onlyY))));	
		sort(al(Events));
		for(event& e: Events){
			e.ly = (distance(onlyY.begin(), lower_bound(al(onlyY), e.ly)));
			e.ry = (distance(onlyY.begin(), lower_bound(al(onlyY), e.ry)));
		}
		vector<vector<int>> myG(nwin + 1);
		int oh =  (distance(onlyY.begin(), lower_bound(al(onlyY), oheight)));
		BuildG(Events, myG, oh);			
		for(int i = 0; i < nresize; i++){
			int wr, hr;
			cin >> wr >> hr;
			Rwins = wins;
			Rwins[0].w = wr, Rwins[0].h = hr;
			for(int u: myG[0])
				DFS(myG, u, 0);
			cout << "Case " << caseN << ", resize operation " << i+1 << ":\n"; 
			for(int j = 1; j <= nwin; j++)
				cout << "    " << Rwins[j] << endl;
		}
		caseN++;
	}
	return 0;
}
