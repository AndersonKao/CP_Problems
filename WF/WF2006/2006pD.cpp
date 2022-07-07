#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second
template <typename T>
using vec = vector<T>;
using pii = pair<int, int>;
#define debug(x) cout << #x << ":= " << x << endl;
#define depii(x) cout << #x << ":= " << x.F << ", " << x.S << endl;
#define eb emplace_back
int Modn;

int getModn(vec<vec<int>>& Modtable, int L, int d){
    int res = d % Modn;
    #ifdef DModn
    debug(L);
    debug(d);
    debug(Modtable.size());
    #endif
    if (L == 1)
        return Modtable[L][d] =  res;
    return Modtable[L][d] = (Modtable[L - 1][d] * 10 + d) % Modn;

    /*
    for (int i = 0; i < L; i++)
    {
        ans += res;
        ans %= Modn;
        res *= 10;
        //        res += d;
        res %= Modn;
    }
    */
//    return ans;
}
bool avail(int La, int da, int Lc, int dc, bool addi){
    // using A's Length&digit and C's length & digit to determine if A-C > Modn;
    int ans = 0;
    int idx = 0;
    int ten = 1;
    while (idx < La)
    {
        if(idx >= Lc)
            ans += da* ten;
        else{
            if(addi)
                ans += (da + dc) * ten;
            else
                ans += (da - dc) * ten;
        }
        if(ans > Modn)
            return true;
        ten *= 10;
        idx++;
    }
    return false;
}

int main()
{
    while (cin >> Modn) {
        if(Modn == 0)
            break;
        bool found = false;
        vec<vec<pii>> table(Modn);
        vec<vec<int>> Modtable((int)(500), vec<int>(10));
        pii AnsA, AnsC;
        bool AnsAddi = false;
        while(found == false){
        for (int Len = 1;; Len++)
        {
            for (int digit = 1; digit <= 9; digit++)
            {

                //                    cout << getModn(Len, digit) << endl;
                if(Len >= Modtable.size())
                    Modtable.resize(2 * Len, vec<int>(10));
                int rem = getModn(Modtable, Len, digit);
                #ifdef Denume
                debug(Len);
                debug(digit);
                debug(rem);
                #endif
                // check any C there;
                for (int i = table[rem].size() - 1; i >= 0; i--)
                {
                    pii &C = table[rem][i];
                    #ifdef Dpicking
                    cout << "pick ";
                    depii(C);
                    #endif
                    if (Len > C.F && (digit - C.S) >= 0)
                    {
                        if (avail(Len, digit, C.F, C.S, false))
                        {
                            found = true;
                            AnsA = pii(Len, digit);
                            AnsC = C;
                            AnsAddi = false;
                        }
                    }
                    if (found)
                        break;
                }
                if (found)
                    break;
                int CounterRem = (Modn - rem) % Modn;
                for (int i = 0; i < table[CounterRem].size(); i++)
                {
                    pii &C = table[CounterRem][i];
                    #ifdef Dpicking
                    cout << "pick ";
                    depii(C);
                    #endif
                    if (Len > C.F && (digit + C.S) <= 9)
                    {
                        if (avail(Len, digit, C.F, C.S, true))
                        {
                            found = true;
                            AnsA = pii(Len, digit);
                            AnsC = C;
                            AnsAddi = true;
                        }
                    }
                    if (found)
                        break;
                }
                table[rem].eb(Len, digit);
                if (found)
                    break;
            }
            if (found)
                break;
        }
        }
        cout << Modn << ": " << (AnsA.F - AnsC.F) << " " << AnsA.S << " " << AnsC.F << " " << (AnsAddi ?AnsC.S + AnsA.S : AnsA.S - AnsC.S) << endl;
    }
    return 0;
}