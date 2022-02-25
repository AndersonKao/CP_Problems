#include <bits/stdc++.h>
using namespace std;

int T;
int ans;

bool G[15][15];
int deg[15];
void reset(){
    ans = 20;
    for (int i = 0; i < 15; i++){
        fill(G[i], G[i] + 15, false);
        deg[i] = 0;
    }
}

// false if no cycle, true if contains cycle;
bool DFS(int i, int par, bool* visited, bitset<15> &Bs,  int N){
    for (int p = 0; p < N; p++)
    {
        if(!G[i][p] || p == par)
            continue;
        if(!Bs[p]){
            if(!visited[p]){
                visited[p] = true;
                if(DFS(p,i, visited, Bs, N))
                    return true;
            }else{
                return true;
            }
        }
    }
    return false;
}

bool test(unsigned long bits, int N){
    bitset<15> Bs(bits);
    // deg check <= 2 for chain
    for (int i = 0; i < N; i++){
        int dismiss = 0;
        if(Bs[i])
            continue;
        for (int p = 0; p < N;  p++)
        {
            if(G[i][p] && Bs[p])
                dismiss++;
        }
        if(deg[i] - dismiss > 2){
            return false;
        }
    }
    // DFS check:
    // 1. if exist cycle
    // 2. if # of connected component <= Bs.count() + 1;
    int Ncc = 0; // # of connected component;
    bool visited[15];
    fill(visited, visited + 15, false);
    for (int i = 0; i < N; i++)
    {
        if(!visited[i] && !Bs[i]){ // not visited and not eliminated
            visited[i] = true;
            if(DFS(i, -1, visited, Bs, N)){
                return false;
            }
                Ncc++;
        }
    }
    if(Ncc <= Bs.count() + 1){
        // becare of no open ans;
        ans = min(ans, (int)Bs.count());
        return true;
    }
    return false;
}

bool solve(){
    unsigned int N;
    cin >> N;
    if(N == 0)
        return false;
    reset();
    int u, v;
    while (cin >> u >> v)
    {
        if(u == -1 && v == -1)
            break;
        if(!G[u-1][v-1]){
            G[u - 1][v - 1] = G[v - 1][u - 1] = true;
            deg[u - 1]++;
            deg[v - 1]++;
        }
    }

    bool solve = false;
    for (unsigned long bits = 0; bits < (1 << N); bits++){
        if(test(bits, N)){
            solve = true;
        }
    }
    return solve;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int cnt = 1;
    while(solve()){
        cout << "Set " << cnt++ << ": Minimum links to open is " << ans << endl;
    }
    return 0;
}