#include <bits/stdc++.h>
using namespace std;
#define MAX_N 200005;
#define enp pair<int, int> // edge-weight, node-index
#define con pair<int, int> // connection

struct tarjan{
    vector<vector<int>> G; // adjacency List
    vector<int> D;  // visit or visited and D-value
    vector<int> L;  // for L-value
    vector<con> edgeBridge;
    vector<int> APnode;
	vector<int> isAPnode;
    int timestamp;
    tarjan(int size = 1){
			init(size);
    }
    void init(int size = 1){
        timestamp = 1;
				G.clear();
				D.clear();
				L.clear();
        G.resize(size);
        D.resize(size, 0);
        L.resize(size, 0);
        edgeBridge.clear();
        APnode.clear();
				isAPnode.clear();
				isAPnode.resize(size, 0);
    }
    void addedge(int u, int v)
    {   // undirected graph
        G[u].push_back(v);
        G[v].push_back(u);
    }
    void DFS(int v, int pa){ // init: call DFS(v,v)
        D[v] = L[v] = timestamp++;
        int Childcount = 0;
        bool isAP = false;
        for(int w: G[v]){
            if(w == pa)
                continue;
            if(!D[w]){ // 用 D[w] == 0 if not visited
                DFS(w, v);
                Childcount++;
                if(D[v] <= L[w])
                    isAP = true; // 結 論 2 對於除了 root 點以外的所有點 v，v 點在 G 上為 AP 的充要條件為其在 T 中至少有一個子節點 w 滿足 D(v) ≤ L(w)
                if(D[v] < L[w])
                    edgeBridge.emplace_back(v,w);// 結 論 3 對於包含 r 在內的所有點 v 和 v 在 T 中的子節點 w，邊 e(v, w) 在圖 G 中為bridge 的充要條件為 D(v) < L(w)。
                L[v] = min(L[v], L[w]);
            }
            L[v] = min(L[v], D[w]);
        }
        if(v == pa && Childcount < 2)
            isAP = false;
        if(isAP){
            APnode.emplace_back(v);
						isAPnode[v] = true;
				}
    }
};
#define eb emplace_back
#define debug(x) cout << #x << ": " << x << endl;
#define al(x) x.begin(), x.end()
#define F first
#define S second
#define depii(x) cout << "(" << x.first << ", " << x.second << ")" << endl;
#define debug(x) cout << #x << ": " << x << endl;
using pii = pair<int, int>;
vector<int> vis;
vector<int> ccID;
int touch;
int myDFS(tarjan& mTar, int u, int id){
	vis[u] = true;
	ccID[u] = id;
	int ans = 1;
	for(int v: mTar.G[u]){
		if(vis[v])
			continue;
		if(mTar.isAPnode[v]){
			if(touch == -1){
				touch = v;
			}
			else if(touch != v){
				touch = -2;
			}
			continue;
		}
		ans += myDFS(mTar, v, id);
	}
	return ans ;
}
int main(){
	int N;
	int caseN = 1;
	while(cin >> N){
		if(N == 0)break;
		vector<pii> edges(N);
		int Nnum = 0;
		for(int i = 0; i < N; i++){
			cin >> edges[i].F >> edges[i].S;
			Nnum = max(Nnum, max(edges[i].F, edges[i].S));
			edges[i].F--, edges[i].S--;
		}
		tarjan mTar(Nnum);
		for(pii&e : edges){
			mTar.addedge(e.F, e.S);
		}
		mTar.DFS(0, 0);
#ifdef Dtar
		cout << "APnodes: ";
		for(int i = 0; i < mTar.APnode.size(); i++){
			cout << mTar.APnode[i] << " ";
		}
		cout << endl;
#endif
		vis.clear(), vis.resize(Nnum, 0);
		ccID.clear(), ccID.resize(Nnum, -1);
		int curID = 0;
		long long ans = 0;
		long long sizeans = 1;
		for(int u = 0; u < Nnum; u++){
			if(vis[u] == 0 && mTar.isAPnode[u] == false){
				touch = -1;
				long long mySize = myDFS(mTar, u, curID);
				if(touch != -2){
//					debug(touch[curID]);
					ans++;
					sizeans  *= mySize;
				}
				curID++;
			} 
		}
		if(ans == 1){
			ans = 2;
			sizeans = (Nnum * ((long long)Nnum - 1)) / 2;
		}
		cout << "Case " << caseN++ << ": " << ans << " " << sizeans << endl;
	}
	return 0;
}
