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
int MCMF_t;
int m, n, k;

void init(){
    debug(m);
    debug(n);
    msize.resize(m);
    pspec.resize(n);
    G.clear();
    G.resize((m + 1)*n + 2);
    E.clear();
    dis.resize((m + 1)*n + 2);
    pre.resize((m + 1)*n + 2);
    st.clear();
    st.resize(m, vector<PLL>(n));
    taskAns.resize(n);
}
void add_edge(int from, int to, int cap, LL cost){
    G[from].eb(E.size());
    E.eb(from, to, cost, cap);    
    G[to].eb(E.size());
    E.eb(to, from, -cost, 0);    
}

LL BF(int s, unsigned int Gsize){ //Bellman-Ford
    fill(al(dis), disINF);
    fill(al(pre), -1);
    dis[s] = 0;


    int f, t; // from, to
    LL c,v; // cur capacity value

    REP(i, Gsize)
        REP(e, E.size()){
            f = E[e].f, t = E[e].t, c = E[e].c, v = E[e].v;
            if(v <= 0)
                continue;
            if(dis[t] > dis[f] + c){
                dis[t] = dis[f] + c;
                pre[t] = e;
            }
        }
    /*
    REP(i, pre.size()){
        if(pre[i] != -1)
            //cout << "vertex " << i << " come from " << E[pre[i]].f << endl;
    }
    */
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
        E[pre[u] ^ 1].v += flowval;
        u = E[pre[u]].f;
    }
    return cost * flowval;
}

LL MCMF(int s){
//    cout << "new round MCMF\n";
    
    LL ans = 0; 

    LL val;
    while(val = BF(s, G.size())){
        //debug(val);
        ans += val; 
        //debug(ans);
    }
    return ans;
}

int main(){
    /*
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    */
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
        REP1(i, m * n){
            mul = n - (i - 1)/m;
            add_edge(0, i, 1, 0);
            LL cursize = msize[(i-1) % m];
            REP(j, n){
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
            /*
            if(i % m == 0){
                //debug(mul);
                mul--;
            }
            */
        }
        MCMF_t = (m + 1) * n + 1;
        REP(j, n){
            add_edge(m * n + j + 1, MCMF_t, 1, 0);
        }
        LL myans = MCMF(0);

        // generate period ans.
        mul = n;
        for(int i = m * n; i>0; i--){
            debug(i);
            int mid= (i - 1) % m;
            int ntask = n - (i - 1) / m - 1;
            debug(mid);
            debug(ntask);
            st[mid][ntask].F = 0;
            if(ntask != 0){
                st[mid][ntask].F = st[mid][ntask-1].S + 1;
            }
                debug(st[mid][ntask].F); 
            for(int &e: G[i]){
                if(E[e].v == 0 && E[e].t != 0){
                    debug(e);
                    debug(E[e].t);
                    taskAns[E[e].t - m * n - 1].F  = mid; 
                    taskAns[E[e].t - m * n - 1].S  = ntask; 
                    st[mid][ntask].S = st[mid][ntask].F + (E[e].c/(n - (i-1) / m));
                    break;
                }
            } 
        }
        // output
        cout << "Case " << Case++ << endl;
        cout << "Average turnaround time = " <<   myans/(double)n << endl;
        int mid, ntask;
        REP(j, n){
            mid = taskAns[j].F;
            ntask = taskAns[j].S;
            cout << "Program " << j + 1 << " runs in region ";
            debug(ntask);
            cout << mid + 1<< " from " << st[mid][ntask].F << " to "<< st[mid][ntask].S << endl;
        }
    }

    return 0;
}

