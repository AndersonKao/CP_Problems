#include <bits/stdc++.h>
using namespace std;


#define MAXN 200000
vector<vector<int>> G;

int L[MAXN + 1];
int R[MAXN + 1];

int typer = 1;
void DFS(int u, int p)
{

    L[u] = MAXN;
    R[u] = 0;
    for(auto& v: G[u]){
        if(v == p)
            continue;
        DFS(v, u);
        L[u] = min(L[u], L[v]);
        R[u] = max(R[u], R[v]);
    }
    if(G[u].size() == 1 && p != -1){
        L[u] = R[u] = typer++;
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    G.resize(N + 1);
    int a, b;
    for (int i = 0; i < N-1; i++){
        cin >> a >> b;
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }
    DFS(1, -1);
    for (int i = 1; i <= N; i++){
        cout << L[i] << " " << R[i] << endl;
    }

        return 0;
}