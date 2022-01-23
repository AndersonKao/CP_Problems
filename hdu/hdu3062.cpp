// by atsushi
// AC 2020-08-25 15:28:40
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <stack>
using namespace std;
// #define LOCAL_TEST
class tarjan_for_SCC
{
private:
    vector<vector<int>> G; // adjacency list
    vector<int> D;
    vector<int> L;
    vector<int> sccID;
    stack<int> st; // for SccID
    vector<bool> inSt;
    vector<vector<int>> reG;
    int timeStamp, sccIDstamp;

public:
    void init(int size = 1)
    {
        G.clear();
        G.resize(size + 5);
        D.clear();
        D.resize(size + 5, 0);
        L.clear();
        L.resize(size + 5, 0);
        sccID.clear();
        sccID.resize(size + 5, 0);
        while (!st.empty())
            st.pop();
        inSt.clear();
        inSt.resize(size + 5, false);
        reG.clear();
        sccIDstamp = timeStamp = 1;
    }
    void addEdge(int from, int to)
    {
        G[from].emplace_back(to);
    }
    void DFS(int v, int pa)
    {                              //call DFS(v,v) at first
        D[v] = L[v] = timeStamp++; //timestamp > 0
        st.push(v);
        inSt[v] = true;

        for (int w : G[v])
        { // directed graph don't need w == pa
            if (!D[w])
            { // D[w] = 0 if not visited
                DFS(w, v);
                L[v] = min(L[v], L[w]);
            }
            else if (inSt[w])
            {                           /* w has been visited.
                if we don't add this, the L[v] will think that v can back to node whose index less to v.
                !inSt[w] is true that v -> w is a forward edge
                opposite it's a cross edge
            */
                L[v] = min(L[v], D[w]); // why D[w] instead of L[w]??
            }
        }
        if (D[v] == L[v])
        {
            int w;
            do
            {
                w = st.top();
                st.pop();
                sccID[w] = sccIDstamp; // scc ID for this pooint at which SCC
                inSt[w] = false;
            } while (w != v);
            sccIDstamp++;
        }
    }
    void infor(int N)
    {

        cout << "G: \n";
        for (int i = 0; i < N; i++)
        {
            cout << i << ": ";
            for (int w : G[i])
            {
                cout << w << " ";
            }
            cout << '\n';
        }
        cout << "D:";
        for (int i = 0; i < N; i++)
        {
            cout << D[i] << " ";
        }
        cout << endl;
        cout << "L:";
        for (int i = 0; i < N; i++)
        {
            cout << L[i] << " ";
        }
        cout << endl;
        cout << "sccID:";
        for (int i = 0; i < N; i++)
        {
            cout << sccID[i] << " ";
        }
        cout << endl;
    }
    int getsccID(int v)
    {
        return sccID[v];
    }
    bool visited(int v)
    {
        return D[v];
    }
};

int main()
{
#ifdef LOCAL_TEST
    freopen("test1.txt", "r", stdin);
#endif
    int N, Enum;
    // std::ios_base::sync_with_stdio(false);
    // cin.tie(0);
    tarjan_for_SCC tj;
    while (~scanf("%d %d", &N, &Enum))
    {
        int A1, A2, B1, B2;
        int A1wifu, A2wifu, A1hus, A2hus;
        // vector<int> indeg;
        tj.init(2 * N);
        // indeg.resize(2 * N, 0);
        // A + N for husband, A for wifu

        for (int i = 0; i < Enum; i++)
        {
            scanf("%d%d%d%d", &A1wifu, &A2wifu, &B1, &B2);
            // cin >> A1wifu >> A2wifu >> B1 >> B2;

            A1hus = A1wifu + N;
            A2hus = A2wifu + N;
            if (B1 && B2)
            {
                tj.addEdge(A1hus, A2wifu);
                tj.addEdge(A2hus, A1wifu);
                // indeg[A2wifu]++;
                // indeg[A1wifu]++;
            }
            else if (B1 && !B2)
            {
                tj.addEdge(A1hus, A2hus);
                tj.addEdge(A2wifu, A1wifu);
                // indeg[A2hus]++;
                // indeg[A1wifu]++;
            }
            else if (!B1 && B2)
            {
                tj.addEdge(A1wifu, A2wifu);
                tj.addEdge(A2hus, A1hus);
                // indeg[A2wifu]++;
                // indeg[A1hus]++;
            }
            else
            {
                tj.addEdge(A1wifu, A2hus);
                tj.addEdge(A2wifu, A1hus);
                // indeg[A2hus]++;
                // indeg[A1hus]++;
            }
        }
        // sort(indeg.begin(), indeg.end());
        // int MinIn = 1000000000;

        // cout << "MinIn: " << MinIn << endl;
        for (int i = 0; i < 2 * N; i++)
        {
            if (!tj.visited(i))
                tj.DFS(i, i);
        }
        // cout << endl;
        // tj.generateReG(2 * N);
        // tj.infor(2 * N);
        for (int i = 0; i < N; i++)
        {
            if (tj.getsccID(i) == tj.getsccID(i + N))
            {
                cout << "NO\n";
                break;
                // return 0;
            }else if(i == N-1){
                cout << "YES\n";
            }
        }
    }
    return 0;
}