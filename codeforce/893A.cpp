#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll, ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define ppi pair<pii,int>
#define pip pair<int,pii>
#define pdd pair<double, double>
#define f first
#define s second
#define MOD 1000000007
#define mkp make_pair
#define M_PI 3.14159265358979323846
#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define LOR(i,l,r) for (ll i=l;i<=r;i++)
#define FORD(i,r,l) for (int i=r;i>=l;i--)
#define LORD(i,r,l) for (ll i=r;i>=l;i--)
#define INF 1000000000
#define CL(x) memset(x,0,sizeof(x))
#define DEB(x) cout << #x << " : " << x << '\n'
#define ALL(x) x.begin(), x.end()
#define SZ(x) x.size()
#define UI(x) (int)(x-'A')
#define LI(x) (int)(x-'a')
typedef long long ll;

int Q;
ll X,Y;
const int mxk = 20, mxn = 1000000;
ll C[mxn+mxk+5][mxk+5];
ll pow2[mxn+5];

/*

factorize each X and do H(Y,Pk) for each prime factor power Pk

*/

void init()
{
    cin>>Q;
    FOR(i,0,mxn+mxk)
    {
        C[i][0]=1;
        FOR(j,1,min(i-1,mxk))C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;      // generating C function
        if(i<=mxk)C[i][i]=1;
    }
    pow2[0]=1;
    FOR(i,1,mxn)pow2[i]=(pow2[i-1])*2%MOD;
}

ll sol()
{
    ll x = X;
    ll i = 2;
    ll ans = 1;
    while(i*i<=x)
    {
        if(x%i==0)
        {
            ll pw = 0;
            while(x%i==0)
            {
                pw++;
                x/=i;
            }
            ans=(ans*C[Y+pw-1][pw])%MOD;
        }
        i++;
    }
    if(x>1)
    {
        ll pw=1;
        ans=(ans*C[Y+pw-1][pw])%MOD;
    }
    ans=(ans*pow2[Y-1])%MOD;
    cout<<ans<<'\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();
    while(Q--)
    {
        cin>>X>>Y;
        sol();
    }

    return 0;
}
 