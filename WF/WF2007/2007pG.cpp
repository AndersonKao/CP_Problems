// AC one shot 2022-07-08 19:29:10
#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second
#define eb emplace_back
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << ":= " << x << endl;
template <typename T>
using vec = vector<T>;
using piii = tuple<int, int, int>;

#define REP(i, n) for (int i = 0; i < (int)n; i++)
using pii = pair<int, int>;
int main()
{
    int N, M;
    int caseN = 1;
    while (cin >> N >> M)
    {
        if(N == 0 && M == 0)
            break;
        vec<set<pii>> Vs(N);
        vec<piii> base;
        vec<int> bytes(N);
        vec<int> permu(N);
        REP(i, N)
        {
            cin >> bytes[i];
            permu[i] = i;
        }
        REP(i, M)
        {
            int id, l, r;
            cin >> id >> l >> r;
            id--;
            base.eb(id, l, r);
        }
        int ANS = numeric_limits<int>::max();
        do
        {
            #ifdef Dpremu
            for(int e: permu)
                cout << e << " ";
            cout << endl;
            #endif
            Vs.clear();
            Vs.resize(N);
            int pid = 0;
            int ntbyte = 1;
            int cursize = 0;
            int anssize = 0;
            for (int bid = 0; bid < M; bid++)
            {
                int id, l, r;
                tie(id, l, r) = base[bid];
                //debug(pid);
                if (id == permu[pid] && l == ntbyte)
                {
                    if(r == bytes[id]){
                        pid++;
                        ntbyte = 1;
                    }
                    else{
                        ntbyte = r + 1;
                    }
                    if(pid >= N)
                        continue;
                    id = permu[pid];
                    set<pii> &myS = Vs[id];
                    set<pii>::iterator t;
                    while (!myS.empty() && (t= myS.begin())->F == ntbyte)
                    {
                        ntbyte = t->S + 1;
                        cursize -= (t->S - t->F + 1);
                        myS.erase(t);
                        if(ntbyte-1 == bytes[id]){
                            pid++;
                            if(pid >= N)
                                break;
                            id = permu[pid];
                            myS = Vs[id];
                            ntbyte = 1;
                        }
                    }
                }
                else{
                    Vs[id].emplace(l, r);
                    cursize += (r - l + 1);
                    anssize = max(cursize, anssize);
                }
            }
            ANS = min(anssize, ANS);
        } while (next_permutation(al(permu)));
        cout << "Case " << caseN++ << ": " << ANS << "\n\n";
    }
    return 0;
}