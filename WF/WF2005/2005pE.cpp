// AC 2022-06-22 17:26:02
#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
#define F first
#define S second
template <typename T>
using vec = vector<T>;
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << " := " << x << endl;
const double PI = 3.14159265;
using ll = long long;

int main(){
    int n;
    const int st = (60 * 5 + 37)*60;
    const int ed = (60 * 18 + 17)*60;
    int caseN = 1;
    while (cin >> n)
    {
        if(!n)
            break;
        ll w, h;
        cin >> w >> h;
        vec<ll> m(n), d(n), pre(n);

        REP(i, n-1){
            cin >> m[i] >> d[i];
        }
        cin >> m[n - 1];
        pre[0] = 0;
        for (int i = 1; i < n; i++)
            pre[i] = pre[i - 1] + d[i - 1];

        int query;
        cout << "Apartment Complex: " << caseN++ << endl;
        while (cin >> query){
            if(query == 0)
                break;
            double ltheta = 0.0, rtheta =  0.0;
            int qi = query % 100 - 1; // which building 0-index
            int qm = query / 100; // which floor 1-index
            #ifdef Ddebug
            debug(qi);
            debug(qm);
            #endif
            if (query < 100 || qi >= m.size() || qm > m[qi]) {
                cout << "Apartment " << query << ": Does not exist\n";
                continue;
            }

            for (int i = 0; i < qi; i++)
            {
                if(m[i] <= (qm - 1))
                    continue;
                int ih = (m[i] - (qm-1)) * h;
                int iw = pre[qi] - pre[i] + w * (qi- i - 1);
                #ifdef Ddebug
                cout << "i: " << i << endl;
                debug(ih);
                debug(iw);
                #endif
                ltheta = max(ltheta, atan(ih / (double)iw));
            }
            for (int i = qi +  1; i < n; i++)
            {
                if(m[i] <= (qm - 1))
                    continue;
                int ih = (m[i] - (qm-1)) * h;
                int iw = pre[i] - pre[qi] + w * (i-qi - 1);
                #ifdef Ddebug
                cout << "i: " << i << endl;
                debug(ih);
                debug(iw);
                #endif
                rtheta = max(rtheta, atan(ih / (double)iw));
            }
            #ifdef Ddebug
            debug(ltheta);
            debug(rtheta);
            #endif
            int ansst = floor(st + (ltheta / PI) * (ed - st));
            int ansed = floor(st + (1- (rtheta / PI)) * (ed - st));
            #ifdef Ddebug
            debug(ansst);
            debug(ansed);
            #endif
            int sth = ansst / 3600;
            int stm = (ansst % 3600) / 60;
            int sts = (ansst % 60);
            int edh = ansed / 3600;
            int edm = (ansed % 3600) / 60;
            int eds = (ansed % 60);
            //            cout << endl;
            cout << "Apartment " << query << ": ";
            cout << setw(2) << setfill('0') << sth << ":" << setw(2) << setfill('0') << stm << ":" << setw(2) << setfill('0') << sts;
            cout << " - ";
            cout << setw(2) << setfill('0') << edh<< ":" << setw(2) << setfill('0') << edm<< ":" << setw(2) << setfill('0') << eds;
            cout << endl;
        }
    }

        return 0;
}
