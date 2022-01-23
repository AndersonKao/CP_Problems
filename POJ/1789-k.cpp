#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
#include <queue>
#define MAX_N 2005
using namespace std;
struct disjointset{
    int f[MAX_N];
    int rank[MAX_N];
    void init(){
        for (int i = 0; i < MAX_N; i++){
            f[i] = i;
            rank[i] = 1;
        }
    }
    int find(int v){
        if(f[v] == v)
            return v;
        return f[v] = find(f[v]);
    }
    bool same(int a, int b){
        return find(a) == find(b);
    }
    void Union(int a, int b){
        if(same(a,b))
            return;
        if(rank[a] < rank[b]){
            swap(a, b);
        }
        f[f[b]] = f[a];
        rank[a]++;
    }
};
struct edge{
    int u, v, w;
    edge(int a, int b, int c): u(a), v(b), w(c){}
    int operator<(edge &r){
        return this->w < r.w;
    }
};

vector<edge> G;
char strs[2005][10];
int main(){
    int N;
    disjointset DJ;
    while (cin >> N){
        if(!N)
            break;
        DJ.init();
        G.clear();
        for (int i = 0; i < N; i++){
            cin >> strs[i];
        }
        for (int i = 0; i < N; i++){
            for (int j = i+1; j < N; j++){
                
                int res = 0;
                for (int k = 0; k < 7; k++){
                    if(strs[i][k] != strs[j][k])
                        res++;
                    // cout << res << endl;
                }
                G.push_back(edge(i, j, res));
            }
        }
        sort(G.begin(), G.end());
        int ans = 0;
        int edge_num = 0;
        int u, v, w;

        for (int i = 0; i < G.size(); i++)
        {
            u = G[i].u;
            v = G[i].v;
            w = G[i].w;
            if(DJ.same(u,v))
                continue;
            DJ.Union(u, v);
            ans += w;
            // cout << "ans change to " << ans << endl;
            edge_num++;
            if(edge_num >= N-1)
                break;
        }
        cout << "The highest possible quality is 1/" << ans << ".\n";
  
    }
        return 0;
}
/*
6
aaaaaaa
aaiiiii
aiaiaia
iiiaaai
aaiaiia
aiiaiai
4
aaaaaaa
baaaaaa
abaaaaa
aabaaaa
*/