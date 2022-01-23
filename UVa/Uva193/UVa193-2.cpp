// AC 2020-09-21 23:54:00
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
vector<int> G[104];
vector<int> bl;
vector<int> ANSv;
bool visited[104];
int color[104];
int ans;
// #define TEST
int N, k;
int cnt;
void DFS(int v){
    if(v > N){
        if(bl.size() > ans){
            ans = bl.size();
            ANSv = bl;
        }
        return;
    }
    bool blackable = true;
    for (auto u: G[v]){
        if(color[u] == 1){
            blackable = false;
        }
    }
    if(blackable){
        color[v] = 1;
        bl.push_back(v);
        DFS(v + 1);
        bl.pop_back();
    }
    
    color[v] = 2;

    DFS(v + 1);
}
// #define TEST
int main(){
    #ifdef TEST
    freopen("in.txt", "r", stdin);
    #endif
    int T;
    cin >> T;
    while(T--){
        cnt = 0;
        ans = 0;
        cin >> N >> k;
        for(int i = 1; i <= N; i++){
            G[i].clear();
        }
        ANSv.clear();
        int a, b;
        for(int i = 0; i < k; i++){
            cin >> a >> b;
            G[a].emplace_back(b);
            G[b].emplace_back(a);
        }
        DFS(1);
        sort(ANSv.begin(), ANSv.end());
        cout << ans << endl;
        for (int i = 0; i < ANSv.size(); i++){
            cout << ANSv[i] << (i == ANSv.size() - 1 ? '\n' : ' ');
        }
    }
    return 0;
}