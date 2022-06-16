// AC 2022-06-06 08:18:59
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define F first
#define S second
#define eb emplace_back
#define REP(i, n) for (int i = 0; i < n; i++)
#define REP1(i, n) for (int i = 1; i <= n; i++)
#define al(x) x.begin(), x.end()
template <typename T>
using vec = vector<T>;
vec<int> days = {0, 
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool specyear(int y){
    if((y % 4 == 0 && y % 100 != 0 )|| (y % 400 == 0)){
        return true;
    }
    return false;
}
struct day
{
    int y, m, d;
    day(){
        y = m = d = 0;
    }
    day(int a, int b, int c) : y(a), m(b), d(c){}
    
    bool operator<(const day& rem){
        return (y != rem.y ? y < rem.y : (m != rem.m ? m < rem.m : (d < rem.d)));
    }
    bool operator==(const day& rem){
        return (y == rem.y) && (m == rem.m) && (d == rem.d);
    }

    day tomo(){
        day rem = *this;
        rem.d = d + 1;
        int monthday = days[rem.m];
        if(rem.m == 2 && specyear(rem.y))
            monthday++;
        if (rem.d > monthday){
            rem.d = 1;
            rem.m++;
            if(rem.m > 12){
                rem.m = 1;
                rem.y++;
            }
        }
        return rem;
    }
    day prev(){
        day rem = *this;
        rem.d = d - 1;
        if(rem.d == 0){
            rem.m--;
            if(rem.m == 0){
                rem.m = 12;
                rem.d = days[rem.m];
                rem.y--;
            }
            else {
                if(rem.m == 2 && specyear(rem.y)){
                    rem.d = days[rem.m] + 1;
                }
                else
                    rem.d = days[rem.m];
            }
        }
        return rem;
    }
    friend ostream& operator<<(ostream &os, const day &rem);
};
ostream& operator<<(ostream &os, const day &rem){
    return (os << rem.m << "/" << rem.d << "/" << rem.y);
}
enum type
{
    RIN = 1,
    NIN = 2,
    NOUT = 3,
    ROUT = 4
};
string ptype(int type){
    if(type == 1)
        return string("RIN");
    else if(type == 2)
        return string("NIN");
    else if(type == 3)
        return string("ROUT");
    else if(type == 4)
        return string("NOUT");
    return "FUCK";
}
 auto cmp = [](pair<day, int> &a, pair<day, int> &b)
             { 
                if(a.F == b.F)
                    return a.S < b.S;
                return a.F < b.F; 
            };
void process(vec<pair<day, int>> R, type IN, type OUT, vec<pair<day, int>>& V){
    vec<pair<day, int>> proc;
    int cover = 0;
    int st = 0;
    for (int i = 0; i < R.size(); i++)
    {
        if(R[i].S == IN){
            cover++;
            if(cover == 1)
                st = i;
        }else if(R[i].S == OUT){
            cover--;
            if(cover == 0){
                proc.eb(R[st].F, IN);
                proc.eb(R[i].F, OUT);
            }
        }
    }
    for (int i = 0; i < proc.size();){
        int st = i;
        int ed = i + 1;
        while (ed + 1 < proc.size() && proc[ed+1].F == proc[ed].F.tomo()){
            ed += 2;
        }
        V.eb(proc[st].F, IN);
        V.eb(proc[ed].F, OUT);
        i = ed + 1;
    }
}

int main()
{
    int Nx, Nr;
    int caseN = 1;
    while (cin >> Nx >> Nr)
    {
        if(!(Nx || Nr))
            break;
        if(caseN != 1)
        cout << endl;
        cout << "Case " << caseN++ << ":\n";
        vec<pair<day, int>> RC;
        vec<pair<day, int>> proc;
        vec<pair<day, int>> NQ;
        vec<pair<day, int>> V;

        REP(i, Nx){
            int x;
            cin >> x;
            RC.eb(day(x / 10000, (x % 10000) / 100, (x % 100)), RIN);
            cin >> x;
            RC.eb(day(x / 10000, (x % 10000) / 100, (x % 100)), ROUT);
        }
        REP(i, Nr){
            int x;
            cin >> x;
            NQ.eb(day(x / 10000, (x % 10000) / 100, (x % 100)), NIN);
            cin >> x;
            NQ.eb(day(x / 10000, (x % 10000) / 100, (x % 100)), NOUT);
        }
       
        sort(al(RC), cmp);
        sort(al(NQ), cmp);
        process(RC, RIN, ROUT, V);
        process(NQ, NIN, NOUT, V);
        
        sort(al(V), cmp);

        int cover = 0, asking = 0;
        vec<day> ans;
        for (int i = 0; i < V.size(); i++)
        {
            day &rem = V[i].F;
            int dtype = V[i].S;
            if (dtype == RIN)
            {
                cover++;
                if(cover == 1 && asking > 0){
                    ans.eb(rem.prev());
                }
            }
            else if(dtype  == ROUT){
                cover--;
                if(cover == 0 && asking > 0){
                    ans.eb(rem.tomo());
                }
            }
            else if(dtype == NIN){
                asking++;
                if(cover == 0 && asking  == 1)
                    ans.eb(rem);
            }
            else if(dtype  == NOUT){
                asking--;
                if(cover == 0 && asking == 0){
                    ans.eb(rem);
                }
            }
        }
        if(ans.size() == 0){
            cout << "    No additional quotes are required.\n";
            continue;
        }
        vec<pair<day, day>> realans;
        for (int i = 0; i < ans.size();)
        {
            int st = i;
            int ed = i + 1;
            while (ed + 1 < ans.size() && ans[ed].tomo() == ans[ed+1]){
                ed += 2;
            }
            realans.eb(ans[st], ans[ed]);
            i = ed + 1;
            // cout << "    " << ans[i] << " to " << ans[i + 1] << endl;
        }
        for(auto&e: realans){
            cout << "    ";
            if (e.F == e.S)
            {
                cout << e.F << endl;
            }else
                cout << e.F << " to " << e.S << endl;
        }
    }
    return 0;
}