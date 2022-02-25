#include <bits/stdc++.h>
using namespace std;

vector<int> G[100];
int indeg[100];
bool visited[100];
bool inStack[100];
void topo(vector<int>& ans, int N){
    ans.clear();
    int cur;
    queue<int> Q;
    for (int i = 0; i < N; i++){
        if(indeg[i] == 0){
            Q.emplace(i);
        }
    }
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        ans.emplace_back(u);
        for(auto &v: G[u]){
            if(--indeg[v] == 0){
                Q.emplace(v);
            }
        }
    }
}
void topodfs(vector<int>& ans, int u, int N){
    visited[u] = true;
    inStack[u] = true;
    for(auto& v: G[u]){
        if(!visited[v]){
            topodfs(ans, v, N);
        }
    }
    ans.emplace_back(u);
    inStack[u] = false;
}
int main(){
    int N, M;
    while(cin >> N >> M){
        if(N == 0 && M == 0)
            break;
        fill(indeg, indeg + N, 0);
        fill(inStack, inStack + N, false);
        fill(visited, visited + N, false);
        for (int i = 0; i < N; i++)
        {
            G[i].clear();
        }
        int u, v;
        for (int i = 0; i < M; i++){
            cin >> u >> v;
            u--, v--;
            G[u].emplace_back(v);
            indeg[v]++;
        }
        vector<int> ans;
        //topo(ans, N);
        for (int i = 0; i < N; i++){
            if(indeg[i] == 0){
                topodfs(ans, i, N);
            }
        }
        for (int i = ans.size() - 1; i >= 0; i--)
        {
            cout << ans[i] + 1 << (i == 0? "\n" : " ");
        }
    }
    return 0;
}
/*
8 10
7 5
5 4
5 2
2 1
2 6
5 3
3 6
6 8
1 8
4 1
5 4
1 2
2 3
1 3
1 5
0 0
*/