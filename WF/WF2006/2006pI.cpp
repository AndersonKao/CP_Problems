#include <bits/stdc++.h>
using namespace std;
template <typename T>
using vec = vector<T>;
using ll = long long;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define al(x) x.begin(), x.end()
#define eb emplace_back
#define debug(x) cout << #x << ":= " << x << endl;

const int INF = 10000;
using miter = map<string, int>::iterator;

int main(){
    int P;
    int R;
    int caseN = 1;
    while (cin >> P >> R)
    {
        if(P == 0 && R == 0)
            break;
        vec<vec<int>> G;
        map<string, int> nid;
        G.resize(P, vec<int>(P, INF));
        REP(i, P)
            G[i][i] = 0;
        int curP = 0;
        REP(i, R)
        {
            string ustr, vstr;
            cin >> ustr >> vstr;
            miter itu = nid.find(ustr);
            if(itu == nid.end()){
                nid[ustr] = curP++;
            }
            miter itv = nid.find(vstr);
            if(itv == nid.end()){
                nid[vstr] = curP++;
            }
            int u = nid[ustr], v = nid[vstr];
            G[u][v] = min(G[u][v], 1);
            G[v][u] = min(G[v][u], 1);
        }
        cout << "Network " << caseN++ << ": ";
        if (curP != P)
        {
            cout << "DISCONNECTED\n\n";
            continue;
        }

        for (int k = 0; k < P; k++){
            for (int i = 0; i < P; i++){
                for (int j = 0; j < P; j++){
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
                }
            }
        }

        int ANS = 0;
        bool disconnect = false;
        for (int i = 0; i < P; i++)
        {
            for (int j = 0; j < P; j++){
                if(G[i][j] == INF){
                    disconnect = true;
                    break;
                }
                ANS = max(ANS, G[i][j]);
            }
            if(disconnect)
                break;
        }
        if(disconnect) {
            cout << "DISCONNECTED\n";
        }
        else
            cout << ANS << endl;
        cout << endl;
    }
        return 0;
}