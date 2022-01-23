#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define LL long long
int N, K, M;
vector<tuple<int, int, int>> E; // w, u ,v
struct DSU{
    int pa[1000001];
    DSU(int N){
        for (int i = 0; i <= N; i++)
            pa[i] = i;
    }
    int find(int k) { return pa[k] = (pa[k] == k ? k : find(pa[k])); }
    void merge(int x, int y){
        int pax = find(x), pay = find(y);
        pa[pay] = pax;
    }
};
int kruskalMST(){
    DSU dsu(N);
    sort(E.begin(), E.end());
    int cnt = 0;
    int ans = 0;
    for(auto e: E){
        int w, u, v;
        tie(w, u, v) = e;
        if(dsu.find(u) == dsu.find(v))
            continue;
        ans += w;
        dsu.merge(u, v);
        cnt++;
        /*
        if(cnt == N-1)
            break;
        */
    }
    if(cnt != N-1)
        return -1;
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    int u, v, w;
    bool first = false;
    while(cin >> N)
    {
        if(first)
            cout << "\n";
        first = true;

        E.clear();
        int preANS = 0;
        for (int i = 0; i < N - 1; i++){
            cin >> u >> v >> w;
            preANS += w;
        }
        cout << preANS << endl;
        
        cin >> K;
        int start = -1;
        for (int i = 0; i < K; i++){
            cin >> u >> v >> w;
            if(start == -1)
                start = u;
            E.emplace_back(w, u, v);
        }
        cin >> M;
        for (int i = 0; i < M; i++)
        {
            cin >> u >> v >> w;
            E.emplace_back(w, u, v);
        }
        cout <<  kruskalMST()<< endl;
    }

        return 0;

}