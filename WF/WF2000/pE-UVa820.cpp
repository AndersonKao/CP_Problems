#include <bits/stdc++.h>
using namespace std;

// O((V+E)F)
#define MAXN 101
// remember to change used into the maxNode size -- kattis elementary math
bool used[MAXN];
int End;
vector<int> V[MAXN];
vector<tuple<int, int>> E;

// x=>y 可以流 C 
// if undirected or 2-direc edge, bakcward Capacity become C;
// Graph build by edge array
// 反向邊的編號只要把自己的編號 xor 1 就能取得
void add_edge(int x, int y,int c)
{
    V[x].emplace_back( E.size() );
    E.emplace_back(y,c);
    V[y].emplace_back( E.size() );
    E.emplace_back(x, c);
}
int dfs(int v, int f)
{
    if( v==End ) return f;
    used[v] = true;
    int e,w;
    for( int eid : V[v] )
    {
        tie(e,w) = E[eid];
        if( used[e] || w==0 ) continue;
        
        w = dfs(e, min(w,f));
        if( w>0 )
        {
            // 更新流量
            get<1>(E[eid  ]) -= w;
            get<1>(E[eid^1]) += w;
            return w;
        }
    }
    return 0;// Fail!
}
int ffa(int s,int e)
{
    int ans = 0, f;
    End = e;
    while(true)
    {
        memset(used, 0, sizeof(used));
        f = dfs(s, INT_MAX);
        if( f<=0 ) break;
        ans += f;
    }
    return ans;
}


int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    int s, t, c;
    int cnt = 1;
    while(cin >> n){
        if(n == 0)
            break;
        for (int i = 0; i <= n; i++){
            V[i].clear();
        }
        E.clear();
        cin >> s >> t >> c;
        for (int i = 0; i < c; i++){
            int u, v, f;
            cin >> u >> v >> f;
            add_edge(u, v, f);
        }
        cout << "Network " << cnt++ << endl;
        cout << "The bandwidth is " << ffa(s, t) << ".\n\n";

    }
    return 0;
}

/*
4
1 4 5
1 2 20
1 3 10
2 3 5
2 4 10
3 4 20
0
*/
