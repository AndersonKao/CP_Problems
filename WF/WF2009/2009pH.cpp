#include <bits/stdc++.h>
using namespace std; 
#define eb emplace_back
vector<vector<int>> G;
vector<vector<int>> reG;
vector<int> sccID;
vector<vector<int>> sccG;
int sccV = 0;
void addEdge(int u, int v){
	G[u].eb(v);
	reG[v].eb(u);
}
vector<bool> vis;
stack<int> st;
void dfs(vector<vector<int>>* nowG, int u){
	vis[u] = true;
	for(int& v: (*nowG)[u]){
		if(vis[v] == false){
			dfs(nowG, v);	
		}
	} 
	if(nowG == &G){
		st.push(u);
	}
	else
		sccID[u] = sccV;
}
void kosaraju(){
	vis.resize(G.size());
	sccID.resize(G.size());
	fill(vis.begin(), vis.end(), false);
	for(int u = 0; u < G.size(); u++){
		if(vis[u] == false){
			dfs(&G, u);
		}
	} 
	fill(vis.begin(), vis.end(), false);
	sccV = 0;
	while(st.empty() == false){
		if(vis[st.top()] == false)
			dfs(&reG, st.top());
		st.pop();
		sccV++;
	}
}
int main(){
	int caseN = 1;
	int B, M;
	while(cin >> B >> M){
		if(B == 0 && M == 0)
			break;
		G.clear();	
		G.resize(2*B);
		reG.clear();
		reG.resize(2*B);
		// A -> i, not A -> 100+i.
		for(int i = 0; i < M; i++){
			int k;
			cin >> k;
			vector<int> poll(k);
			vector<char> opin(k);
			for(int j = 0; j < k; j++){
				cin  >> poll[j] >> opin[j];	
				poll[j]--;
			}
			if(k == 1 || k == 2){
				for(int j = 0; j < k; j++){
					if(opin[j] == 'y'){
						addEdge(poll[j]+B, poll[j]);
					}else{
						addEdge(poll[j], poll[j]+B);
					}
				}	
			}
			else {
				for(int j = 0; j < k; j++){
					int nj = poll[j] + B;
					for(int t = j+1; t < k; t++){
						int nt = poll[t] + B;
						if(opin[j] == 'y'){
							if(opin[t] == 'y'){
								addEdge(nj, poll[t]);
								addEdge(nt, poll[j]);
							}else{
								addEdge(nj, nt);
								addEdge(poll[t], poll[j]);
							}	
						}
						else{
							if(opin[t] == 'y'){
								addEdge(poll[j], poll[t]);
								addEdge(nt, nj);
							}else{
								addEdge(poll[j], nt);
								addEdge(poll[t], nj);
							}
						}
					}
				}
			}
		}	
		kosaraju();	
		bool sol = true;
		for(int i = 0; i < B; i++){
			if(sccID[i] == sccID[i+B]){
				sol = false;
			}
		}
		if(sol){
			sccG.clear();
			sccG.resize(sccV,vector<int>(sccV, 0));
			for(int u = 0; u < G.size(); u++){
				for(int &v: G[u]){
					sccG[sccID[u]][sccID[v]] = 1;
				}
			}
			for(int k = 0; k < sccV; k++){
				for(int u = 0; u < sccV; u++){
					for(int v = 0; v < sccV; v++){
						if(sccG[u][k] && sccG[k][v])		
							sccG[u][v] = 1;
					}
				}		
			}
			cout << "Case " << caseN++ << ": ";
			for(int i = 0; i < B; i++){
				int nitoi = sccG[sccID[i+B]][sccID[i]];
				int itoni = sccG[sccID[i]][sccID[i+B]];
				if(itoni == 0 && nitoi == 0){
					cout << '?'; 	
				}
				else if(itoni){
					cout << 'n';
				}
				else{
					cout << 'y';
				}
			}
			cout << endl;
		}
		else{
			cout << "Case " << caseN++ << ": impossible\n";
		}
	}
	return 0;
}
