#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxn = 1001;
struct edge
{
    int u, v;
    bool is_bridge;
    edge(int u = 0, int v = 0) : u(u), v(v), is_bridge(0) {}
};
int n, m;
vector<int> G[maxn]; // 1-base
vector<edge> E;
vector<int> nG[maxn], bcc[maxn];
int low[maxn], dfn[maxn], Time;
int bcc_id[maxn], bridge_cnt, bcc_cnt; // 1-base
bool is_cut[maxn];         // whether is av
bool cir[maxn];
int st[maxn], top;
int fG[maxn][maxn];

inline void bcc_init(int n)
{
    Time = bcc_cnt = bridge_cnt = top = 0;
    E.clear();
    for (int i = 1; i <= n; ++i)
    {
		fill(fG[i], fG[i]+n+1, 0);
        G[i].clear();
        dfn[i] = 0;
        bcc_id[i] = 0;
		is_cut[i] = 0;
    }
}

inline void add_edge(int u, int v)
{
    G[u].push_back(E.size());
    G[v].push_back(E.size());
    E.push_back(edge(u, v));
}

void dfs(int u, int pa = -1)// call dfs(u) for all unvisited node
{ 
    int child = 0;
    low[u] = dfn[u] = ++Time;
    st[top++] = u;
    for (int eid : G[u])
    {
        int v = E[eid].u ^ E[eid].v ^ u;
        if (!dfn[v])
        {
            dfs(v, u), ++child;
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v])
            {
                is_cut[u] = true; // 結 論 2 對於除了 root 點以外的所有點 v，v 點在 G 上為 AP 的充要條件為其在 T 中至少有一個子節點 w 滿足 dfn(v) ≤ low(w)
                // getting bcc
                bcc[++bcc_cnt].clear();
                int t;
                do
                {
                    bcc_id[t = st[--top]] = bcc_cnt;
                    bcc[bcc_cnt].push_back(t);
                } while (t != v);
                bcc_id[u] = bcc_cnt;
                bcc[bcc_cnt].eb(u);
            }

            if (dfn[u] < low[v])// 結 論 3 對於包含 r 在內的所有點 v 和 v 在 T 中的子節點 w，邊 e(v, w) 在圖 G 中為bridge 的充要條件為 dfn(v) < low(w)。
            {
                E[eid].is_bridge = 1;
                ++bridge_cnt;
            }
        }
        else if (dfn[v] < dfn[u] && v != pa) // !=pa vary important
            low[u] = min(low[u], dfn[v]);
    }
    if (pa == -1 && child < 2)
        is_cut[u] = false;
}

void bcc_solve(int n)
{
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            dfs(i);
    // block-cut tree
	/*
    for (int i = 1; i <= n; ++i)
        if (is_cut[i])
            bcc_id[i] = ++bcc_cnt, cir[bcc_cnt] = 1;
    for (int i = 1; i <= bcc_cnt && !cir[i]; ++i)
        for (int j : bcc[i])
            if (is_cut[j])
                nG[i].pb(bcc_id[j]), nG[bcc_id[j]].pb(i);
				*/
}
int gcd(int a, int b){
	if(b == 0){
		return a;
	}
	return gcd(b, a% b);
}
int main(){
	yccc;		
	int t;
	cin >> t;
	while(t--){
		cin >> n >> m;		
		bcc_init(n);
		for(int i = 0 ; i < m; i++){
			int u, v;
			cin >> u >> v;
			add_edge(u, v);
			fG[u][v] = fG[v][u] = 1;
		}
		dfs(1);
		int cutNum = 0;
		
		for(int u = 1; u <= n; u++){
			if(is_cut[u]) cutNum++;
		}
		int q = 0;
		int p = bcc_cnt;
		for(int i = 1; i <= bcc_cnt; i++){
			int tmp = 0;
//			cout << "bcc " << i << ": ";
			for(int v: bcc[i]){
//				cout << v << " ";
				for(int u: bcc[i]){
					if(u == v) continue;
					if(fG[u][v]) tmp++;
				}
			}
//			cout << endl;
			q = max(q, tmp >> 1);	
		}
		int g = gcd(p, q);
		p /= g;
		q /= g;
		cout << cutNum << " " << bridge_cnt << " " << p << " " << q << endl;
	}

	return 0;
}

