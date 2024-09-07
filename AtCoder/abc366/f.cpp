#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, treeorder_statistics_node_update>;
*/
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define ln '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;

bool cmp(pii &A, pii& B){
	int a = B.F * A.S + B.S;
	int b = A.F * B.S + A.S;
	return a >= b;
}
// Miminimum Li Chao Tree
typedef long long ftype;
typedef complex<ftype> point;
#define x real
#define y imag

ftype dot(point a, point b) {
    return (conj(a) * b).x();
}

ftype f(point a,  ftype x) {
    return dot(a, {x, 1});
}

const int maxn = 2e5;

point line[4 * maxn];

/*
a line is  y = k * x + b, using point to represent it.
y = (k, b) * (x, 1) (dot operation).
*/
// y = nw.real() * x + nw.imag().
void add_line(point nw, int idx = 1, int l = 0, int r = maxn)
{
    int m = (l + r) / 2;
    bool lef = f(nw, l) > f(line[idx], l);
    bool mid = f(nw, m) > f(line[idx], m);
    if(mid) {
        swap(line[idx], nw);
    }
    if(r - l == 1) {
        return;
    } else if(lef != mid) {
        add_line(nw, 2 * idx, l, m);
    } else {
        add_line(nw, 2 * idx + 1, m, r);
    }
}

// get minimum in some point x;
ftype get(int x, int idx = 1, int l = 0, int r = maxn)
{
    int m = (l + r) / 2;
    if(r - l == 1) {
        return f(line[idx], x);
    } else if(x < m) {
        return max(f(line[idx], x), get(x, 2 * idx, l, m));
    } else {
        return max(f(line[idx], x), get(x, 2 * idx + 1, m, r));
    }
}

int main(){
	yccc;		
	int n, k;
	cin >> n >> k;
	vec<pair<int, int>> V(n);
	for(int i = 0; i< n; i++){
		int a, b;
		cin >> a >> b;
		add_line({a, b});
	}
	ll val = 1;
	for(int i =0; i < k; i++){
		
		val = V[i].F * val + V[i].S;
	}
	cout << val <<endl;

	return 0;
}

