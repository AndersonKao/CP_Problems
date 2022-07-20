// AC 2022-07-18 21:43:09
#include <utility>
#include <bits/stdc++.h>
using namespace std;

#define debug(x) cout << #x << ": " << x << endl;
#define F first
#define S second
using pii = pair<int, int>;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
using ll = long long;
const ll disINF = 2000000000000;
int R, C;
inline int toid(int r, int c){
	return r * C + c; 
}
using status = tuple<ll, int, int, int>;// dis, r, c, direc
pii vec[4] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
};
int main(){
	int caseN = 1;
	pii st, ed;
	while(cin >> R >> C >> st.F >> st.S >> ed.F >> ed.S) {
		st.F--, st.S--, ed.F--, ed.S--;
		if(R == 0 && C == 0)
			break;
		vector<vector<ll>> G(R * C, vector<ll>(R * C, disINF));
		for(int i = 0; i < R; i++){
			for(int j = 0; j < C-1; j++){
				int Fid =toid(i, j);
				int Tid =toid(i, j+1);
				ll w;
				cin >> w;
				if(w != 0)
					G[Tid][Fid] = G[Fid][Tid] = w;
			}
			if(i == R-1)
				break;	
			for(int j = 0; j < C; j++){
				int Fid =toid(i, j);
				int Tid =toid(i + 1, j);
				ll w;
				cin >> w;
				if(w != 0)
					G[Tid][Fid] = G[Fid][Tid] = w;
			}
		}	
/*
		REP(i, R*C){
			G[i][i] = 0;
		}
*/
		vector<vector<vector<ll>>> dis(R, vector<vector<ll>>(C, vector<ll>(8, disINF)));
		priority_queue<status, vector<status>, greater<status>> pq;
		REP(i, 8){
//			dis[st.F][st.S][i] = 0;
			pq.emplace(0, st.F, st.S, i);
		}
		bool start = true;
		while(!pq.empty()){
			int ri, ci, di;
			ll idis;
			tie(idis, ri, ci, di) = pq.top();
			if(start){
				if(ri != st.F || ci != st.S)
					start = false;
			}
			pq.pop();
#ifdef Dgrep
			printf("grep %ld %d %d %ld\n", idis, ri, ci, di);
#endif
			if(start == false && idis != dis[ri][ci][di])
				continue;	
			if((di & 1) == 0){ // not going to make turn
					int i = (di >> 1);
					pii to(ri + vec[i].F, ci + vec[i].S);
					if(to.F >= R || to.F < 0 || to.S >= C || to.S < 0)
//					if(Tid >= R*C || Tid < 0 || Fid >= R*C || Fid < 0)
						continue;
					int Fid =toid(ri, ci);
					int Tid =toid(to.F, to.S);
					ll w = G[Fid][Tid];
					REP(j, 2) { // turn or not
						int twice = 2;
						int id = di + j;
						if(j == 0)
							twice = 1;
						if(to == ed || start)
							twice = 2;
						if(dis[to.F][to.S][id] > idis + twice * w){
							pq.emplace(dis[to.F][to.S][id] = idis + twice * w, to.F, to.S, id);
#ifdef Drelax							
							printf("relax %ld, %ld, %ld, %ld\n", dis[to.F][to.S][id], to.F, to.S, id);
#endif
						}	
					}
			}
			else{
				for(int i = 0; i <= 3; i++){ // direc
					if((di >> 1) == i)
						continue;
					pii to(ri + vec[i].F, ci + vec[i].S);
					if(to.F >= R || to.F < 0 || to.S >= C || to.S < 0)
					//if(Tid >= R*C || Tid < 0 || Fid >= R*C || Fid < 0)
						continue;
					int Fid =toid(ri, ci);
					int Tid =toid(to.F, to.S);
					ll w = G[Fid][Tid];
					for(int j = 0; j <= 1; j++){ // turn or not
						int id = (i << 1) + j;
						int twice = 2;
						if(dis[to.F][to.S][id] > idis + twice * w){
							pq.emplace(dis[to.F][to.S][id] = idis + twice *w, to.F, to.S, id);
#ifdef Drelax							
							printf("relax %ld, %ld, %ld, %ld\n", dis[to.F][to.S][id], to.F, to.S, id);
#endif
						}	
					}
				}
			}
		}
		ll ans = disINF;
		REP(i, 8){
			ans = min(ans, dis[ed.F][ed.S][i]);
		}	
		cout << "Case " << caseN++ << ": ";
		if(ans == disINF)
			cout << "Impossible\n";
		else
		 	cout << ans << endl;
	}
	return 0;
}
