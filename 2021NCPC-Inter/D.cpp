//AC
#include <bits/stdc++.h>

//#define RANDTEST
#ifdef RANDTEST
#include <windows.h>
#endif
using namespace std;
// Max weight perfect bipartite matching
// O(V^3)
#define MAXN 505
#define INF 0x3f3f3f3f3f3f3f3f
#define LL long long
int n;// 1-base，0表示沒有匹配 
LL g[MAXN][MAXN]; //input graph
int My[MAXN],Mx[MAXN]; //output match
LL lx[MAXN],ly[MAXN],pa[MAXN],Sy[MAXN];
bool vx[MAXN],vy[MAXN];
void augment(int y){
	for(int x, z; y; y = z){
		x=pa[y],z=Mx[x];
		My[y]=x,Mx[x]=y;
	}
}
void bfs(int st){
	for(int i=1; i<=n; ++i)
		Sy[i] = INF, vx[i]=vy[i]=0;
	queue<int> q; q.push(st);
	for(;;){
		while(q.size()){
			int x=q.front(); q.pop();
			vx[x]=1;
			for(int y=1; y<=n; ++y) if(!vy[y]){
				LL t = lx[x]+ly[y]-g[x][y];
				if(t==0){
					pa[y]=x;
					if(!My[y]){augment(y);return;}
					vy[y]=1,q.push(My[y]);
				}else if(Sy[y]>t) pa[y]=x,Sy[y]=t;
			}
		}
		LL cut = INF;
		for(int y=1; y<=n; ++y)
			if(!vy[y]&&cut>Sy[y]) cut=Sy[y];
		for(int j=1; j<=n; ++j){
			if(vx[j]) lx[j] -= cut;
			if(vy[j]) ly[j] += cut;
			else Sy[j] -= cut;
		}
		for(int y=1; y<=n; ++y){
			if(!vy[y]&&Sy[y]==0){
				if(!My[y]){augment(y);return;}
				vy[y]=1, q.push(My[y]);
			}
		}
	}
}
LL KM(){
	memset(My,0,sizeof(int)*(n+1));
	memset(Mx,0,sizeof(int)*(n+1));
	memset(ly,0,sizeof(LL)*(n+1));
	for(int x=1; x<=n; ++x){
		lx[x] = -INF;
		for(int y=1; y<=n; ++y)
			lx[x] = max(lx[x],g[x][y]);
	}
	for(int x=1; x<=n; ++x) bfs(x);
	LL ans = 0;
	for(int y=1; y<=n; ++y) ans+=g[My[y]][y];
	return ans;
}
#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
int main(){
    yccc;
#ifdef RANDTEST
    DWORD star_time = GetTickCount();
#endif
#ifndef RANDTEST
    cin >> n;
#endif
#ifdef RANDTEST
    srand(time(NULL));
    n = 500;
#endif
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++)
        {
            int cost;
#ifndef RANDTEST
    cin >> cost;
#endif
#ifdef RANDTEST 
            cost = rand()%500 + 1;
#endif
            g[i][j] = 500 - cost;
        }
    }
    LL reverseans = KM();
    //cout << reverseans << endl;
    cout << 500 * n - reverseans << endl;
#ifdef RANDTEST
    DWORD end_time = GetTickCount();
    cout << "end_time: " << (end_time-star_time)<< endl;
#endif

    return 0;
}