#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, Q;
int value[MAXN];
vector<int> mv[MAXN];
vector<vector<int>> G;
void postfix(int u, int p){

    for(auto& v: G[u]){
        if(v != p)
            postfix(v, u);
    }

    vector<vector<int>::iterator> itrs;
    itrs.resize(G[u].size());
    int atmost = 0;
    for (int i = 0; i < G[u].size(); i++){
        itrs[i] = mv[G[u][i]].begin();
    }
    int min_index, max_value;
    bool myself = false;
    for (int k = 0; k < 20; k++){
        max_value = 0;
        min_index = -1;
        for (int i = 0; i < G[u].size(); i++){
            if(itrs[i] != mv[G[u][i]].end() && *itrs[i] > max_value){
                min_index = i;
                max_value = *itrs[i];
            }
        }
        if(min_index == -1){
            if(!myself)
                mv[u].emplace_back(value[u]);
            break;
        }else{
            if(!myself && *itrs[min_index] < value[u]){
                mv[u].emplace_back(value[u]);
                myself = true;
            }else{
                mv[u].emplace_back(*itrs[min_index]);
                itrs[min_index]++;
            }
        }
    }
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N >> Q;
    for (int i = 0; i < N; i++){
        cin >> value[i];
    }
    G.resize(N);
    int a, b;
    for (int i = 0; i < N - 1; i++){
        cin >> a >> b;
        a--, b--;
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }
    postfix(0, -1);

    /*
    for (int i = 0; i < N; i++){
        cout << i + 1 << ": ";
        for(auto& u: mv[i]){
            cout << u << ", ";
        }
        cout << endl;
    }
    */
    int V, K;
    for (int i = 0; i < Q;i++){
        cin >> V >> K;
        cout << mv[V-1][K - 1] << endl;
    }

        return 0;
}