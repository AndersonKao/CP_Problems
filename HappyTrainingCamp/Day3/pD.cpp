#include <bits/stdc++.h>
using namespace std;

int T;

void solve(){

}
int G[1001][1001] = {0};
int deg[1001];
int need[1001];
bool visited[1001];
int DFS(int v, int N)
{
    int ans = 0;
    visited[v] = true;
    for (int i = 0; i < N; i++){
        if(G[v][i] && !visited[i]){
            ans += DFS(i, N);
        }
    }
    if(deg[v] &1)
        ans++;
    return ans;
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N, E, cost;
    int cnt = 1;
    while (cin >> N >> E >> cost)
    {
        if (N == 0)
            break;
        fill(deg, deg + N, 0);
        fill(visited, visited + N, false);
        fill(need, need + N, false);
        for (int i = 0; i < N; i++)
        {
            fill(*(G + i), *(G + i) + N, 0);
        }
        int a, b;
        for (int i = 0; i < E; i++)
        {
            cin >> a >> b;
            a--;
            b--;
            G[a][b] = G[b][a] = 1;
            deg[a]++;
            deg[b]++;
            need[a] = true;
            need[b] = true;
        }
        int single;
        int ans = E;
        for (int i = 0; i < N; i++)
        {
            if (need[i] && !visited[i])
            {
                ans++;
                single = DFS(i, N);
                if (single > 2)
                {
                    ans += single / 2 - 1;
                }
            }
        }
        cout << "Case " << cnt++ << ": "<< (ans == 0 ? 0 : (ans - 1) * cost) << endl;

}

    return 0;
}