// AC 2022-02-26 08:33:49
// WA, new thought
// 直接用cnt 但是忘記就散是cnt >= len[1]，cnt也要++(leaf)
// WA
// 沒有考慮到leaf自己的ANS剛好也是0，但是會被當成沒有child 
// WA new thought
// 只要看 len [0][1]為0的狀況就可，但是沒考慮到重複值的問題
// WA
// 不知道漏了什麼case
// WA 
// 沒有考慮只有一個child的 case，for root and leaf
#include <bits/stdc++.h>
using namespace std;

using edge = pair<int, int>;

vector<vector<int>> G;
vector<int> maxD; // longest path from this vertex to leaf
vector<int> ANS;
void DFSdepth(int now, int p){
    int ans = 0;
    for(auto& u: G[now]){
        if(u == p)
            continue;
        DFSdepth(u, now);
        ans = max(maxD[u] + 1, ans);
    }
    maxD[now] = ans;
}
void DFSans(int now, int p){
    int ans = 0;
    int len[2] = {0};
    int cnt = 0;
    for(auto& u: G[now]){
        if(u == p)
            continue;
        if(maxD[u] >= len[0])
            len[1] = len[0], len[0] = maxD[u], cnt++;
        else if(maxD[u] >= len[1])
            len[1] = maxD[u], cnt++;
        DFSans(u, now);
        ans = max(ANS[u], ans);
    }
    int add = 2;
    if(cnt == 0)
        add = 0;
    else if(cnt == 1)
        add = 1;
    ANS[now]= max(ans, len[0] + len[1] + add);
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    G.resize(N);
    maxD.resize(N);
    ANS.resize(N);
    
    int u, v;
    for (int i = 0; i < N-1; i++){
        cin >> u >> v;
        u--, v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    DFSdepth(0, -1);
    DFSans(0, -1);
    int ans = 0;
    for (int i = 0; i < N; i++){
      //  cout << i << ", depth= " << maxD[i] << ", ANS= " << ANS[i] << endl;
        ans = max(ans, ANS[i]);
    }
    cout << ans << endl;
    return 0;
}