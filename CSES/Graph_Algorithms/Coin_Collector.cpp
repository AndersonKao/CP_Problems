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


// by atsushi
// sccID[u] will be a REVERSED topological sort order of each SCC
struct tarjan_for_SCC{
    vector<vector<int>> G; // adjacency list
    vector<int> dfn;
    vector<int> low;
    vector<int> sccID;
    stack<int> st; // for SccID
    vector<bool> inSt;
    vector<vector<int>> conG; // contracted graph
    int Time, sccNum;
    void init(int n = 1){ // 1-base
        n++;
        G.assign(n, vec<int>());
        dfn.assign(n, 0);
        low.assign(n, 0);
        sccID.assign(n, 0);
        inSt.assign(n, false);
        while(!st.empty())
            st.pop();
        conG.clear();
        sccNum = Time = 0;
    }
    void addEdge(int from, int to){
        G[from].eb(to);
    }
    void dfs(int u){ //call DFS(u) for all unvisited vertex 
        dfn[u] = low[u] = ++Time; //timestamp > 0
        st.push(u);
        inSt[u] = true;

        for(int v: G[u]){ 
            if(!dfn[v]){ // dfn[v] = 0 if not visited
                dfs(v);
                low[u] = min(low[u], low[v]);
            }else if(inSt[v])
            { /* v has been visited.
                if we don't add this, the low[u] will think that u can back to node whose index less to u.
                inSt[v] is true that u -> v is a cross edge
                opposite it's a forward edge
            */
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(dfn[u] == low[u]){
            int v;
            sccNum++;
            do{
                v = st.top(), st.pop();
                sccID[v] = sccNum, inSt[v] = false;
            } while (v != u);
        }
    }
    // generate induced graph.
    void generateReG(){
        conG.assign(sccNum+1, vec<int>());
        for (int u = 1; u < G.size(); u++){
            for(int v: G[u]){
                if(sccID[u] == sccID[v])
                    continue;
                conG[sccID[u]].emplace_back(sccID[v]);
            }
        }
    }
};
const int maxn = 100000;
ll val[maxn+1];
ll ccval[maxn+1];
int main(){

	yccc;		
	int n, m;
	cin >> n >> m;
	tarjan_for_SCC mG;
	mG.init(n);

	for(int i = 1 ;i <= n; i++){
		cin >> val[i];
	}

	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		mG.addEdge(u, v);
	}
	
	for(int u = 1 ; u <= n; u++){
		if(mG.dfn[u] == 0){
			mG.dfs(u);
		}
	}

	mG.generateReG();
	for(int u = 1 ;u <= n; u++){
//////////////////		cout << mG.sccID[u] << endl;
		ccval[ mG.sccID[u] ] += val[u];
	}

	vec<ll> dp(mG.sccNum + 1, 0);
	ll ans = 0;
	for(int u = 1; u <= mG.sccNum; u++){
		dp[u] = ccval[u];
		for(int v: mG.conG[u]){
			dp[u] = max(dp[u], dp[v] + ccval[u]);			
		}
		ans = max(ans, dp[u]);
//		cout << dp[u] << endl;
	}

	cout << ans << endl;

	return 0;
}

