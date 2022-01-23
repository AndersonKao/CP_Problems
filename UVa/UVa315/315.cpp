// AC 2020-08-21 16:24:03
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <utility>
using namespace std;
#define MAX_N 200005;
#define enp pair<int, int> // edge-weight, node-index
#define con pair<int, int> // connection
class tarjan{
    vector<vector<int>> G;
    vector<int> D;
    vector<int> L;
    vector<int> APnodes;
    vector<con> edgeBridge;
    int timestamp;
public:
    void init(int size = 1){
        timestamp = 1;
        D.resize(size, 0);
        L.resize(size, 0);
        G.resize(size);
        APnodes.clear();
        edgeBridge.clear();
    }
    void addEdge(int u, int v){
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    void DFS(int v, int pa){
        D[v] = L[v] = timestamp++;
        // cout << "visiting " << v << " D set to " << D[v] << endl;
        int Childcount = 0;
        bool isAP = false;
        for(int w: G[v]){
            if(w == pa)
                continue;
            if(!D[w]){
                DFS(w, v);
                Childcount++;
                if(D[v] <= L[w])
                    isAP = true;
                L[v] = min(L[v], L[w]);
            }
            L[v] = min(L[v], D[w]);
        }
        if(v == pa && Childcount < 2)
            isAP = false;
        if(isAP)
            APnodes.emplace_back(v);
    }
    int APsize(){
        return APnodes.size();
    }
    void infor(int N){
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
        for(int u: APnodes){
            cout << u << " ";
        }
        cout << endl;
        cout << "connecttion\n";
        for (int i = 1; i <= N; i++){
            cout << i << ": ";
            for(int v: G[i]){
                cout << v << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};
int main(){
    int N;
    while(cin >> N){
        if(!N)
            break;
        int w, v;
        tarjan T;
        T.init(N + 5);
        string str;
        string num;
        cin.get();
        getline(cin, str);
        stringstream ss(str);
        while (ss >> w)
        {
            if(!w)
                break;
            while (ss >> v)
            {
                T.addEdge(w, v);
                // cout << "add " << w << " " << v << endl;
            }
            getline(cin, str);
            ss = stringstream(str);
        }
        T.DFS(1, 1);
        // cout << "ans: ";
        cout << T.APsize() << endl;
        // cout << "case done.\n";
        // T.infor(N);
    }
    // cout << "good finish\n";
    return 0;
}