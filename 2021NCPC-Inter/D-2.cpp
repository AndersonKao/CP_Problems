#include <bits/stdc++.h>
//#include <windows.h>
using namespace std;
#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
template<typename TP>
struct MCMF{
	static const int MAXN=1005;
	static const TP INF=999999999;
	struct edge{
		int v,pre;
		TP r,cost;
		edge(int v,int pre,TP r,TP cost):v(v),pre(pre),r(r),cost(cost){}
	};
	int n,S,T;
	TP dis[MAXN],PIS,ans;
	bool vis[MAXN];
	vector<edge> e;
	int g[MAXN];
	void init(int _n){

		memset(g,-1,sizeof(int)*((n=_n)+1));
		e.clear();
	}
	void add_edge(int u,int v,TP r,TP cost,bool directed=false){
		e.push_back(edge(v,g[u],r,cost));
		g[u]=e.size()-1;
		e.push_back(
		edge(u,g[v],directed?0:r,-cost));
		g[v]=e.size()-1;
	}
	TP augment(int u,TP CF){
		if(u==T||!CF)return ans+=PIS*CF,CF;
		vis[u]=1;
		TP r=CF,d;
		for(int i=g[u];~i;i=e[i].pre){
			if(e[i].r&&!e[i].cost&&!vis[e[i].v]){
				d=augment(e[i].v,min(r,e[i].r));
				e[i].r-=d;
				e[i^1].r+=d;
				if(!(r-=d))break;
			}
		}
		return CF-r;
	}
	bool modlabel(){
		for(int u=0;u<=n;++u)dis[u]=INF;
		static deque<int>q;
		dis[T]=0,q.push_back(T);
		while(q.size()){
			int u=q.front();q.pop_front();
			TP dt;
			for(int i=g[u];~i;i=e[i].pre){
				if(e[i^1].r&&(dt=dis[u]-e[i].cost)<dis[e[i].v]){
					if((dis[e[i].v]=dt)<=dis[q.size()?q.front():S]){
						q.push_front(e[i].v);
					}else q.push_back(e[i].v);
				}
			}
		}
		for(int u=0;u<=n;++u)
			for(int i=g[u];~i;i=e[i].pre)
				e[i].cost+=dis[e[i].v]-dis[u];
		return PIS+=dis[S], dis[S]<INF;
	}
	TP mincost(int s,int t){
		S=s,T=t;
		PIS=ans=0;
		while(modlabel()){
			do memset(vis,0,sizeof(bool)*(n+1));
			while(augment(S,INF));
		}
        return ans;
	}
};

//#define RANDTEST
int main(){
#ifdef RANDTEST
    DWORD star_time = GetTickCount();
#endif
    yccc;
    MCMF<int> mcmf;
    int n;
#ifndef RANDTEST
    cin >> n;
#endif
#ifdef RANDTEST
    srand(time(NULL));
    n = 500;
#endif
    int end = n * 2 + 1;
    mcmf.init(end + 1);
    for (int i = 1; i <= n; i++){
        mcmf.add_edge(i + n, end, 1, 0, true);
        mcmf.add_edge(0, i, 1 , 0, true);
        for (int j = 1; j <= n; j++)
        {
            int cost;
#ifndef RANDTEST
            cin >> cost;
#endif
#ifdef RANDTEST 
            cost = rand()%500 + 1;
#endif
            mcmf.add_edge(i, j + n,1, cost, true);
        }
    }
    int ans = mcmf.mincost(0, end);
    cout << ans << endl;

#ifdef RANDTEST
    DWORD end_time = GetTickCount();
    cout << "end_time: " << (end_time-star_time)<< endl;
#endif
    return 0;
}