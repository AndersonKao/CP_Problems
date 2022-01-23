#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define edge tuple<double, int, int>

pii nodes[505];
vector<edge> Es;

struct DSU{
    int group[505];
    DSU(){
        for (int i = 0; i <= 500; i++)
            group[i] = i;

    }
    DSU(int N){
        for (int i = 0; i <= N; i++)
            group[i] = i;
    }
    void reset(int N){
        for (int i = 0; i <= N; i++)
            group[i] = i;
    }
    int find(int x){
        return (group[x] == x ? x : group[x] = find(x));
    }
    bool same(int x, int y){
        return find(x) == find(y);
    }
    void Union(int x, int y){
        group[find(x)] = find(y);
    }
};
DSU dsu;

int S, P;
double distance(pii a, pii b){
    double xdis = (double)a.first - (double)b.first;
    double ydis = (double)a.second - (double)b.second;
    return sqrt(xdis * xdis + ydis * ydis);
}

double solve(){
    int x, y;
    cin >> S >> P;
    dsu.reset(P);
    for (int i = 0; i < len; i++){
        cin >> x >> y;
        nodes[i] = pii(x, y);
        for (int j = i - 1; j >= 0; j--){
            Es.emplace_back(distance(nodes[i], nodes[j]), i, j);
        }

    } 
    sort(Es.begin(), Es.end());
    double dis;
    double ans = 0.0;
    int cnt = 0;
    for(auto e: Es){
        tie(dis, x, y) = e;
        if(dsu.same(x, y))
            continue;
        dsu.Union(x, y);
        ans = max(ans, dis);
        cnt++;
        if(cnt == ((P-1) - (S-1)))
            break;
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    cout << std::fixed << setprecision(2);
    while(T--){
        Es.clear();
        cout << solve() << endl;
    }
    return 0;
}