#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxn = 2000000;
const int maxx = 1e6;

// Miminimum Li Chao Tree
const ll inf = 1e18;
struct line
{
    ll m, b;
    line(){m = b = inf;}
    line(ll mm, ll bb){m = mm, b = bb;}
    ll y(ll x){
        if(m == inf || b == inf)
            return inf;
        return m * x + b;
    }
};


line segs[4*maxx];
ll dp[maxn], sval[maxn], fval[maxn];
/*
a line is  y = k * x + b, using point to represent it.
*/
void add_line(line cur, int idx = 1, int l = 0, int r = maxx)
{
    if(l == r){
        if(cur.y(l) < segs[idx].y(l)){
            segs[idx] = cur;
        }
        return;
    }
    int mid = (l + r) >> 1;
    if(cur.m > segs[idx].m){
        swap(cur, segs[idx]);
    }
    if(cur.y(mid) < segs[idx].y(mid)){
        swap(cur, segs[idx]);
        add_line(cur, idx * 2, l, mid);
    }
    else{
        add_line(cur, idx * 2 + 1, mid + 1, r);
    }
}

// get minimum in some line x;
ll query(int x, int idx = 1, int l = 0, int r = maxx)
{
    ll cur = segs[idx].y(x);
    if(l == r){
        return cur;
    }
	ll mid = (l + r) >> 1;
    if(x <= mid){
        return min(cur, query(x, idx * 2, l, mid));
    }
    else{
        return min(cur, query(x, idx * 2 + 1, mid + 1, r));
    }
}

int main(){
	yccc;		
	int n, skill;
	cin >> n >> skill;
	for(int i = 0; i < n; i++){
		cin >> sval[i];
	}
	for(int i = 0; i < n; i++){
		cin >> fval[i];
	}
	add_line(line(skill, 0));

	for(int i = 0; i < n; i++){
		dp[i] = query(sval[i]);
		add_line({fval[i], dp[i]});
	}
	cout << dp[n-1] << endl;
	return 0;
}

