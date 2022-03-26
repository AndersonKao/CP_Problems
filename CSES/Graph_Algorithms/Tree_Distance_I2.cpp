// AC 	2022-02-26 19:28:58
// More clear Dynamic programming 
#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;
vector<vector<int>> G;
vector<pair<PII,PII>> maxlen;
vector<int> maxD;
vector<int> ANS;
void DFSdepth(int now, int p){ // first use this to calculate max len it can go to leaf.
    int len;
    maxlen[now].first.first = maxlen[now].second.first = 0;
    maxlen[now].first.second = maxlen[now].second.second= -1;
    for(auto& u: G[now]){
        if(u == p)
            continue;
        DFSdepth(u, now);
        len = maxlen[u].first.first + 1;
        if(len >= maxlen[now].first.first){
            maxlen[now].second = maxlen[now].first;
            maxlen[now].first.first = len;
            maxlen[now].first.second = u;
        }else if(len >= maxlen[now].second.first){
            maxlen[now].second.first = len;
            maxlen[now].second.second = u;
        }
    }
}
void DFSans(int now, int p){ // renew the maxlen
    int ans = 0;
    if(p != -1)
    if(maxlen[p].first.second != now){
        ans = max(ans, maxlen[p].first.first + 1);
    }else{
        ans = max(ans, maxlen[p].second.first + 1);
    }
    if(ans >= maxlen[now].first.first){
        maxlen[now].second = maxlen[now].first;
        maxlen[now].first.first = ans;
        maxlen[now].first.second = p;
    }else if(ans >= maxlen[now].second.first){
        maxlen[now].second.first = ans;
        maxlen[now].second.second = p;
    }

    for(auto& u:G[now]){
        if(u == p)
            continue;
        DFSans(u, now);
    }
    ANS[now] = maxlen[now].first.first;
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    G.resize(N);
    maxD.resize(N);
    ANS.resize(N);
    maxlen.resize(N);
    int u, v;
    for (int i = 0; i < N - 1; i++){
        cin >> u >> v;
        u--, v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    DFSdepth(0, -1);
    DFSans(0, -1);
    for (int i = 0; i < N; i++)
        cout << ANS[i] << (i == N - 1 ? "\n" : " ");
        return 0;
}