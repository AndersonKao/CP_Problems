#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using Prior = priority_queue<T>;
template<typename T> using prior = priority_queue<T, vector<T>, greater<T>>;
 
#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
 
const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 4*1e18;
const int MOD = 1e9+7;
 
ll& pmod(ll& a, ll b) { a = (a+b) % MOD; return a; }
ll& pmod(ll& a, ll b, ll c) { a = (a+b) % c; return a; }
ll& mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; return a; }
ll& mmod(ll& a, ll b, ll c) { a = (a-b+c) % c; return a; }
ll& tmod(ll& a, ll b) { a = (a*b) % MOD; return a; }
ll mul(ll a, ll b) { return (a*b) % MOD; }
ll mul(ll a, ll b, ll c) { return (a*b) % c; }
ll POW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }
ll FAC(ll a) { ll res = 1; REP1(i, a) tmod(res, i); return res; }
 
template<typename T1, typename T2>
ofstream operator<<(ofstream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int good;

bool div(string& src)
{
    for (int i = 0; i < src.size(); i++)
    {
        if (i == src.size() - 1)
        {
            int ret = (src[i] - '0') % 2;
            src[i] = '0' + ((src[i] - '0') / 2);

            if (all_of(al(src), [](char i){ return i == '0'; }))
                good++;

            return ret;
        }
        else
        {
            if ((src[i] - '0') % 2)
                src[i + 1]++;

            src[i] = '0' + ((src[i] - '0') / 2);
        }
    }
}

void mul(vec<int>& src)
{
    REP(i, src.size())
        src[i] *= 2;

    int i = 0;
    while (src[i] >= 10)
    {
        src[i + 1] += src[i] / 10;
        src[i] %= 10;

        i++;
    }
}
void add(vec<int>& src)
{
    src[0]++;

    int i = 0;
    while (src[i] >= 10)
    {
        src[i] -= 10;
        src[i + 1]++;

        i++;
    }
}

int main()
{
    yccc;
    int c = 1;

    string a, b;
    while (cin >> a >> b)
    {
        if (a == "0" and b == "0")
            return 0;

        cout << "Case Number " << c++ << ": ";

        good = 0;

        vec<int> _list;

        while (good != 2)
        {
            _list.eb(div(a) ^ div(b));
        }

        int sz = _list.size();

        vec<int> tans(sz);
        for (int i = 1; i < sz; i++)
            if (_list[i-1] == 1)
            {
                _list[i - 1] ^= 1;
                _list[i] ^= 1;

                if (i+1 < sz)
                    _list[i + 1] ^= 1;

                tans[i] = !tans[i];
            }

        if (_list[sz-1] and sz % 3 == 2)
        {
            cout << "impossible\n";
            continue;
        }
        else if (_list[sz-1] and sz % 3 == 1)
        {
            REP(i, sz)
                tans[i] = !tans[i];

            for (int i = 2; i < sz; i += 3)
                tans[i] = !tans[i];
        }

        vector<int> ans(120, 0);

        for (int i = sz - 1; i >= 0; i--)
        {
            mul(ans);

            if (tans[i])
                add(ans);
        }

        int p = false;
        for (int i = 119; i >= 0; i--)
        {
            if (p)
            {
                cout << ans[i];
            }
            else
            {
                if (ans[i] != 0)
                {
                    cout << ans[i];
                    p = true;
                }
            }
        }

        cout << endl;
    }

    
}