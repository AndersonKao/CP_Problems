#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll, ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define ppi pair<pii,int>
#define pip pair<int,pii>
#define ppp pair<pii,pii>
#define pdd pair<double, double>
#define f first
#define s second
#define MOD 1000000007
#define mkp make_pair
#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define LOR(i,l,r) for (ll i=l;i<=r;i++)
#define FORD(i,r,l) for (int i=r;i>=l;i--)
#define LORD(i,r,l) for (ll i=r;i>=l;i--)
#define CL(x) memset(x,0,sizeof(x))
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int)(x.size())
#define UI(x) (int)(x-'A')
#define LI(x) (int)(x-'a')
#define DI(x) (int)(x-'0')
#define LL_MAX (1LL<<60)
#define DB 0
#define DBG(x) if(DB)cout << #x << " : " << x << '\n'
#define PRALL(v) if(DB)for(auto it : v)cout<<v<<' '; NL;
#define NL cout<<'\n';
#define FND(S,x) (S.find(x)!=S.end())
#define bit(x,y) (!!(x&(1<<y)))
typedef long long ll;
typedef long double ld;

int N;

map<int,int> cnt;//occurrence of prime p
map<int,pii> mnp;//least two powers of prime p // pii (smallest, 2nd small)

void upd(int p, int w)
{
    pii & P = mnp[p];
    int c = cnt[p];

    if( !c )P.f = w;
    else if( w < P.f )
    {
        P.s = P.f;
        P.f = w;
    }
    else if( c==1 || w < P.s )
    {
        P.s = w;
    }
    cnt[p]++;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>N;
    int Ai;
    FOR(i,1,N)
    {
        cin>>Ai;

        int x = 2;
        while( x*x <= Ai )
        {
            if( Ai%x == 0 )
            {
                int w = 0;
                while( Ai%x==0 )
                {
                    w++;
                    Ai/=x;
                }
                upd( x, w );
            }
            x++;
        }
        if( Ai > 1 )
        {
            upd( Ai, 1 );
        }
    }
    ll ans = 1;
    for( auto mnpi : mnp )
    {
        int pi = mnpi.f;
        int c = cnt[pi]; //cnt
        pii P = mnpi.s;
        int w;//power of pi in ans
        if( c == N )    // that means normal case
        {
            w = P.s;
        }
        else if( c == N-1 ) // because one of numbers doesn't have this prime factor
                            // the smallest is zero, the 2nd smallest be first
        {
            w = P.f;
        }
        else w = 0;         // more than two numbers don't have this pf
                            // we can simply take zero

        while(w--)ans*=pi;
    }
    cout<<ans<<'\n';

    return 0;
}