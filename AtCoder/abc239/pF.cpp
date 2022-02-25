#include <bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, M;

int limit[MAXN];
int deg[MAXN];
bool visited[MAXN];
int p[MAXN];

int master(int i){
    if(p[i] == i){
        return i;
    }
    return p[i] = master(p[i]);
}

void merge(int a, int b){
    p[b] = master(a);
}
vector<vector<int>> G;
int DFS(int u, set<int> &S){

    int ans = -1;
    visited[u] = true;
    if(deg[u] < limit[u]){
        S.emplace(u);
        ans = u;
    }
    for(auto& v: G[u]){
        if(!visited[v]){
        
            if(deg[v] < limit[v]){
                ans = v;
            }
            int k = DFS(v, S);
            ans = (k == -1 ? ans : k);
        }
    }

    return ans;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N >> M;
    G.resize(N);
    fill(deg, deg + N, 0);
    fill(visited, visited+ N, false);
    for (int i = 0; i < N; i++)
    {
        cin >> limit[i];
    }
    int u, v;
    for (int i = 0; i < M; i++){
        cin >> u >> v;
        u--, v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
        deg[u]++;
        deg[v]++;
    }
    for (int i = 0; i < N; i++){
        if(deg[i] > limit[i]){
            cout << "-1\n";
            return 0;
        }

        cout << i << " deg = " << deg[i] <<  ": ";
        for(auto ji: G[i]){
            cout << ji << " ";
        }
        cout << endl;
    }
    set<int> S;
    S.clear();
    vector<pair<int, int>> ANS;

    DFS(0, S);

    for (int i = 0; i < N; i++){
        if(visited[i])
            continue;
        for(auto ki: S){
            cout << ki << ", ";
        }
        cout << endl;
        int sb = *(S.begin());
        int u2 = DFS(i, S);
        cout << "toadd " << sb << ", " << u2 << endl;
        if(u2 == -1){
            cout << "-1\n";
            return 0;
        }
        deg[sb]++;
        deg[u2]++;
        ANS.emplace_back(sb + 1, u2 +1);
        if(deg[sb] == limit[sb]){
            S.erase(sb);
        }
        else if(deg[sb] > limit[sb]){
            cout << "-1\n";
            return 0;
        }
        if(deg[u2] == limit[u2]){
            S.erase(u2);
        }
        else if(deg[u2] > limit[u2]){
            cout << "-1\n";
            return 0;
        }
    }
    for(auto& e: ANS){
        cout << e.first << " " << e.second << endl;
    }

        return 0;
}