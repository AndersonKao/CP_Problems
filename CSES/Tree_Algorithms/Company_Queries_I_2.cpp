// AC 2022-02-28 10:10:06
// Offline Way
#include <bits/stdc++.h>
using namespace std;

int N, Q;
int sti;
int Mstack[200000];
vector<vector<int>> G;
vector<int> Queries; // jumpsteps
vector<vector<int>> QID;
vector<int> ANS;
void DFS(int now, int p)
{
    Mstack[sti] = now;
    // queries
    for(auto& qid: QID[now]){
        if(Queries[qid] > sti)
            ANS[qid] = -2;
        else
            ANS[qid] = Mstack[sti - Queries[qid]];
    }
    sti++;

    for (auto &u: G[now]){
        if(u == p)
            continue;
        DFS(u, now);
    }
    sti--;
}
int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N >> Q;
    G.resize(N);
    QID.resize(N);
    ANS.resize(Q);
    int u;
    for (int i = 1; i < N; i++)
    {
        cin >> u;
        u--;
        G[u].emplace_back(i);
    }
    int q;
    for (int i = 0; i < Q; i++)
    {
        cin >> u >> q;
        u--;
        QID[u].emplace_back(Queries.size());
        Queries.emplace_back(q);
    }
    sti = 0;
    DFS(0, -1);
    for (int i = 0; i < Q; i++){
        cout << ANS[i] + 1 << (i == Q - 1 ? "\n" : " ");
    }

        return 0;
}
