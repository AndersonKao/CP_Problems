// AC 2022-02-22 04:12:42
#include <bits/stdc++.h>
using namespace std;

int T;

vector<vector<int>> G;
bool visited[200001];
bool solved = false;
int repeat;
stack<int> Scopy;
void DFS(int u, int p, stack<int> &S){
    visited[u] = true;
    if(solved)
        return;
    for(auto &v: G[u]){
        if(v == p)
            continue;
        if(visited[v]){
            solved = true;
            Scopy = S;
            repeat = v;
            return;
        }
        S.emplace(v);
        DFS(v, u, S);
        S.pop();
        if(solved)
            break;
    }
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N;

    G.resize(N + 1);
    cin >> M;
    int u, v;
    fill(visited, visited + N + 1, false);
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    stack<int> S;
    for (int i = 1; i <= N; i++){
        if(!visited[i]){
            S.emplace(i);
            DFS(i, -1, S);
            S.pop();
            if(solved)
                break;
        }
    }
    if(solved){ 
        while(!S.empty()){
            S.pop();
        }
        while(!Scopy.empty() && Scopy.top() != repeat){
            S.emplace(Scopy.top());
            Scopy.pop();
        }
        cout << S.size() + 2 << endl;
        cout << repeat << " ";
        while(!S.empty() && S.top() != repeat){
            cout  << S.top()<< " ";
            S.pop();
        }
        cout << repeat;
        cout << endl;
    }
    else {
        cout << "IMPOSSIBLE\n";
    }
    return 0;
}