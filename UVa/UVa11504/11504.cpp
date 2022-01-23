// AC 2020-08-24 00:29:28
// remember to consider all Indeg = 0 case;

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <utility>
using namespace std;
#define LOCAL_TEST
#define con pair<int, int>
// by atsushi from sylveon's template
class tarjan_for_SCC{
private:
    vector<vector<int>> G; // adjacency list
    vector<int> D;
    vector<int> L;
    vector<int> sccID;
    stack<int> st; // for SccID
    vector<int> sccNode;
    vector<bool> inSt;
    vector<vector<int>> reG;
    int timeStamp, sccIDstamp;
public:
    void init(int size = 1){
        G.clear();
        G.resize(size + 5);
        D.clear();
        D.resize(size + 5, 0);
        L.clear();
        L.resize(size + 5, 0);
        sccID.clear();
        sccID.resize(size + 5, 0);
        while(!st.empty())
            st.pop();
        sccNode.clear();
        inSt.clear();
        inSt.resize(size + 5, false);
        reG.clear();
        sccIDstamp = timeStamp = 1;
    }
    void addEdge(int from, int to){
        G[from].emplace_back(to);
    }
    void DFS(int v, int pa){ //call DFS(v,v) at first
        
        D[v] = L[v] = timeStamp++; //timestamp > 0
        st.push(v);
        inSt[v] = true;

        for(int w: G[v]){
            // if(w == pa) // directed graph don't need this
            //     continue;
            if(D[w] == 0){ // D[w] = 0 if not visited
                DFS(w, v);
                L[v] = min(L[v], L[w]);
            }else if(inSt[w])
            { /* w has been visited.
                if we don't add this, the L[v] will think that v can back to node whose index less to v.
                !inSt[w] is true that v -> w is a forward edge
                opposite it's a cross edge
            */
                L[v] = min(L[v], D[w]); // why D[w] instead of L[w]??
            }
        }
        if(D[v] == L[v]){
            int w;
            do{
                w = st.top();
                st.pop();
                sccID[w] = sccIDstamp; // scc ID for this pooint at which SCC
                inSt[w] = false;
            } while (w != v);
            sccIDstamp++;
            // sccNode.emplace_back(v);
        }
    }
    void generateReG(int N = 1){
        reG.clear();
        reG.resize(sccIDstamp);
        for (int i = 1; i <= N; i++){
            for(int w: G[i]){
                if(sccID[i] == sccID[w])
                    continue;
                reG[sccID[i]].emplace_back(sccID[w]);
            }
        }
    }
    int ans(){
        int inNum = 0;
        // cout << "sccIdstamp: " << sccIDstamp << endl;
        vector<bool> in;
        in.resize(sccIDstamp+5, false);
        for (int i = 1; i < sccIDstamp; i++){
            for(int w:reG[i]){
                in[w] = true;
            }
        }
        for (int i = 1; i < sccIDstamp; i++){
            if(!in[i])
                inNum++;
        }
        // if(!inNum)  // for if reG is a circle, but this is impossible
            // return 1;
        return inNum;
    }
    bool visited(int v){
        return D[v];
    }
    void infor(int N = 1){
        cout << "D: ";
        for (int i = 1; i <= N; i++){
            cout << D[i] << " ";
        }
        cout << endl;
        cout << "L: ";
        for (int i = 1; i <= N; i++){
            cout << L[i] << " ";
        }
        cout << endl;
        cout << "SccID: ";
        for (int i = 1; i <= N; i++){
            cout << sccID[i] << " ";
        }
        cout << endl;
        cout << "reG's edges: ";
        for (int i = 1; i < sccIDstamp; i++){
            cout << i << ": ";
            for(int w: reG[i]){
                cout << w << " ";
            }
            cout << endl;
        }
    }
};
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    #ifdef LOCAL_TEST
        freopen("test6.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
#endif
    int T;
    int N;
    int Enum, x, y;
    vector<int> inEdge;
    cin >> T;
    tarjan_for_SCC tj;
    while(T--){
        cin >> N >> Enum;
        inEdge.clear();
        inEdge.resize(N + 5, 0);
        tj.init(N);

        for (int i = 0; i < Enum; i++)
        {
            cin >> x >> y;
            tj.addEdge(x, y);
            inEdge[y]++;
        }
        int MinIn = 1000005;
        for (int i = 1; i <= N; i++){
            MinIn = min(MinIn, inEdge[i]);
        }
        for (int i = 1; i <= N; i++)
        {
            if (inEdge[i] == MinIn && !tj.visited(i))
            {
                tj.DFS(i, i);
            }
        }
        tj.generateReG(N);
        cout << tj.ans() << endl;
    }
    return 0;
}