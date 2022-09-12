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
using Iter = vector<int>::iterator;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
int N;
const double eps = 1e-12;
const double teps = 1e-6;
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
	bool operator==(const event& e){
		return (fcmp(t, e.t) == 0 && ((i == e.i && si == e.si && j == e.j && sj == e.sj) || (i == e.j && si == e.sj && j == e.i && sj == e.si))); 
	}
	friend ostream& operator<<(ostream& os, const event& e);
};
ostream& operator<<(ostream& os, const event& e){
	return (os << "t: " << e.t << ", i: " << e.i << " si: " << e.si << " j: " << e.j << " sj: " << e.sj);
}
vector<event> mT;
vector<point3d> pts;
vector<vector<bool>> Eused;
vector<bool> used;
vector<int> pa;
vector<double> dis;
vector<vector<int>> G;

void init(int N){
	mT.clear();
	pts.resize(N);
	Eused.clear();
	Eused.resize(N, vector<bool>(N, false));
	used.resize(N);
	fill(al(used), false);
	pa.resize(N);
	fill(al(pa), -1);
	dis.resize(N);
	fill(al(dis), disINF);
	G.clear();
	G.resize(N);
}

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

void getT(int i, int si, int j, int sj, vector<event>& mT){
#ifdef DgetT
	printf("getT on (%d, %d) and (%d, %d)\n", i, si, j, sj);
#endif
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
	if(isnan(T1) == false  && fcmp(T1, 0.0) > 0){
		mT.eb(T1, i, si, j , sj);
	}
	if(isnan(T2) == false  && fcmp(T2, 0.0) > 0){
		mT.eb(T2, i, si, j , sj);
	}
}

void DFS_printG(int u, int pa, vector<vector<int>>& pG){
	for(int v: pG[u]){
		if(v == pa) continue;
		printf("edge (%d, %d)\n", u, v);
		DFS_printG(v, u, pG);
	}	
}
bool DFS_1(int u, int target, vector<int>& pa){
	if(u == target){
		return true;
	}
	for(int v: G[u]){
		if(v == pa[u]){
			continue;
		}
		pa[v] = u;
		if(DFS_1(v, target, pa)){
			return true;
		}
		pa[v] = -1;
	}
	return false;
}

bool checkCycle(int e_u, int e_v, int add_u, int add_v){
#ifdef DcheckC
	printf("start form %d to %d, try to find (%d, %d)\n", add_u, add_v, e_u, e_v);
#endif
	vector<int> pa_rootu(N, -1); // parent for rooted on add_u.
	bool found = DFS_1(add_u, add_v, pa_rootu);
#ifdef DcheckC
	cout << "current G:\n";
	// check generated MST
	DFS_printG(0, -1, G);
	cout << "tmp route: \n";
	for(int u = 0; u < N; u++){
		cout << u << ": " << pa_rootu[u] << (u == N-1 ? "\n" : " ");
	}
	
	if(found == false){
		cout << "critical error\n";
	}
#endif
	return (pa_rootu[e_u] == e_v || pa_rootu[e_v] == e_u);
}
void EraseEdge(int u, int v){
#ifdef Derase
	printf("erasing (%d, %d)\n", u, v);
#endif
	for(Iter it = G[u].begin(); it != G[u].end(); it++){
		if(*it == v){
			G[u].erase(it);
			break;
		}
	}
	for(Iter it = G[v].begin(); it != G[v].end(); it++){
		if(*it == u){
			G[v].erase(it);
			break;
		}
	}
	Eused[u][v] = Eused[v][u] = false;
}

void AddEdge(int u, int v){
#ifdef Dadd
	printf("adding (%d, %d)\n", u, v);
#endif
	G[u].emplace_back(v);
	G[v].emplace_back(u);
	Eused[u][v] = Eused[v][u] = true;
}

bool checkMST(event& cur){
	double curt = cur.t;
	double pret = curt - teps*2;
	double predis_i = getdis(cur.i, cur.si, pret);
	double predis_j = getdis(cur.j, cur.sj, pret);
#ifdef DcheckM
	cout << "doing  " << cur << endl;
	debug(predis_i);
	debug(predis_j);
#endif
	if(fcmp(predis_i, predis_j) < 0){
#ifdef DcheckM
		cout << "i is shorter\n";
#endif
		if(Eused[cur.i][cur.si] == true && Eused[cur.j][cur.sj] == false){
#ifdef DcheckM
			cout << "correct siutation\n";
#endif
			if(checkCycle(cur.i, cur.si, cur.j, cur.sj)){
#ifdef DcheckM
				cout << "cycle detected\n";
#endif
				EraseEdge(cur.i, cur.si);
				AddEdge(cur.j, cur.sj);
				return true;
			}
		}
	}
	else if(fcmp(predis_i, predis_j) > 0){
#ifdef DcheckM
		cout << "j is shorter\n";
#endif
		if(Eused[cur.i][cur.si] == false && Eused[cur.j][cur.sj] == true){
#ifdef DcheckM
			cout << "correct siutation\n";
#endif
			if(checkCycle(cur.j, cur.sj, cur.i, cur.si)){
#ifdef DcheckM
				cout << "cycle detected\n";
#endif
				EraseEdge(cur.j, cur.sj);
				AddEdge(cur.i, cur.si);
				return true;
			}
		}
	}
	else {
#ifdef DcheckM
		cout << "how could i = j?\n";
#endif
	}
	return false; 
}

int main(){
	cout << fixed << setprecision(10);
	int casen = 1;
	while(cin >> N){
			init(N);
		for(int i = 0; i < N; i++){
			cin >> pts[i].x >> pts[i].y >> pts[i].z >> pts[i].dx >> pts[i].dy >> pts[i].dz;
		}
		// generate all event
	//G.clear(), G.resize(N);
		for(int i = 0; i < N; i++){
			for(int si = i+1; si < N; si++){
				for(int j = 0; j < N; j++){
					for(int sj = j+1; sj < N; sj++){
						if((i == j && si == sj)) continue;
							getT(i, si, j, sj, mT); 	
					}
				}
			}
		}
		sort(al(mT), [](const event& l, const event& r){
			return l.t < r.t;
		});
		mT.resize(distance(mT.begin(), unique(al(mT))));
#ifdef Devent
		for(event& e: mT){
			cout << e << endl;						
		}
#endif

		// generate first MST, using Prim's
		// use array to find min. perform in (V^2).
		dis[0] = 0.0;
		pa[0] = -1;
		int cnt = 0; // how many vertex had been added to MST.
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

			if(pa[mi] != -1){
				G[pa[mi]].eb(mi);
				//edges.eb(mi, pa[mi]);
				G[mi].eb(pa[mi]);
				Eused[pa[mi]][mi] = Eused[mi][pa[mi]] = true;
			}

			cnt++;

			for(int i = 0; i < N; i++){
				if(used[i]) continue;	
				double curdis = getdis(mi, i, 0.0);
				if(fcmp(dis[i], curdis) > 0){
					dis[i] = curdis;
					pa[i] = mi;
				} 
			}
		}

		// check generated MST
#ifdef DMST
		DFS_printG(0, -1, G);
#endif
		int ans = 1;
		for(event&e : mT){
			if(checkMST(e)){
				ans++;
#ifdef Dans
				printf("ans increase %d\n", ans);
#endif
			}
		}
		printf("Case %d: %d\n", casen++, ans);
	}
	return 0;
}
