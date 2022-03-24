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

void init(){
    //debug(m);
    //debug(n);
    if(msize.size() < m)
        msize.resize(m);
    if(pspec.size() < n)
        pspec.resize(n);
    G.clear();
    G.resize((m + 1)*n + 2);
    E.clear();
    if(dis.size() < (m + 1)*n + 2)
        dis.resize((m + 1)*n + 2);
    inq.resize((m + 1) * n + 2);
    if (pre.size() < (m + 1) * n + 2)
        pre.resize((m + 1)*n + 2);
    st.clear();
    st.resize(m, vector<PLL>(n));
    if(taskAns.size() < n)
        taskAns.resize(n);
    if(Mcnt.size() < m)
        Mcnt.resize(m);
    fill(al(Mcnt), 0);
}
void add_edge(int from, int to, int cap, LL cost){
    G[from].eb(E.size());
    E.eb(from, to, cost, cap);    
    G[to].eb(E.size());
    E.eb(to, from, -cost, 0);    
}
LL BF(int s, unsigned int Gsize)
{ // Bellman-Ford
    fill(al(dis), disINF);
    fill(al(inq), false);
    fill(al(pre), -1);
    dis[s] = 0;
    queue<int> Q;
    Q.emplace(0);
    int f, t; // from, to
    LL c,v; // cur capacity value
    while(!Q.empty()){
        int u = Q.front();
        Q.pop(), inq[u] = false;
        for(int& e: G[u]){
            f = E[e].f, t = E[e].t, c = E[e].c, v = E[e].v;
            if(v <= 0)
                continue;
            if(dis[t] > dis[f] + c){
                dis[t] = dis[f] + c;
                pre[t] = e;
                if(!inq[t])
                    inq[t] = true, Q.emplace(t);
            }
        }
    }
 
    if(pre[MCMF_t] == -1){
        return 0;
    }

    int u = MCMF_t;
    LL flowval = llINF;
    LL cost = 0;
    while(pre[u] != -1){
        flowval = min(flowval, E[pre[u]].v); 
        cost += E[pre[u]].c;
        u = E[pre[u]].f;
    }
    u = MCMF_t;
    while(pre[u] != -1){
        E[pre[u]].v -= flowval;
        if(u > m * n && u <= (m + 1) * n){
            taskAns[u - m * n - 1].F = pre[u];
        }
        E[pre[u] ^ 1].v += flowval;
        u = E[pre[u]].f;
    }
    return cost * flowval;
}

LL MCMF(int s){
    LL ans = 0; 
    LL val;
    while(val = BF(s, G.size())){
        ans += val; 
    }
    return ans;
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
        REP(i, m){
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
        LL myans = MCMF(0);
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
