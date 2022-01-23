// AC 2020-09-20 14:58:35
// by Dinics
#include <vector>
#include <cstring>
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;
#define maxn 101
#define INT_MAX 10000000
int End, dist[maxn];
vector<tuple<int, int, int>> V[maxn];
// 1st for node-index, 2nd for cap, 3nd for the index of the edge and the vector[u];
void addEdge(int u, int v, int c){
    V[u].emplace_back(v, c, V[v].size());
    V[v].emplace_back(u, c, V[u].size() - 1);
}
bool bfs(int s) {
    memset(dist, -1, sizeof(dist));
    queue<int> qu;
    qu.emplace(s);
    dist[s]=0;

    while( !qu.empty() ) {
        int S = qu.front(); qu.pop();
        for(auto &p : V[S]) {
            int E, C;
            tie(E, C, ignore) = p;
            if( dist[E]==-1 && C!=0 ) {
                dist[E]=dist[S]+1;
                qu.emplace(E);
            }
        }
    }
    return dist[End] != -1;
}
int dfs(int v, int f) { 
    int e,w,rev;
    if( v==End || f==0 ) return f;
    for( auto &t : V[v] )
    {
        tie(e,w,rev) = t;
        if( dist[e]!=dist[v]+1 || w==0 )
            continue;

        w = dfs(e, min(w,f));
        if( w>0 )
        {
            get<1>(t) -= w;
            get<1>(V[e][rev]) += w;
            return w;
        }
    }
    dist[v] = -1; //優化，這個點沒用了 
    return 0;// Fail!
}
int dinic(int s,int e)
{
    int ans = 0, f;
    End = e;
    while(bfs(s))
    {
        while( f = dfs(s, INT_MAX) )
            ans += f;
    }
    return ans;
}

// #define TEST
int N, S, T, c;
int main(){
    #ifdef TEST
    freopen("in.txt", "r", stdin);
    #endif
    int counter = 1;
    while(cin >> N){
        if(!N)
            break;
        for (int i = 0; i < maxn; i++){
            V[i].clear();
        }
        // E.clear();
        cin >> S >> T;
        cin >> c;
        // End = T;
        int a, b, cap;
        for (int i = 0; i < c; i++){
            cin >> a >> b >> cap;
            addEdge(a, b, cap);
        }
        int ANS = dinic(S, T);
        cout << "Network " << counter++ << '\n';
        cout << "The bandwidth is " << ANS << ".\n\n";
    }
    return 0;
}