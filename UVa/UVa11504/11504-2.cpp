// this one by kosaraju

// AC 2020-08-24 18:41:12
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
// #define TEST_LOCAL
vector<bool> visited;
vector<vector<int>> G;
vector<vector<int>> GT;
vector<vector<int>> reG;
vector<int> sccID;
vector<int> indeg;
int sccIDCounter;
stack<int> st;
void DFS(vector<vector<int>> *dG, int v, int k = -1)
{
    visited[v] = true;
    sccID[v] = k;
    for (int w : (*dG)[v])
    {
        if (!visited[w])
        {
            DFS(dG, w, k);
        }
    }
    if (dG == &G)
        st.push(v);
}

void kosaraju(int N)
{
    visited.clear();
    visited.resize(N + 5, false);
    for (int i = 1; i <= N; i++)
    {
        if (!visited[i])
            DFS(&G, i);
    }
    // cout << "generating sccID " << sccIDCounter << endl;
    visited.clear();
    visited.resize(N + 5, false);
    while (!st.empty())
    {
        int v = st.top();
        st.pop();
        if (!visited[v])
        {
            // cout << "start from " << v << endl;
            DFS(&GT, v, sccIDCounter++);
        }
    }
}
void init(int N)
{

    G.clear();
    G.resize(N + 5);
    GT.clear();
    GT.resize(N + 5);
    sccID.clear();
    sccID.resize(N + 5);
    reG.clear();
    indeg.clear();
    sccIDCounter = 1;
    while (!st.empty())
        st.pop();
}
int main()
{
#ifdef TEST_LOCAL
    freopen("test6.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    // std::ios_base::sync_with_stdio(false);
    // cin.tie(0);
    int T;
    int N;
    int Enum;
    cin >> T;
    
    while (T--)
    {
        // cout << "case" << T << endl;
        cin >> N >> Enum;
        init(N);
        int x, y;
        for (int i = 0; i < Enum; i++)
        {
            cin >> x >> y;
            G[x].emplace_back(y);
            GT[y].emplace_back(x);
        }
        kosaraju(N);
        // for (int i = 1; i <= N; i++)
        // {
        //     cout << sccID[i] << " ";
        // }
        // cout << endl;
        reG.resize(sccIDCounter + 1);
        indeg.resize(sccIDCounter + 1);
        for (int i = 1; i <= N; i++)
        {
            for (int w : G[i])
            {
                if (sccID[i] == sccID[w])
                    continue;
                reG[sccID[i]].emplace_back(sccID[w]);
                indeg[sccID[w]]++;
            }
        }
        int ans = 0;
        for (int i = 1; i < sccIDCounter; i++)
        {
            if (indeg[i] == 0)
                ans++;
        }
        cout << ans << endl;
    }
    return 0;
}