#include <bits/stdc++.h>
using namespace std;
//#define DEBUGK
//#define DEBUG2

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
#ifdef DEBUGK
    cout << "DFSing " << i << endl;
#endif
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
#ifdef DEBUGK
                cout << "(i, p) =" << i << ", " << p << " detect cycle\n";
#endif
                return true;
            }
        }
    }
    return false;
}

bool test(unsigned long bits, int N){
    bitset<15> Bs(bits);
#ifdef DEBUGK
    cout << "using set " << Bs << endl;
#endif
    // deg check <= 2
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
            #ifdef DEBUGK
            cout << "deg error on index: " << i << endl;
            #endif
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

            #ifdef DEBUGK
            cout << "Try DFS\n";
            #endif
            if(DFS(i, -1, visited, Bs, N)){
            #ifdef DEBUGK
                cout << "u got cycles\n";
            #endif
                return false;
            }
#ifdef DEBUGK
            cout << "NCC increased\n";
#endif
                Ncc++;
        }
    }
#ifdef DEBUGK
    if(Ncc > Bs.count() + 1)
        cout << "Too much component() = " << Ncc << endl;
#endif

    if(Ncc <= Bs.count() + 1){
#ifdef DEBUG2
        if(ans >= Bs.count()){
            cout << "We should open: ";
            for (int i = 0; i < N; i++)
                if(Bs[i])
                    cout << i + 1 << " ";
            cout << endl;
        }
#endif
        // becare of no open ans;
        ans = min(ans, (int)Bs.count());

#ifdef DEBUGK
        cout << "set ans = " << ans << endl;
#endif
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

#ifdef DEBUGK
    cout << "origin deg\n";
    for (int i = 0; i < N; i++){
        cout << "deg " << i << " = " << deg[i] << endl;
    }
#endif
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