#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<utility>
#include<string>
#include<set>
// #define int long long 
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front
#define F first
#define S second
#define pii pair<int,int>
#define mp make_pair
using namespace std;

const int N = 250001;

map<char,int>dir;
int n;
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
char dddd[4] = {'E','W','S','N'};
char st[N];

int l,s,e,d;
vector< vector< pii > >X;

void chmax(int x1,int x2,int id1,int id2,int dr){
    if(id1>id2)
        swap(id1,id2), dr ^= 1;
    if(id2-id1==1)
        return;
    int dd = abs(x1-x2);
    if(dd<l)
        l = dd, s = id1, e = id2, d = dr;
    else if(dd==l){
        if(id1<s)
            l = dd, s = id1, e = id2, d = dr;
        else if(id1==s && id2>e)
            l = dd, s = id1, e = id2, d = dr;
    }
}

void solve(){
		scanf("%d", &n);
    //cin >> n;
		scanf("%s", st);
//    cin >> st;
    int x = 0, y = 0;
    int mnx = 1e9+10, mny = 1e9+10;
	int maxx = -1e9-10, maxy = -1e9-10;
    for(int i=0;i<=n;i++){
        if(i)
            x += dx[dir[st[i-1]]], y += dy[dir[st[i-1]]];
        mnx = min(x,mnx), mny = min(y,mny);
		maxx = max(x, maxx), maxy = max(y, maxy);
    }
    x = -mnx, y = -mny;
	maxx -= mnx;
	maxy -= mny;
	X.resize(maxx+2);
    // hor
    l = 10*N;
    for(int i=0;i<=n;i++){
        if(i)
            x += dx[dir[st[i-1]]], y += dy[dir[st[i-1]]];
        X[x].pb(mp(y,i));
    }
    for(int i=0;i<X.size();i++)
        sort(X[i].begin(), X[i].end());
    x = -mnx, y = -mny;
    for(int i=0;i<=n;i++){
        if(i)
            x += dx[dir[st[i-1]]], y += dy[dir[st[i-1]]];
        vector< pii >::iterator p = upper_bound(X[x].begin(), X[x].end(), mp(y,10*N));
        if(p!=X[x].end()) // E
            chmax(y,(*p).F,i,(*p).S,dir['E']);
        p = lower_bound(X[x].begin(), X[x].end(), mp(y,0));
        if(p!=X[x].begin()){ // W
            p--;
            chmax(y,(*p).F,i,(*p).S,dir['W']);
        }
    }
   
    // ver
    x = -mnx, y = -mny;
	X.resize(maxy+2);
    for(int i=0;i<X.size();i++)
        X[i].clear();
    for(int i=0;i<=n;i++){
        if(i)
            x += dx[dir[st[i-1]]], y += dy[dir[st[i-1]]];
        X[y].pb(mp(x,i));
    }
    for(int i=0;i<X.size();i++)
        sort(X[i].begin(), X[i].end());
    x = -mnx, y = -mny;
    for(int i=0;i<=n;i++){
        if(i)
            x += dx[dir[st[i-1]]], y += dy[dir[st[i-1]]];
        vector< pii >::iterator p = upper_bound(X[y].begin(), X[y].end(), mp(x,10*N));
        if(p!=X[y].end()) // S
            chmax(x,(*p).F,i,(*p).S,dir['S']);
        p = lower_bound(X[y].begin(), X[y].end(), mp(x,0));
        if(p!=X[y].begin()){ // N
            p--;
            chmax(x,(*p).F,i,(*p).S,dir['N']);
        }
    }
    cout << l << ' ' << s << ' ' << e << ' ' << dddd[d] << '\n';
}

signed main(){
    dir['N'] = 3, dir['S'] = 2, dir['W'] = 1, dir['E'] = 0;
    solve();
    return 0;
}
