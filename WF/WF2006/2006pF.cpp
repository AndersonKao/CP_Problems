// AC 2022-07-01 15:25:58
// WA
// mistaken on putting invalid format such like *T-U-NC into sol. We should only put *T-U-N
// WA
// shaft count error
// *0-12-5 and *0-12-3 should be 4 and 5 rather than 3 and 5
// WA
// idiot. writing vec<char> but all the way of bool operation
//WA
// if id-2 is a '*' then we can't use the same shaft
#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n; i++)
template <typename T>
using vec = vector<T>;
#define eb emplace_back
#define debug(x) cout << #x << ":= " << x << endl;
vec<string> minsol, hrsol;
vec<char> names;
vec<int> gears;
vec<char> used;
int N;
const double eps = 1e-9;
int fcmp(double a, double b)
{
    if(fabs(a-b) < eps)
        return 0;
    return (a > b) * 2 - 1;
}
void init(int N){
    names.resize(N);
    gears.resize(N);
    minsol.clear(), hrsol.clear();
    used.clear();
    used.resize(N, 'U');
}

void findall(int layer, double rate, string sol){
    #ifdef Drecur
    debug(sol);
    #endif
    if (fcmp(rate, 24.0) == 0)
    {
        int len = sol.length();
        if (len - 2 >= 0){
            if(sol[len-2] == '-'){
                minsol.eb(sol);
            }
        }
        else{
            minsol.eb(sol);
        }
    }
    if(fcmp(rate, 2.0) == 0){
        //hrsol.eb(sol);
        int len = sol.length();
        if (len - 2 >= 0){
            if(sol[len-2] == '-'){
                hrsol.eb(sol);
            }
        }
        else{
            hrsol.eb(sol);
        }
    }
    if(layer >= 6)
        return;
    if(sol == "*"){
        REP(i, N){
            used[i] = 'D';
            findall(layer + 1, rate, sol + (char)('0' + i));
            used[i] = 'U';
        }
    }
    else{
        int sid = sol.size() - 1;

        // add next gear.
        REP(i, N){
            if(used[i] == 'U'){
                used[i] = 'D';
                int preid = sol[sid] - '0';
                findall(layer + 1, -rate * (gears[preid] / (double)gears[i]), sol + '-' + (char)('0' + i));
                used[i] = 'U';
            }
        }

        // add same shaft
        if(sid - 1 >= 0 && (sol[sid-1] == '-' /*|| sol[sid-1] == '*'*/) )
        {
            REP(i, N){
                if(used[i] == 'U'){
                    used[i] = 'D';
                    findall(layer + 1, rate, sol + (char)('0' + i));
                    used[i] = 'U';
                }
            }
        }
    }
}

bool match(string& minsol, string& hrsol, int& solNs, int& solNg){

    vec<bool> mused(N, false);
    int sid = 0;
    solNs = solNg = 0; // shaft num, gear num
    int limit = min(minsol.length(), hrsol.length());
    for (sid = 0; sid < limit; sid++){
        if(minsol[sid] != hrsol[sid])
            break;
        char &e = minsol[sid];
        if (e == '-' || e == '*')
            solNs++;
        else
            solNg++;
    }
    if(minsol[sid-1] == '-'){
        solNs--;
        sid--;
    }

    for (int i = sid; i < minsol.length(); i++)
    {
        char &ch = minsol[i];
        if (ch != '*' && ch != '-')
        {
            if (mused[(ch - '0')] == true)
                return false;
            mused[(ch - '0')] = true;
            solNg++;
        }
        else
            solNs++;
    }
    for (int i = sid; i < hrsol.length(); i++)
    {
        char &ch = hrsol[i];
        if(ch != '*' && ch != '-'){
            if( mused[(ch - '0')] == true )
                return false;
            mused[(ch - '0')] = true;
            solNg++;
        }
        else
            solNs++;
    }
    return true;
}

int main(){
    int caseN = 1;
    while (cin >> N)
    {
        if(N == 0)
            break;
        if(caseN != 1)
            cout << endl;
        int baseR;
        cin >> baseR;
        init(N);
        REP(i, N)
        {
            cin >> names[i] >> gears[i];
        }
        string sol = "*";
        findall(0, (double)baseR, sol);
        #ifdef Dsols
        cout << "minute sols:\n";
        for(string e: minsol){
            cout << e << endl;
        }
        cout << "hour sols:\n";
        for(string e: hrsol){
            cout << e << endl;
        }
        #endif
        if(minsol.size() == 0 || hrsol.size() == 0){
            cout << "Trial " << caseN++ << " IS IMPOSSIBLE\n";
            continue;
        }
        int ansNs, ansNg;
        string minans = "", hrans = "";
        string ansalpha = "";
        ansNs = ansNg = numeric_limits<int>::max();
        for (string &mine : minsol)
        {
            for(string& hre: hrsol){
                /*
                debug(mine);
                debug(hre);
                */
                int solNs = 0, solNg = 0;
                bool better = false;
                if (match(mine, hre, solNs, solNg))
                {
                    #ifdef DDans
                    debug(solNs);
                    debug(solNg);
                    #endif

                    string solalpha = "";
                    for(char&e:mine){
                        if(e == '*' || e=='-')
                            continue;
                        solalpha += names[(e - '0')];
                    }
                    for(char&e:hre){
                        if(e == '*' || e=='-')
                            continue;
                        solalpha += names[(e - '0')];
                    }

                    if(solNs < ansNs || (solNs == ansNs && solNg < ansNg)){
                        better = true;
                    }
                    else if(solNs == ansNs && solNg == ansNg && solalpha < ansalpha){
                            better = true;
                    }
                    if(better){
                        ansNg = solNg, ansNs = solNs;
                        minans = mine;
                        hrans = hre;
                        ansalpha = solalpha;
                        #ifdef Dans
                        debug(ansNs);
                        debug(ansNg);
                        debug(ansalpha);
                        cout << "change to " << minans << " and " << hrans << endl;
#endif
                    }
                }
            }
        }
        
        if(ansNs == numeric_limits<int>::max()){
            cout << "Trial " << caseN++ << " IS IMPOSSIBLE\n";
        }
        else{
            for(char&e : minans){
                if(e == '*' || e=='-')
                    continue;
                e = names[(e - '0')];
            }
            for(char&e : hrans){
                if(e == '*' || e=='-')
                    continue;
                e = names[(e - '0')];
            }
            cout << "Trial " << caseN++ << endl;
            cout << "Minutes: " << minans << endl;
            cout << "Hours:   " << hrans << endl;
        }
    }

    return 0;
}