#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using p = pair<T, T>;

struct pt{
	ll x, y;
	pt() {}
	pt(int x,int y):x(x), y(y){};
	friend ostream& operator<<(ostream& os, const pt& p);
};

ostream& operator<<(ostream& os,const pt& p){
	return (os << "(" << p.x << ", " << p.y << ")");
}

struct edge{
	pt st,ed;
	edge(){}
	edge(pt s, pt e){
		st = s, ed = e;
	}
	edge(ll x1, ll y1, ll x2, ll y2):st(x1, y1), ed(x2, y2){

	}
	friend ostream& operator<<(ostream& os, const edge& e);

};
ostream& operator<<(ostream& os, const edge& e){
	return (os << "from " << e.st << " to " << e.ed);
}

struct event{
	int type; // 0 for in , 1 for uquery, 2 for out
	ll x;
	int l, r;
	event(int t, ll x, int l ,int r):type(t), x(x), l(l), r(r){

	}
};
#define LC(x) (2*x+1)
#define RC(x) (2*x+2)
struct segT{
	vector<ll> seq;
	int n;
	void Build(int n){
		seq.resize(4*n, 0);
		fill(al(seq), 0);
		this->n = n;
	}
	ll Query(int l, int r){
		if(r < l)
			return 0;
		return query(l, r, 0, n-1, 0);
	}
	ll query(int l, int r ,int L, int R, int idx){
		if(R < l || r < L)
			return 0;
		if(l <= L && R <= r){
			return seq[idx];
		}
		int M = (L+R) >> 1;
		return query(l, r, L, M, LC(idx)) + query(l, r, M+1, R, RC(idx));
	}

	void Modify(int i, int val){
		modify(0, n-1, i, 0, val);
	}
	void modify(int L, int R, int i, int idx, int val){
		if(L == R){
			seq[idx] += val;
			return;
		}
		int M = (L+R) >> 1;
		if(i <= M){
			modify(L, M, i, LC(idx), val);
		}
		else{
			modify(M+1, R, i,RC(idx), val);
		}
		seq[idx] = seq[LC(idx)] + seq[RC(idx)];
	}

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

	ll k;
   int	n, m;
	cin >> k >> n >> m;
	vector<ll> turnA(n+2, 0), turnB(m+2, 0);
	vector<edge> eA[2]; // 0 for hori, 1 for verti
	vector<edge> eB[2]; // 0 for hori, 1 for verti
	pt curA(0, 1), curB(1, 0);
	bool Aright = true, Bright = false;
	for(int i = 1; i <= n+1; i++){
		if(i == n+1)
			turnA[i] = k+1;
		else
			cin >> turnA[i];
		pt next = curA;
		if(Aright){
			next.x += (turnA[i] - turnA[i-1]);
			eA[0].eb(curA, next); 
		}
		else{
			next.y += (turnA[i] - turnA[i-1]);
			eA[1].eb(curA, next); 
		}
		curA = next;
		Aright = !Aright;
	}
	for(int i = 1; i <= m+1; i++){
		if(i == m+1)
			turnB[i] = k+1;
		else
			cin >> turnB[i];
		pt next = curB;
		if(Bright){
			next.x += (turnB[i] - turnB[i-1]);
			eB[0].eb(curB, next); 
		}
		else{
			next.y += (turnB[i] - turnB[i-1]);
			eB[1].eb(curB, next); 
		}
		curB = next;
		Bright = !Bright;
	}
#ifdef Dedge
	for(int j = 0; j < 2; j++){
		debug(j);
		for(edge& e: eA[j]){
			cout << e << endl;	
		}
	}
	for(int j = 0; j < 2; j++){
		debug(j);
		for(edge& e: eB[j]){
			cout << e << endl;	
		}
	}
#endif
	ll ans = 0;
	int sta = 0, stb = 0;	
	while(sta < eA[0].size() && stb < eB[0].size()){
		if(eA[0][sta].st.y < eB[0][stb].st.y){
			sta++;
			continue;
		}
		if(eA[0][sta].st.y > eB[0][stb].st.y){
			stb++;
			continue;
		}
		ll l = max(eA[0][sta].st.x, eB[0][stb].st.x);
		ll r = min(eA[0][sta].ed.x, eB[0][stb].ed.x);
		if(l < r){
			ans += ((r - l));	
		}
		sta++, stb++;
	}
#ifdef Dans
	debug(ans);
#endif
	
	sta = 0, stb = 0;	
	while(sta < eA[1].size() && stb < eB[1].size()){
		if(eA[1][sta].st.x < eB[1][stb].st.x){
			sta++;
			continue;
		}
		if(eA[1][sta].st.x > eB[1][stb].st.x){
			stb++;
			continue;
		}
		ll l = max(eA[1][sta].st.y, eB[1][stb].st.y);
		ll r = min(eA[1][sta].ed.y, eB[1][stb].ed.y);
		if(l < r){
			ans += ((r - l));	
		}
		sta++, stb++;
	}
#ifdef Dans
	debug(ans);
#endif
	eA[0][0].st = pt(1,1);
	eB[1][0].st = pt(1,1);
	vector<ll> onlyY;
	for(edge&e: eA[0]){
		e.st.x += 1;
		onlyY.eb(e.st.y);
	}
	for(edge&e: eA[1]){
		e.st.y += 1;
		onlyY.eb(e.st.y);
		onlyY.eb(e.ed.y);
	}
	for(edge&e: eB[0]){
		e.st.x += 1;
		onlyY.eb(e.st.y);
	}
	for(edge&e: eB[1]){
		e.st.y += 1;
		onlyY.eb(e.st.y);
		onlyY.eb(e.ed.y);
	}
	sort(al(onlyY));
	onlyY.resize(distance(onlyY.begin(), unique(al(onlyY))));
	vector<event> eq;

	segT mT;
	auto cmp = [](event&a, event&b){
		if(a.x != b.x)
			return a.x < b.x;
		return a.type < b.type;
	};

	for(edge&e: eA[0]){
		int sty = lower_bound(al(onlyY), e.st.y) - onlyY.begin();
		int edy = lower_bound(al(onlyY), e.ed.y) - onlyY.begin();
		eq.eb(0, e.st.x, sty, sty);
		eq.eb(2, e.ed.x, edy, edy);
	}
	for(edge&e: eB[1]){
		int sty = lower_bound(al(onlyY), e.st.y) - onlyY.begin();
		int edy = lower_bound(al(onlyY), e.ed.y) - onlyY.begin();
		eq.eb(1, e.st.x, sty, edy);
	}

	mT.Build(onlyY.size()+5);
	sort(al(eq), cmp);
	for(event& e: eq){
		if(e.type == 0){
			mT.Modify(e.l, 1);
		}	
		else if(e.type == 1){
			ans += mT.Query(e.l, e.r);
		}
		else{
			mT.Modify(e.l, -1);
		}
	}
#ifdef Dans
	debug(ans);
#endif

	eq.clear();
	
	for(edge&e: eB[0]){
		int sty = lower_bound(al(onlyY), e.st.y) - onlyY.begin();
		int edy = lower_bound(al(onlyY), e.ed.y) - onlyY.begin();
		eq.eb(0, e.st.x, sty, sty);
		eq.eb(2, e.ed.x, edy, edy);
	}
	for(edge&e: eA[1]){
		int sty = lower_bound(al(onlyY), e.st.y) - onlyY.begin();
		int edy = lower_bound(al(onlyY), e.ed.y) - onlyY.begin();
		eq.eb(1, e.st.x, sty, edy);
	}
	mT.Build(onlyY.size()+5);

	sort(al(eq), cmp);

	for(event& e: eq){
		if(e.type == 0){
			mT.Modify(e.l, 1);
		}	
		else if(e.type == 1){
			ans += mT.Query(e.l, e.r);
		}
		else{
			mT.Modify(e.l, -1);
		}
	}

#ifdef Dans
	debug(ans);
#endif
	cout << k - ans << " " << k - ans << " " << ans;

	return 0;
}
