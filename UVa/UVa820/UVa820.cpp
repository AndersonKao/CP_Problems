// AC 2020-09-20 14:58:35
#include <vector>
#include <cstring>
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>
using namespace std;
#define INT_MAX 10000000
int N, S, T, c;
vector<int> G[101];
vector<tuple<int, int>> E;
bool used[101];
int dfs(int v, int f){

    if(v == T){
        // cout << v << " ";
        return f;
    }
    used[v] = true;
    int u, w;
    for(auto eid: G[v]){
        tie(u, w) = E[eid];
        if(used[u] || w == 0)
            continue;
        w = dfs(u, min(f, w));
        if(w > 0){
            get<1>(E[eid]) -= w;
            get<1>(E[eid ^ 1]) += w;
            // cout << v << " ";
            return w;
        }
    }
    return 0;
}
int ffa(){
    int ans = 0;
    int f;
    while(true){
        memset(used, 0, sizeof(used));
        f = dfs(S, INT_MAX);
        // cout << "find f: " << f << endl;
        if(f <= 0){
            break;
        }
        ans += f;
        // cout << "cur ans: " << ans << endl;
    }

    return ans;
}
// #define TEST
int main(){
    #ifdef TEST
    freopen("in.txt", "r", stdin);
    #endif
    int counter = 1;
    while(cin >> N){
        if(!N)
            break;
        for (int i = 0; i <= N; i++){
            G[i].clear();
        }
        E.clear();
        cin >> S >> T;
        cin >> c;
        int a, b, cap;
        for (int i = 0; i < c; i++){
            cin >> a >> b >> cap;
            G[a].emplace_back(E.size());
            E.emplace_back(b, cap);
            G[b].emplace_back(E.size());
            E.emplace_back(a, cap);
        }
        int ANS = ffa();
        cout << "Network " << counter++ << '\n';
        cout << "The bandwidth is " << ANS << ".\n\n";
    }
    return 0;
}