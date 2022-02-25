#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
using mat = vector<vector<long long>>;
using pt = pair<int, int>;

#define f first
#define s second
#define rep(i,n) for(int i = 0; i < (n); i++)

int n,m,h,w; 
vector<pt> poi(1000001);

pt upright(pt p){
    pt ur(0, 0);
    if ((p.f - h) > 0)
        ur.f = p.f-h;
    if ((p.s - w > 0))
        ur.s = p.s-w;
    return ur;
}
pt leftdown(pt p){
    pt ld(n-1, m-1);
    if ((p.f + h) < n-1)
        ld.f = p.f + h;
    if ((p.s + w < m-1))
        ld.s = p.s + w;
    return ld;
}

ll check(ll b, mat& grid){
    
}

ll bs(ll lh, ll rh, mat& grid){
    while(abs(rh-lh > 1)){
        ll mid = (rh-lh) / 2;
        if(check(mid, grid) >= 0)
            rh = mid;
        else
            lh = mid;
    }
    return lh;
}

int main()
{
    cin >> n >> m >> h >> w;
    mat grid(n, vector<ll>(m));
    rep(i, n) rep(j, m){
        cin >> grid[i][j];
        poi[grid[i][j]] = pt(i, j);
    }
    cout << bs(0, 1000001, grid);
    return 0;
}