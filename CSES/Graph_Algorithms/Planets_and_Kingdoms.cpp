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
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;

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
        G.clear();
        G.resize(N);
        GT.clear();
        GT.resize(N);
        while(!st.empty())
            st.pop();
        visited.clear();
        visited.resize(N, false);
        scc.clear();
        scc.resize(N);
        sccNum = 0;
    }
    void addEdge(int u, int v){
        G[u].emplace_back(v);
        GT[v].emplace_back(u);
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
	int n, m;
	cin >> n >> m;
	Kosaraju mK;
	mK.init(n);
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		mK.addEdge(u-1, v-1);
	}
	mK.run();
	cout << mK.sccNum << endl;
	for(int u = 0; u < n; u++){
		cout << mK.scc[u] + 1 << " ";
	}
		
	return 0;
}

