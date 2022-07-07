// AC
#include <bits/stdc++.h>
using namespace std;

template <typename T>
using vec = vector<T>;
using ll = long long;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define al(x) x.begin(), x.end()
#define eb emplace_back
vec<vec<int>> tickets;
vec<int> tcost;
vec<int> target;
vec<vec<tuple<int, int, int>>> G; // to ,weight , ticket id;
int citiessize;
// vertex id = i + j * citiessize for f(i, j),  now on city i,  complete first j target;
// our and
void buildGraph()
{
    G.clear();
    G.resize(target.size() * citiessize);
    for (int i = 0; i < (int)tickets.size(); i++)
    {
        int st = tickets[i][0];
        for (int j = 1; j < (int)tickets[i].size(); j++){ // getdown at j-th city 
            int ed = tickets[i][j];
            for (int cj = 0; cj < (int)target.size(); cj++){ // start from (st, cj)
                int subseqSize = 0;
                int idx = cj+1;
                for (int ti = 0; ti <= j; ti++) // check end in (ed, cj + subseqsize);
                {
                    if(idx >= target.size())
                        break;
                    if (tickets[i][ti] == target[idx])
                    {
                        idx++, subseqSize++;
                    }
                }
                int u = st + cj * citiessize;
                int v = ed + (cj + subseqSize) * citiessize;
                if(u >= G.size() || v>= G.size())
                    continue;
                G[u].eb(v, tcost[i], i);
            }
        }
    }
}

using pil = pair<ll, int>;
using pii = pair<int, int>;
vec<pair<int, int>> from;
vec<ll> Distance;
#define debug(x) cout << #x << ":= " << x << endl;
void dijkstra(int st)
{
    from.clear();
    from.resize(target.size() * citiessize);
    Distance.clear();
    Distance.resize(target.size() * citiessize, 100000 * target.size() * citiessize);
    //debug(st);
    Distance[st] = 0;
    from[st] = {-1, -1};
    priority_queue<pil, vec<pil>, greater<pil>> Q;
    Q.emplace(0, st);
    while (!Q.empty())
    {
        int u;
        ll dis;
        tie(dis, u) = Q.top();
        //debug(u);
        Q.pop();
        if(dis != Distance[u])
            continue;
        for(auto& edge: G[u]){
            ll w;
            int v, tid;
            tie(v, w, tid) = edge;
            if (dis + w < Distance[v])
            {
                Distance[v] = dis + w;
                Q.emplace(dis + w, v);
                from[v] = {u, tid};
            }
        }
    }
}
int main()
{
    int NT, NI;
    int Casen = 0;
    while (cin >> NT)
    {
        Casen++;
        if (NT == 0)
            break;
        tickets.resize(NT);
        tcost.resize(NT);
        vec<int> cities;
        REP(i, NT)
        {
            int n;
            cin >> tcost[i];
            cin >> n;
            tickets[i].resize(n);
            REP(j, n){
                cin >> tickets[i][j];
                tickets[i][j]--;
                cities.eb(tickets[i][j]);
            }
        }
        sort(al(cities));
        cities.resize(distance(cities.begin(), unique(al(cities))));
        citiessize = cities.size();
        REP(i, NT){
            REP(j, tickets[i].size()){
                tickets[i][j] = lower_bound(al(cities), tickets[i][j]) - cities.begin();
            }
        }
        cin >> NI;
        REP(roundT, NI){
            int RN;
            cin >> RN;
            target.resize(RN);
            for (int &e : target){
                cin >> e;
                e--;
                e = lower_bound(al(cities), e) - cities.begin();
            }

            buildGraph();
            #ifdef DebugG
            for (int u = 0; u < G.size(); u++){
                cout << "vertex " << u << ": \n";
                for (auto&e: G[u]){
                    ll w, v, tid;
                    tie(v, w, tid) = e;
                    cout << "(" << v << ", " << w << ", " << tid <<"), ";
                }
                cout << endl;
            }
            #endif
            int st = target[0];
            dijkstra(st);
            int ed = target.back() + (target.size() - 1) * citiessize;
            stack<int> tans;
            int edans = ed;
            while (ed != st)
            {
                tans.emplace(from[ed].second);
                ed = from[ed].first;
            }
//            tans.pop();
            cout << "Case " << Casen << ", Trip " << roundT + 1 << ": Cost = " << Distance[edans] << endl;
            cout << "  Tickets used:";
            while(!tans.empty()){
                cout << " " << tans.top() + 1;
                tans.pop();
            }
            cout << endl;
        }
    }
    return 0;
}