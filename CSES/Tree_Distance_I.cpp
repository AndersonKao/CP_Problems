// AC
// 每次做完這個node的答案後，把這個node的edge做排序，整體是O(V+E+ElogE)
// TLE
// 以1為root，2~n都接在n上面，那麼每次都去找parent的答案會到O(N^2)
#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;
vector<vector<PII>> G;
vector<int> maxD;
vector<int> ANS;
void DFSdepth(int now, int p){
    int ans = 0;
    int u, Eans;
    for(auto& e: G[now]){
        tie(Eans, u) = e;
        if(u == p)
            continue;
        DFSdepth(u, now);
        ans = max(ans, maxD[u] + 1);
    }
    maxD[now] = ans;
}
void DFSans(int now, int p){
    int ans = 0;
    int u, Eans;
//    cout << "at vertex " << now + 1 << ": ";
    for(auto& e:G[now]){
        tie(Eans, u) = e;
        if(u == p){
            int tmp = 0;
            int pu, pEans;
            for(auto& pe: G[u]){
                tie(pEans, pu) = pe;
                if(pu == now)
                    continue;
                //cout << "(" << pu + 1<<", " << pEans << "), ";
                tmp = max(tmp, pEans);
                break;
            }
//            cout << endl;
            e.first = tmp + 1; // 1 for u to v;
        }
        else{
            e.first = maxD[u] + 1;
        }
        ans = max(e.first, ans);
    }
    sort(G[now].begin(), G[now].end(), greater<PII>());
    for(auto& e:G[now]){
        tie(Eans, u) = e;
        if(u != p)
            DFSans(u, now);
    }
    ANS[now] = ans;
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    G.resize(N);
    maxD.resize(N);
    ANS.resize(N);
    int u, v;
    for (int i = 0; i < N - 1; i++){
        cin >> u >> v;
        u--, v--;
        G[u].emplace_back(0, v);
        G[v].emplace_back(0, u);
    }
    DFSdepth(0, -1);
    DFSans(0, -1);
    for (int i = 0; i < N; i++){
        cout << ANS[i] << (i == N - 1 ? "\n" : " ");
    }
        return 0;
}