#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, treeorder_statistics_node_update>;
*/
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define ln '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;

// scc[u] will be a topological sort order of each SCC
struct Kosaraju{
    int NodeNum;
    vector<vector<int>> G;
    vector<vector<int>> GT;
    stack<int> st;
    vector<bool> visited;
    vector<int> scc;
    int sccNum;

    void init(int N){
        NodeNum = N;
        G.assign(N, vec<int>());
        GT.assign(N, vec<int>());
        while(!st.empty())
            st.pop();
        visited.assign(N, false);
        scc.assign(N, 0);
        sccNum = 0;
    }
    void addEdge(int u, int v){
        G[u].eb(v);
        GT[v].eb(u);
    }
    void DFS(bool isG, int u, int sccID = -1){
        visited[u] = true;
        vector<vector<int>> &dG = (isG ? G : GT);
        for(int v: dG[u])
        {
            if(!visited[v]){
                DFS(isG, v, sccID);
            }
        }
        if(isG){
            st.push(u);
        }
        else{
            scc[u] = sccID;
        }
    }
    void run(){
        fill(al(visited), false);
        for (int i = 0; i < NodeNum; i++){
            if(!visited[i])
                DFS(true, i);
        }
        fill(al(visited), false);
        while(!st.empty()){
            if(!visited[st.top()])
                DFS(false, st.top(), sccNum++);
            st.pop();
        }
    }

    vector<vector<int>> reduceG(){ //call after run
        vector<vector<int>> reG;
        reG.resize(sccNum);
        for (int i = 0; i < NodeNum; i++){
            for(int w: G[i]){
               if(scc[i] == scc[w])
                   continue;
               reG[scc[i]].emplace_back(scc[w]);
            }
        }
        return reG;
    }
};
int main(){
	yccc;		
	int n, m;
	cin >> n >> m;
	Kosaraju SCC;
	SCC.init(n);
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		SCC.addEdge(u-1, v-1);
	}
	SCC.run();
	
	if(SCC.sccNum == 1){
		cout << "YES\n";
	}
	else{
		cout << "NO\n";
		int sccid = SCC.scc[0];
		for(int u = 1; u < n; u++){
			if(SCC.scc[u] < sccid){
				cout << "1 " << u+1 << endl;
				break;
			}
			else if(SCC.scc[u] > sccid){
				cout << u+1 << "1 " << endl;
				break;
			}
		}
			
	}


	return 0;
}

