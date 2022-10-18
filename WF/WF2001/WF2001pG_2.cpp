// try cp-algorithm
// AC List Removals
// TLE SPFA 可以採用
// WA task順序沒搞好
#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
#define REP(i, n) for(int i=0;i<n;i++)
#define REP1(i, n) for(int i=1;i<=n;i++)
#define F first
#define S second
#define eb emplace_back
#define pb push_back 
#define endl '\n'
#define mp make_pair(a,b)
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define al(a) a.begin(),a.end()
#define int long long
LL disINF = numeric_limits<long long>::max() / 3;
LL llINF = numeric_limits<long long>::max();

struct edge{
    int f, t; // from, to
    LL c, v; // cost, cur capacity value
public:
    edge(int f, int t, int c, int v):f(f), t(t), c(c), v(v){}
};
vector<LL> msize;
vector<vector<PLL>> pspec; // memorysize -> time
vector<vector<int>> G;
vector<edge> E;
vector<LL> dis;
vector<int> pre;
vector<vector<PLL>> st;
vector<PII> taskAns;  // mid, ntask;

vector<int> Mcnt; // task for each memory
vector<bool> inq;
int MCMF_t;
int m, n, k;
struct Edge
{
    int from, to, capacity, cost;
};
vector<Edge> edges;
vector<vector<int>> adj, cost, capacity;

const int INF = 1e9;
void init(){
    edges.clear();
    adj.clear();
    cost.clear();
    capacity.clear();
}
void add_edge(int from, int to, int cap, LL cost){
    E.eb(from, to, cost, cap);    
    E.eb(to, from, -cost, 0);    
}
void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int min_cost_flow(int N, vector<Edge>& edges, int K, int s, int t) {
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0;
    int cost = 0;
    vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        // find max flow on that path
        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    if (flow < K)
        return -1;
    else
        return cost;
}

bool cmptopo(int a, int b){
    return taskAns[a] < taskAns[b];
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int Case = 1; cout << fixed << setprecision(2);
    while(cin >> m >> n){
        if(n == 0 && m == 0)
            break;
        init();
        REP(i, m)
        {
            cin >> msize[i];
        }
        REP(i, n){
            cin >> k;
            pspec[i].resize(k);
            REP(j, k){
                cin >> pspec[i][j].F >> pspec[i][j].S;
            }
        }
        LL mul = n;
        LL msizeI = 0;
        REP1(i, m * n)
        {
            mul = n - (i - 1)/m;
            add_edge(0, i, 1, 0);
            LL cursize = msize[msizeI];
            msizeI = (msizeI + 1 == m ? 0 : msizeI + 1);
            REP(j, n)
            {
                LL cost = -1;
//                cout << "processing msize = " << cursize<< endl;
                REP(k, pspec[j].size()){
                    if(pspec[j][k].F <= cursize){
                        cost = pspec[j][k].S;
                    }
                    else
                        break;
                }
                if(cost != -1){
                    add_edge(i, m * n + j + 1, 1, mul * cost);
                }
            }
        }
        MCMF_t = (m + 1) * n + 1;
        REP(j, n){
            add_edge(m * n + j + 1, MCMF_t, 1, 0);
        }
        // MCMF
        LL myans = min_cost_flow(MCMF_t+1, edges, INF, 0, MCMF_t);
        //
        cout << "Case " << Case++ << endl;
        cout << "Average turnaround time = " <<   myans/(double)n << endl;

        vector<int> topo(n);
        REP(task, n){
            topo[task] = task;
        }
        sort(al(topo), cmptopo);
        int i, mid, ntask, div;

        for (auto task : topo)
        {
            i = E[taskAns[task].F].f;
            mid = (i - 1) % m;
            ntask = Mcnt[mid]++;
            taskAns[task].S = ntask;
            div = n - (i - 1) / m;

            st[mid][ntask].F = 0;
            if(ntask > 0){
                st[mid][ntask].F = st[mid][ntask-1].S ;
            }
            st[mid][ntask].S = st[mid][ntask].F + (E[taskAns[task].F].c / (div));
        }
        REP(task, n){
            i = E[taskAns[task].F].f;
            mid = (i - 1) % m;
            ntask = taskAns[task].S;
            cout << "Program " << task + 1 << " runs in region ";
            cout << mid + 1<< " from " << st[mid][ntask].F << " to "<< st[mid][ntask].S << endl;
        }
    }

    return 0;
}