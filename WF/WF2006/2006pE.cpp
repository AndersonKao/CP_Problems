// WA
// for '10' case, we should let '1' + '0' to process it rather than treat '10' ans a special case.
// WA
// countinuous 1 more than three must be decode;
#include <bits/stdc++.h>
using namespace std;
template <typename T>
using vec = vector<T>;
using ll = long long;
#define F first
#define S second
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define al(x) x.begin(), x.end()
#define eb emplace_back
#define debug(x) cout << #x << ":= " << x << endl;
ll possi;
string str;
int L, N;

ll decode(string& str, int bg, int ed){
    ll ans = 0;
    int i = ed;
    ll res = 1;
    while (i >= bg)
    {
        if(str[i] == '1')
            ans += res;
        res <<= 1;
        i--;
    }
    return ans;
}
using pii = pair<int, int>;
stack<pair<int, int>> S;

void recur(int ti, int Onum, int Len)
{
    int strLen = str.length();
    if(ti == strLen-1){
        if(Onum == N && Len == L){
            #ifdef Drecur
            cout << "Count\n";
            stack<pii> S2;
            while(S.size()){
                cout << "(" << S.top().F << ", " << S.top().S << ")\n";
                S2.emplace(S.top());
                S.pop();
            }
            cout << "-0000000-------------------------------\n";
            while (S2.size())
            {
                S.emplace(S2.top());
                S2.pop();
            }
            #endif
            possi++;
        }
        return;
    }

    #ifdef Drecur
    cout << "Onum: " << Onum << " Len : " << Len << endl;
    cout << "layer: " << ti;
    if(str[ti] == '1'){
        cout << " is 1\n";
    }
    else
        cout << " is 0\n";
    #endif
    if(Onum > N || Len > L){
        #ifdef Drecur
        debug(Onum);
        debug(Len);
        #endif
        return;
    }

    if(str[ti] == '1'){
        if (ti - 1 == -1 || ((ti - 1 >= 0) && str[ti - 1] == '0'))
        {
            // decode
            int limit = min(strLen, ti + 20);
            for (int j = ti + 1; j < limit; j++)
            {
                if(str[j] == '0'){
                    ll dec = decode(str, ti, j - 1);
                    #ifdef Ddec
                    cout << "at " << j << ", ";
                    cout << "Decoding: ";
                    for (int test = ti; test < j; test++)
                        cout << str[test];
                    cout << endl;
                    debug(dec);
                    #endif
                    if(dec == 1){
                        recur(j, Onum + 1, Len + 1);
                    }
                    else if(dec == 2){
                        //recur(j, Onum + 1, Len + 2);
                    }
                    else if (dec == 3)
                    {
                        recur(j, Onum + 2, Len + 2);
                        #ifdef Drecur
                        S.emplace(ti, j - 1);
                        #endif
                        recur(j, Onum + 3, Len + 3);
                        #ifdef Drecur
                        S.pop();
                        #endif
                    }
                    else
                    {
                        S.emplace(ti, j - 1);
                        recur(j, Onum + dec, Len + dec);
                        S.pop();
                    }
                }
           }
        }
//        recur(ti + 1, Onum + 1, Len + 1);
    }
    else{
        recur(ti + 1, Onum, Len + 1);
    }
}
int main()
{
    int caseN = 1;
    while (cin >> L >> N)
    {
        if(L == 0 && N == 0)
            break;
        cin >> str;
        possi = 0;
        //string str2 = "1001101";
        /*
        cout << decode(str2, 0, 1) << endl;
        cout << decode(str2, 0, 4) << endl;
        cout << decode(str2, 3, 4) << endl;
        */
        str += "0";
        #ifdef Drecur
        debug(str);
        while (S.size())
            S.pop();
        #endif
        recur(0, 0, 0);
        cout << "Case #" << caseN++ << ": ";
        if (possi == 0)
            cout << "NO";
        else if(possi == 1)
            cout << "YES";
        else
            cout << "NOT UNIQUE";
        cout << endl;
    }
    return 0;
}