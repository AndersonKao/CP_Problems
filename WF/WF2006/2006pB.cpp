#include <bits/stdc++.h>
using namespace std;

template <typename T>
using vec = vector<T>;
using ll = long long;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define al(x) x.begin(), x.end()
#define eb emplace_back
#define debug(x) cout << #x << ":= " << x << endl;

struct edge
{
    int f, t;
    ll cap;
    ll cost;
    edge()
    {
        f = t = cost = cap = 0;
    }
    edge(int f, int t, ll cap, ll cost):f(f), t(t), cap(cap), cost(cost){}
};

vec<vec<int>> G;
vec<edge> E;
void add_edge(int f, int t, ll cap, ll cost)
{
    G[f].eb(E.size());
    E.eb(f, t, cap, cost);
    G[t].eb(E.size());
    E.eb(t, f, 0, -cost);
}
const ll capINF = 10000000LL;
const ll disINF = 10000000LL;
const ll costINF = 1000000LL;
vec<ll> dis;
vec<bool> inQ;
vec<int> pre;

pair<ll, ll> BF(int st, int ed, int N){
    fill(al(dis), disINF);
    fill(al(inQ), false);
    fill(al(pre), -1);
    dis[st] = 0;
    queue<int> Q;
    Q.emplace(st);
    inQ[st] = true;
    int f, t;
    ll cost, cap;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop(), inQ[u] = false;
        for(int &eid: G[u]){
            f = E[eid].f, t = E[eid].t, cost = E[eid].cost, cap = E[eid].cap;
            if(cap <= 0)
                continue;
            if(dis[t] > dis[f] + cost){
                dis[t] = dis[f] + cost;
                pre[t] = eid;
                if(inQ[t] == false)
                    Q.emplace(t), inQ[t] = true;
            }
        }
    }

    if(pre[ed] == -1){
        #ifdef DBF
        debug("no augment path");
        #endif
        return {0, 0};
    }
    int res = ed;
    ll flowval = capINF;
    ll totalCost = 0;
    int eid;
    while (res != st)
    {
        eid = pre[res];
        #ifdef DBF
        debug(res);
        debug(E[eid].cap);
        debug(E[eid].cost);
        #endif
        flowval = min(flowval, E[eid].cap);

        totalCost += E[eid].cost;
        res = E[eid].f;
    }
    res = ed;
    while(res != st){
        eid = pre[res];
        E[eid].cap -= flowval;
        E[eid ^ 1].cap += flowval;
        res = E[eid].f;
    }
    return {totalCost * flowval, flowval};
}
pair<ll, ll> MCMF(int st, int ed){
    ll ans = 0;
    ll fans = 0;
    ll val;
    ll f;
    while(true){
        tie(val, f) = BF(st, ed, G.size());
        if(val == 0)
            break;
        ans += val;
        fans += f;
        #ifdef DMCMF
        debug(val);
        debug(f);
        #endif
    }
    return {ans, fans};
}

int main(){

    int P, I;
    int caseN = 1;
    while (cin >> P >> I)
    {
        if(P == 0 && I == 0)
            break;
        G.clear();
        G.resize(2 + P + I);
        dis.resize(2 + P + I);
        inQ.resize(2 + P + I);
        pre.resize(2 + P + I);
        E.clear();
        int source = 0, terminal = 1 + P + I;
        REP(i, P)
        {
            ll cap;
            cin >> cap;
//            pie.eb(cap);
            add_edge(source, i + 1, cap, 0);
        }
        REP(i, I){
            ll cap;
            cin >> cap;
//            ice.eb(cap);
            add_edge(i + P + 1, terminal, cap, 0);
        }
        REP(i, P){
            int st = i + 1;
            REP(j, I)
            {
                int ed = P + 1 + j;
                double cost;
                cin >> cost;
                /*
                string str;
                cin >> str;
                if(str == "-1")
                    continue;
                ll llcost = 0;
                int deci = 0;
                bool isdeci = false;
                for (int i = 0; i < str.length();i++)
                {
                    if(str[i] == '.'){
                        isdeci = true;
                        continue;
                    }
                    if(isdeci)
                        deci++;
                    llcost *= 10;
                    llcost += (str[i] - '0');
                }
                REP(i, 2-deci)
                    llcost *= 10;
                    */
                /*
                debug(str);
                debug(llcost);
                */

                //                debug(cost);
                //                debug((ll)round(cost * 100.0));
                                ll llcost = (ll)round(cost * 100.0);
                                if (llcost == -100)
                                   continue;
                // debug(cost);
                add_edge(st, ed, capINF, llcost);
            }
        }
        vec<edge> cpE = E;
        pair<ll, ll> Rawans = MCMF(source, terminal);
        #ifdef Doutput
        debug(Rawans.first);
        debug(Rawans.second);
        #endif
        double Minans = Rawans.first / 100.0;
        E = cpE;

        for(auto& edge: E){
            if (edge.cost == 0){

                if(edge.f == 0)
                    edge.cost = costINF;
                else if(edge.t == 0)
                    edge.cost = -costINF;
                else if(edge.t == 1 + P + I)
                    edge.cost = costINF;
                else if (edge.f == 1 + P + I)
                    edge.cost = -costINF;
                continue;
            }
            if(edge.cost > 0)
                edge.cost = costINF - edge.cost;
            else
                edge.cost = -costINF - edge.cost;
        }
        Rawans = MCMF(source, terminal);
        #ifdef Doutput
        debug(Rawans.first);
        debug(Rawans.second);
        #endif
        double Maxans = (3*costINF * Rawans.second - Rawans.first) / 100.0f;

        cout << "Problem " << caseN++ << ": " << fixed << setprecision(2)<< Minans << " to " << Maxans << endl;
    }

        return 0;
}