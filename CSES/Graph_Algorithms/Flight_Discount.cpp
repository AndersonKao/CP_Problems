// AC 2022-02-25 17:23:41
// 其實直接紀錄discount跟 not discount的做法是可以的，剛剛也是忘記開in queue
// 複雜度應該也是 O(E + VlogV) 常數應該是2倍 (Flight_Discount2.cpp)
// AC 2022-02-25 17:22:01
// WA 2022-02-25 17:21:20
// 忘記把min pq拿出來的element if element u!=dis[u] continue
// WA 2022-02-25 17:19:48
// 忘記開min pq ><
// new thought
// 從s, t 做兩次dijkstra，接著枚舉要刪掉的邊get ans
// refer https://codeforces.com/blog/entry/79579
// O(E+VlogV) + O(E);
// TLE 2022-02-25 16:48:01
// 直接把discount 跟not discount塞進pq的作法太慢了
// O(E + VlogV) 其實我估不了正確的值，可能會是 O(3E + 3Vlog(3V))
#include <bits/stdc++.h>

using namespace std;
#define MAXDIS 1000000000000000
using LL = long long;
using PLL = pair<LL, LL>;
using edge = pair<int, LL>;
using pqE = pair<LL, int>;
int N, M;
vector<vector<edge>> G, Ginv;
void Dijsktra(int st, vector<vector<edge>>& G, vector<LL>& dis){
    priority_queue<pqE, vector<pqE>, greater<pqE>> pq;
    dis[st] = 0;
    pq.emplace(0, st);
    int u, v;
    LL w, d;
    bool free;
    while(!pq.empty()){
        tie(w, u) = pq.top();
        pq.pop();
        if(w != dis[u])
            continue;
        for(edge& e: G[u]){
            tie(v, d) = e;
            if(dis[v] > dis[u]+ d){
                dis[v]= dis[u]+ d;
                pq.emplace(dis[v], v);
            }
        }
    } 
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N >> M;
    int u, v;
    LL w;
    G.resize(N);
    Ginv.resize(N);
    vector<LL> disfromS, disfromT;
    disfromS.resize(N, MAXDIS);
    disfromT.resize(N, MAXDIS);

    for (int i = 0; i < M; i++){
        cin >> u >> v >> w;
        u--, v--;
        G[u].emplace_back(v, w);
        Ginv[v].emplace_back(u, w);
    }

    Dijsktra(0, G, disfromS);
    Dijsktra(N-1, Ginv,  disfromT);
    LL ANS = MAXDIS;
    for (int u = 0; u < G.size(); u++)
    {
        for(edge& e: G[u]){
            tie(v, w) = e;
            if(disfromS[u] == MAXDIS || disfromT[v] == MAXDIS)
                continue;
            ANS = min(ANS, disfromS[u] + disfromT[v] + w / 2);
        }
    }

    cout << ANS << endl;

    return 0;
}