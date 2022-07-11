#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define eb emplace_back
template <typename T>
using vec = vector<T>;

vec<vec<int>> G;
vec<vec<int>> disfrom(2);
const int disINF = 500;
int N, M;
void BFS(int st, vec<int>& distance){
    queue<int> Q;
    vec<bool> vis(N, false);
    Q.emplace(st);
    vis[st] = true;
    distance[st] = 0;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for(int &v : G[u]){
            if(vis[v] == false){
                distance[v] = distance[u] + 1;
                vis[v] = true;
                Q.emplace(v);
            }
        }
    }
}
int ansLen = 0;
void subBFS(int st, vec<bool> &visited, int len)
{

    deque<int> Q;
    vec<int> disfromSt(N, disINF);
    disfromSt[st] = false;
    Q.emplace_front(st);

    while(!Q.empty()){
        int u = Q.front();
        Q.pop_front();
        for(int &v: G[u]){
            int w = (visited[v] == true ? 0 : 1);
            if(disfromSt[v] > disfromSt[u] + w){
                disfromSt[v] = disfromSt[u] + w;
                if(w == 0){
                    Q.emplace_front(v);
                }
                else{
                    Q.emplace_back(v);
                }
            }
        }
    }
    ansLen = min(ansLen, len + disfromSt[1]);
}
int cutLen = 0;
void DFS(int u, vec<bool> &visited, int len)
{
    if(len > cutLen)
        return;
    visited[u] = true;

    if(u == 0){
        subBFS(0, visited, len);
        visited[u] = false;
        return;
    }
    for(int& v: G[u]){
        if(visited[v])
            continue;
        DFS(v, visited, len+1);
    }

    visited[u] = false;
}

int main()
{
    int caseN = 1;
    while (cin >> N >> M)
    {
        if(N == 0 && M == 0)
            break;
        G.clear();
        G.resize(N);
        ansLen = numeric_limits<int>::max();
        REP(i, M)
        {
            int u, v;
            cin >> u >> v;
            u--, v--;
            G[u].eb(v);
        }
        REP(i, 2){
            disfrom[i].resize(N);
            fill(disfrom[i].begin(), disfrom[i].end(), disINF);
            BFS(i, disfrom[i]);
        }
        cutLen = disfrom[0][1] + disfrom[1][0];
        vec<bool> visited(N, false);
        DFS(1, visited, 1);
        cout << "Network " << caseN++ << endl;
        if (ansLen == numeric_limits<int>::max())
        {
            cout << "Impossible\n";
        }
        else {
            cout << "Minimum number of nodes = " << ansLen << endl;
        }
        cout << endl;
    }

    return 0;
}