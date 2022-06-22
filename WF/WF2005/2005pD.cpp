// AC 2022-06-22 19:38:41
#include <bits/stdc++.h>
using namespace std;

#define yccc cin.tie(0), ios_base::sync_with_stdio(false);
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
#define F first
#define S second
template <typename T>
using vec = vector<T>;
#define al(x) x.begin(), x.end()
#define eb emplace_back
#define debug(x) cout << #x << " := " << x << endl;

const int P = 52;
vec<vec<int>> Perf(11, vec<int>(52));
vec<int> shuf(52), cshuf(52); // pos i should go to where

void getPerfect(){
    REP(i, 52)
        Perf[0][i] = i;

    for (int i = 1; i < 11; i++){
        for (int j = 0; j < 52; j++){
            Perf[i][j] = Perf[i-1][cshuf[j]];
        }
        /*
        cout << "Perf " << i << ": ";
        REP(j, 52)
        cout << Perf[i][j] << " ";
        cout << endl;
        */
    }
}
inline int diffen(const vec<int>&A, const vec<int>&B){
    int ans = 0;
    REP(i, 52)
    {
        if(A[i] != B[i])
            ans++;
    }
    return ans;
}
int getNofS(vec<int>& A){
    for (int i = 0; i < 11; i++){
        int diff = diffen(A, Perf[i]);
//        debug(diff);
        if (diffen(A, Perf[i]) <= 21)
        {
            return i;
        }
    }
    return -1;
}
using pii = pair<int, int>;
stack<pii> Anstack;
long unsigned int ansSize = numeric_limits<long unsigned int>::max();
vec<pii> ansV;
inline void shuffles(vec<int>& A){
    vec<int> tmp(52);
    tmp = A;
    REP(i, 52)
    {
        A[i] = tmp[shuf[i]];
    }
}
inline void ushuffles(vec<int>& A){
    vec<int> tmp(52);
    tmp = A;
    REP(i, 52)
    {
        A[i] = tmp[cshuf[i]];
    }
}
bool sol;
bool match1, match2, match3;
void DFS(vec<int> &A, int layer, int NofS)
{
    #ifdef DDFS
        debug(layer);
        cout << "A: ";
        REP(i, 52)
        cout << A[i] << " ";
        cout << endl;
    #endif
    int NofSi = NofS - layer;
    int diff = diffen(A, Perf[NofSi]);
    /*
    if(match1 && match2 && match3 && layer >= 9){
        debug(layer);
        debug(NofSi);
        debug(diff);
        cout << "A: ";
        REP(i, 52)
        cout << A[i] << " ";
        cout << endl;
    }
    */
    #ifdef Dsm
    debug(NofSi);
    debug(diff);
    #endif
    if (diff == 0)
    {
        sol = true;
        if (Anstack.size() < ansSize)
        {
            ansSize = Anstack.size();
            ansV.clear();
            while (Anstack.size())
            {
                ansV.eb(Anstack.top().F, Anstack.top().S);
                Anstack.pop();
            }
            //cout << "findsol !!!\n";
            for (int i = ansV.size() - 1; i >= 0; i--){
           //     cout << "Error in shuffle " << ansV[i].F << " at location " << ansV[i].S << endl;
                Anstack.push(ansV[i]);
            }
        }
        else if(Anstack.size() == ansSize){
            vec<pii> tmpAns;
            while (Anstack.size())
            {
                tmpAns.eb(Anstack.top().F, Anstack.top().S);
                Anstack.pop();
            }
//            cout << "findsol !!!\n";
            for (int i = tmpAns.size() - 1; i >= 0; i--){
           //     cout << "Error in shuffle " << ansV[i].F << " at location " << ansV[i].S << endl;
                Anstack.push(tmpAns[i]);
            }
            bool Anshit = false;
            for (int i = 0; i < ansSize; i++){
                if(tmpAns[i].S < ansV[i].S){
                    Anshit = true;
                    break;
                }
            }
            if(Anshit)
                ansV = tmpAns;
        }
        return;
    }
    else if( diff > NofSi * 2){
        #ifdef Dsm
        cout << "to much " << endl;
        #endif
        return;
    }
    else if(Anstack.size() >= ansSize)
        return;

    if (NofSi < 0)
        return;
//    vec<int> tmp(52);
 //   tmp = A;
    shuffles(A);
    DFS(A, layer + 1, NofS);
    ushuffles(A);
    for (int i = 0; i < 51; i++)
    {
        if(A[i] == Perf[NofSi][i] && A[i+1] == Perf[NofSi][i+1])
            continue;
            swap(A[i], A[i + 1]);
            Anstack.emplace(NofSi, i);
            shuffles(A);
            DFS(A, layer + 1, NofS);
            ushuffles(A);

            swap(A[i], A[i + 1]);
            Anstack.pop();
    }
}

int main(){
    yccc;
    int T;
    cin >> T;
    int idx = 1;
    REP(i, 52)
    {
        cshuf[idx] = i;
        idx = (idx + 2 >= 52 ? 0 : idx + 2);
    }
    REP(i, 52){
        for (int j = 0; j < 52; j++){
            if(cshuf[j] == i){
                shuf[i] = j;
                break;
            }
        }
    }
    /*
    REP(i, 52){
        cout << shuf[i] << " ";
    }
    cout << endl;
    REP(i, 52){
        cout << cshuf[i] << " ";
    }
    cout << endl;
    */
    getPerfect();

    REP1(caseN, T)
    {
        match1 = match2 = match3 = false;
        vec<int> A(52);
        ansV.clear();
        ansSize = numeric_limits<long unsigned int>::max();
        while(!Anstack.empty()){
            Anstack.pop();
        }
        REP(i, 52)
        {
            cin >> A[i];
        }
        int NofS = getNofS(A);
        sol = false;
        cout << "Case " << caseN << endl;
        cout << "Number of shuffles = " << NofS << endl;
        DFS(A, 0, NofS);

        if(sol){
            if(ansV.size()){
                for(pii&e: ansV){
                    cout << "Error in shuffle " << e.F << " at location " << e.S << endl;
                }
            }
            else {
                cout << "No error in any shuffle\n";
            }
        }
        cout << endl;
    }

        return 0;
}