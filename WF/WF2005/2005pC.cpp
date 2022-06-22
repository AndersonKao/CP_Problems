#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
using ll = long long;
using edge = tuple<ll, int, int>;
template <typename T>
using vec = vector<T>;
#define eb emplace_back
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << " >= " << x << endl;
struct Disj
{
    vec<int> pa;
    Disj(int n){
        pa.resize(n);
        REP(i, n){
            pa[i] = i;
        }
    }
    bool sameSet(int u, int v){
        return getSet(u) == getSet(v);
    }
    int getSet(int u){
        if(pa[u] == u)
            return u;
        return pa[u] = getSet(pa[u]);
    }
    void merge(int u, int v){
        int k= getSet(v);
        pa[k] = getSet(u);
    }
};
bool DFS(vec<vec<int>>&G, int u, int ed, int pa){
    if(u == ed){
        cout << ed+1 << "-";
        return true;
    }
    for(int&v: G[u]){
        if(v == pa)
            continue;
        if(DFS(G, v, ed, u)){
            cout << u+1;
            if(pa != -1)
                cout << "-";
            return true;
        }
    }
    return false;
}
void normalDFS(vec<vec<int>>&G,vec<bool>&vis, int u, int pa){
    vis[u] = true;
    for (int &v : G[u])
    {
        if(v == pa)
            continue;
        normalDFS(G, vis, v, u);
    }
}
bool valid(vec<vec<int>>&G, vec<int> Js,int  DC,int NC){
    vec<bool>vis(NC, false);
    normalDFS(G, vis, DC, -1);
    for(int&e: Js){
        if(!vis[e])
            return false;
    }
    return true;
}
int main()
{
    int NC, DC, NR, NJ;
    int caseN = 1;
    while (cin >> NC)
    {
        if(NC == -1)
            break;
        cin >> DC >> NR;
        DC--;
        vec<edge> E;
        vec<int> Js;
        REP(i, NR)
        {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            E.eb(w, u, v);
        }
        sort(al(E));
        #ifdef Dedge
        for(auto e: E){
            int w, u, v;
            tie(w, u, v) = e;
            cout << "edge: " << u << ", " << v << " with w = " << w << endl;
        }
        #endif
        cin >> NJ;
        Js.resize(NJ);
        vec<bool> isJ(NC, false);
        REP(i, NJ){
            cin >> Js[i];
            Js[i]--;
            isJ[Js[i]] = true;
        }
        isJ[DC] = true;
        int nonJC = NC - NJ - 1;
        //debug(nonJC);
        int bitset;
        vec<vec<int>> vG;
        ll ans = numeric_limits<ll>::max();
        //string ansstr(NC);
        for (bitset = (1 << nonJC) - 1; bitset >= 0; bitset--)
        {
            vec<bool> avail(NC, true);
            vec<vec<int>> G(NC);
            int sh = 0;
            for (int i = 0; i < NC; i++)
            {
                if(!isJ[i]){
                    if(bitset & (1 << sh)){
                        avail[i] = false;
                    }
                    sh++;
                }
            }

            Disj Set(NC);
            ll cost = 0;
            int idx = -1;
            int Enum = 0;
            for (edge &e : E)
            {
                idx++;
                int u, v, w;
                tie(w, u, v) = e;
                if(!avail[u] || !avail[v])
                    continue;
//                cout << Set.getSet(u) << ", " << Set.getSet(v) << endl;
                if (Set.sameSet(u, v))
                    continue;
 //               cout << "add edge " << u << ", " << v << endl;
                Set.merge(u, v);
  //              cout << Set.getSet(u) << ", " << Set.getSet(v) << endl;
                cost += w;
                G[u].eb(v);
                G[v].eb(u);
                Enum++;
            }
            if(Enum < NJ+1-1)
                continue;
            if(!valid(G, Js, DC, NC)){
                continue;
            }
            if(cost < ans){
                ans = cost;
                vG = G;
            }
            else{

            }
            #ifdef bugG
            REP(i, NC){
                cout << i << "'s neigth: ";
                for(int a: G[i]){
                    cout << a << " ";
                }
                cout << endl;
            }
            cout << "cost: " << cost << endl;
            #endif
            /*
            */
        }
        #ifdef Dans
        REP(i, NC)
        {
            cout << i << "'s neigth: ";
            for (int a : vG[i])
            {
                cout << a << " ";
            }
            cout << endl;
        }
        #endif
        cout << "Case " << caseN++ << ": distance = " << ans << endl;
        REP(i, NJ)
        {
            vec<int> ans;
            cout << "   ";
            DFS(vG, DC, Js[i], -1);
            cout << endl;
        }
        cout << endl;
    }
}