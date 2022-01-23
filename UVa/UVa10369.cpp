#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define edge tuple<int, int, int>

vector<pii> nodes;
vector<edge> Es;

struct DSU{
    int group[10005];
    DSU(int N){
        for (int i = 0; i <= N; i++){
            group[i] = i;
        }
    }
    int find(int x){
        return (group[x] == x ? x : group[x] = find(group[x]));
    }
    bool same(int x, int y){
        return find(x) == find(y);
    }
    void Union(int x, int y){
        group[find(x)] = find(y);
    }
};

int S, P;
int distance(pii a, pii b){
    int xdis = a.first - b.first;
    int ydis = a.second - b.second;
    return (xdis * xdis + ydis * ydis);
}

double solve(){
    int x, y;
    cin >> S >> P;
    priority_queue<edge, vector<edge>, greater<edge>> Q;
    for (int i = 0; i < P; i++){
        cin >> x >> y;
        nodes.emplace_back(x, y);
        for (int j = i - 1; j >= 0; j--)
            Q.emplace(distance(nodes[i], nodes[j]), i, j);
    }

    DSU dsu(P);
    int ans = 0.0;
    int cnt = 0;
    while(!Q.empty()){
        tie(ans, x, y) = Q.top();
        Q.pop();
        if(dsu.same(x, y))
            continue;
        dsu.Union(x, y);
        cnt++;
        if(cnt == ((P-1) - (S-1)))
        {
            return sqrt(ans);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--){
        nodes.clear();
        Es.clear();
        cout << std::fixed << std::setprecision(2) << solve() << endl;
    }
    return 0;
}
