#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define eb emplace_back
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
int N;
const double eps = 1e-6;
const double disINF = 1e20;
int fcmp(double a, double b){
	if(abs(a-b) < eps)	
		return 0;
	return (a>b) * 2 -1;
}
struct point3d{
	int x, y, z;
	int dx, dy, dz;
	point3d(){}
	point3d(int x, int y, int z, int dx, int dy, int dz):x(x), y(y), z(z), dx(dx), dy(dy), dz(dz){}
};
struct event{
	double t;
	int i, si, j ,sj;
	event(){};
	event(double t, int i, int si, int j, int sj):t(t), i(i), si(si), j(j), sj(sj){}
	bool operator<(const event& e){
		return (t < e.t);
	}
	friend ostream& operator<<(ostream& os, const event& e);
};
ostream& operator<<(ostream& os, const event& e){
	return (os << "t: " << e.t << ", i: " << e.i << " si: " << e.si << " j: " << e.j << " sj: " << e.sj);
}
vector<point3d> pts;
tuple<int, int, int> getcoeff(int x1, int vx1, int x2, int vx2){
	int xoff = (x1 - x2), voff = (vx1 - vx2);
	return make_tuple(voff*voff, 2 * xoff * voff, xoff*xoff);
}
double getdis(int i, int j, double t){
	if(fcmp(t, 0.0) == 0){
		int xoff = (pts[i].x - pts[j].x);
		int yoff = (pts[i].y - pts[j].y);
		int zoff = (pts[i].z - pts[j].z);
		return sqrt(xoff * xoff + yoff*yoff + zoff*zoff);
	}
	double xoff = (pts[i].x + pts[i].dx * t - (pts[j].x + pts[j].dx * t));
	double yoff = (pts[i].y + pts[i].dy * t - (pts[j].y + pts[j].dy * t));
	double zoff = (pts[i].z + pts[i].dz * t - (pts[j].z + pts[j].dz * t));
	return sqrt(xoff * xoff + yoff*yoff + zoff*zoff);
}

void getT(int i, int j, int si, int sj, vector<event>& mT){
	int Lt2 = 0, Lt = 0, Lc = 0;
	int t2, t, c;
	tie(t2, t, c) = getcoeff(pts[i].x, pts[i].dx, pts[si].x, pts[si].dx);
	Lt2 += t2, Lt += t, Lc += c; 
	tie(t2, t, c) = getcoeff(pts[i].y, pts[i].dy, pts[si].y, pts[si].dy);
	Lt2 += t2, Lt += t, Lc += c; 
	tie(t2, t, c) = getcoeff(pts[i].z, pts[i].dz, pts[si].z, pts[si].dz);
	Lt2 += t2, Lt += t, Lc += c; 
	int Rt2 = 0, Rt = 0, Rc = 0;
	tie(t2, t, c) = getcoeff(pts[j].x, pts[j].dx, pts[sj].x, pts[sj].dx);
	Rt2 += t2, Rt += t, Rc += c; 
	tie(t2, t, c) = getcoeff(pts[j].y, pts[j].dy, pts[sj].y, pts[sj].dy);
	Rt2 += t2, Rt += t, Rc += c; 
	tie(t2, t, c) = getcoeff(pts[j].z, pts[j].dz, pts[sj].z, pts[sj].dz);
	Rt2 += t2, Rt += t, Rc += c; 
	int A = (Rt2 - Lt2), B = (Rt - Lt), C = (Rc - Lc);
	double T1 = (-B + sqrt(B*B - 4*A*C)) / (2*A);
	double T2 = (-B - sqrt(B*B - 4*A*C)) / (2*A);
	if(isnan(T1) == false && fcmp(T1, 0.0) > 0){
		mT.eb(T1, i, si, j , sj);
	}
	if(isnan(T2) == false && fcmp(T2, 0.0) > 0){
		mT.eb(T2, i, si, j , sj);
	}
}

void DFS(int u, int pa, vector<vector<int>>& pG){
	debug(u);
	for(int v: pG[u]){
		if(v == pa) continue;
		DFS(v, u, pG);
	}	
}

void visTree(vector<pii>& edges){
	vector<vector<int>> G(N);		
	for(pii& e: edges){
		G[e.F].eb(e.S);
		G[e.S].eb(e.F);
	}
	DFS(0, 0, G);
}

int main(){
	while(cin >> N){
		pts.resize(N);
		for(int i = 0; i < N; i++){
			cin >> pts[i].x >> pts[i].y >> pts[i].z >> pts[i].dx >> pts[i].dy >> pts[i].dz;
		}
		vector<event> mT;
		G.clear(), G.resize(N);
		for(int i = 0; i < N; i++){
			for(int si = i+1; si < N; si++){
				for(int j = 0; j < N; j++){
					for(int sj = j+1; sj < N; sj++){
						if(i == j && si == sj) continue;
							getT(i, j, si, sj, mT); 	
					}
				}
			}
		}
		vector<vector<int>> Eused(N, vector<int>(N, 0));
		vector<bool> used(N, false);
		vector<int> pa(N, -1);
		vector<double> dis(N, disINF);
		vector<vector<int>> G(N);
		vector<pii> edges;
		dis[0] = 0.0;
		pa[0] = 0;
		int cnt = 0;
		while(cnt < N){
			int mi = -1;
			double mdis = disINF;
			for(int i = 0; i < N; i++){
				if(used[i]) continue;
				if(mdis > dis[i]){
					mdis = dis[i];
					mi = i;
				}
			}
			used[mi] = true;
			G[pa[mi]].eb(mi);
			edges.eb(mi, pa[mi]);
			G[mi].eb(pa[mi]);
			Eused[pa[mi]][mi] = Eused[mi][pa[mi]] = 0;
			cnt++;
			for(int i = 0; i < N; i++){
				if(used[i]) continue;	
				double curdis = getdis(mi, i, 0.0);
				if(fcmp(dis[i], curdis) < 0){
					dis[i] = curdis;
					pa[i] = mi;
				} 
			}
		}
		for(event& e: mT){
			cout << e << endl;						
		}
	}
	return 0;
}
