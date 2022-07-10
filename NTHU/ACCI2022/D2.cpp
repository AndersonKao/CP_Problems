#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
#define F first
#define S second
#define eb emplace_back
template <typename T>
using vec = vector<T>;
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;

// V times DFS O(EV)
vector<int> V[101];
// V[i]記錄了左半邊可以配到右邊的那些點
int match[101]; // A<=B
// match[i] 記錄了右半邊配對到左半邊的哪個點
bool used[101];
int n;
bool dfs(int v)
{
    for(int e:V[v])
    {
        if( used[e] ) continue;
        used[e] = true;
        if( match[e] == -1 || dfs( match[e] ) )
        {
            match[e] = v;
            return true;               
        }
    }
    return false;
}
int konig()
{
    memset(match,-1,sizeof(match));

    int ans=0;
    
    for(int i=1;i<=n;++i)
    {
        memset(used, 0, sizeof(used));
        if( dfs(i) )
            ans++;
    }

    return ans;
}
#define debug(x) cout << #x << ":" << x << endl;
int main()
{
    int m;
    while(cin >> n >> m){
        if(n == 0 && m == 0)
            break;
        REP(i, 101){
            V[i].clear();
        }
        vec<int> outdeg(101, 0);

        vec<vec<int>> G(101, vec<int>(101, 0));
        REP(i, m)
        {
            int u, v;
            cin >> u >> v;
            G[u][v] = 1;
            V[u].eb(v);
            outdeg[u]++;
        }
        for(int u = 1; u <= n; u++){
            //  不能一邊emplace又一邊存取這個element
            for (int i = 0; i < V[u].size(); i++)
            {
                int v = V[u][i];
                if (outdeg[v] >= 1)
                {
                    for(int &k: V[v]){
                        if(G[u][k] != 1){
                            V[u].eb(k);
                            G[u][k] = 1;
                        }
                    }
                }
            }
        }
        int nmatch = konig();
        cout << n - nmatch << endl;
    }

    return 0;
}