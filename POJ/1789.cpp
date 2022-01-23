#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
#define enp pair<int, int>
char strs[2005][10];
int prim_pq(int N, vector<vector<enp>> &E){
    vector<bool> vis;
    vis.resize(N, false);
    vis[0] = true;
    priority_queue<enp> pq;
    for (vector<enp>::iterator e = E[0].begin(); e != E[0].end(); e++)
    {
        pq.push(enp(-e->first, e->second));
    }
    int ans = 0;
    int edges = 0;
    while(pq.size()){
        int w, v;
        w = -pq.top().first;
        v = pq.top().second;
        pq.pop();
        if(vis[v])
            continue;
        // w *= -1;
        vis[v] = true;
        ans += w;
        edges++;
        if(edges >= N-1)
            break;
        for (vector<enp>::iterator e = E[v].begin(); e != E[v].end(); e++)
        {
            if(!vis[e->second])
                pq.push(enp(-e->first, e->second));
        }
    }
    return ans;
}
int main(){
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    while(cin >> N){
        if(N == 0)
            break;
        vector<vector<enp>> E;
        E.resize(N);
        // cin >> N;
        for (int i = 0; i < N; i++){
            cin >> strs[i];
        }
        int diff = 0;
        for (int i = 0; i < N; i++){
            for (int j = i+1; j < N; j++){  
                diff = 0;
                for (int k = 0; k < 7; k++){
                    if(strs[i][k] != strs[j][k])
                        diff++;
                }
                
                E[i].push_back(enp(diff, j));
                E[j].push_back(enp(diff, i));
            }
        }
        int ans = prim_pq(N, E);
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