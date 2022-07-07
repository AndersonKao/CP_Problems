#include <bits/stdc++.h>
using namespace std;
template <typename T>
using vec = vector<T>;
using ll = long long;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define al(x) x.begin(), x.end()
#define eb emplace_back
#define debug(x) cout << #x << ":= " << x << endl;


int main(){
    int N;
    while(cin >> N){
        if( N == 0)
            break;
        string op;
        int k;
        int a = 0, b = 0;
        bool firstIN = false;
        bool firstSet = true;
        set<int> S;
        int minPeople = 0;
        REP(i, N)
        {
            cin >> op >> k;
            if (firstIN == false)
            {
                if(op == "IN" || op == "OUT")
                    firstIN = true;
                else 
                    continue;
            }
            #ifdef DProcess
            cout << "Process  " << op << " with " << k << endl;
            #endif
            if (op == "PAY")
            {
                b += k;
            }
            else if (op == "IN" || op == "OUT"){
                vec<int> fac;
                for (int i = 1; i <= b; i++){
                    if(b % i == 0)
                        fac.eb(i);
                }
                #ifdef DProcess
                for(auto&e: fac){
                    cout << e - a << ", ";
                }
                cout << endl;
                #endif
                if (b != 0)
                {
                    if(firstSet == true) {
                        for (int i = 0; i < fac.size(); i++){
                            if(fac[i] - a > 0){
                                S.emplace(fac[i] - a);
                            }
                        }
                        firstSet = false;
                    }
                    else{
                        for (set<int>::iterator it = S.begin(); it != S.end();){
                            bool found = false;
                            for (int i = 0; i < fac.size(); i++)
                            {
                                if(fac[i] - a == *it){
                                    found = true;
                                    break;
                                }
                            }
                            if(found == false){
                                set<int>::iterator delit = it;
                                it++;
                                S.erase(delit);
                            }
                            else{
                                it++;
                            }
                        }
                    }
                }
                if(op == "IN") 
                    a += k;
                else if(op == "OUT")
                    a -= k;
                b = 0;
            }
            #ifdef DProcess
            debug(a);
            debug(b);
            #endif
            #ifdef Dset
            cout << "avaiolabeSret: ";
            for (const int &e : S)
            {
                cout << e << " ";
            }
                cout << endl;
            #endif
            minPeople = min(a, minPeople);
        }
        #ifdef DProcess
        debug(minPeople);
        #endif
        if (firstSet == true)
        {
            cout << "SIZE >= " << 1 + (-minPeople) << endl;
        }
        else{
            for (set<int>::iterator it = S.begin(); it != S.end();){
                if(*it < 1 + (-minPeople)){
                    set<int>::iterator delit = it;
                    it++;
                    S.erase(delit);
                }
                else{
                    it++;
                }
            }
            if(S.size() == 0){
                cout << "IMPOSSIBLE\n";
            }
            else{
                bool first = true;
                for (const int&e : S){
                    if(first == false)
                        cout << " ";
                    cout << e;
                    first = false;
                }
                cout << endl;
            }
        }
    }
    return 0;
}
