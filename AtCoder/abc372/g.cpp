
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
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

// O(log(min(a, b)))
// returns gcd and one solution to a*x+b*y=gcd(a,b)
int ext_gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// iterative version of extend gcd
int ext_gcd_iter(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

// find one solution (x0, y0) s.t. a*x0+b*y0=c
// first by finding a sol for a*x+b*y=g.
// since c % g = 0, a*x*(c/g)+b*x*(c/g)=c.
bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = ext_gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false; // proof: a linear combination of a, b is divisible by gcd
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void shift_solution(int & x, int & y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

// # of sols(x,y) s.t. a*x+b*y = c between x,y range
int find_all_solutions(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    int lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    int rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    int lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    int rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if (lx > rx)
        return 0;
    return (rx - lx) / abs(b) + 1;
}
/*
iterate all solutions
x = lx + k (b/g) for all k >= 0, until x = rx.

Theorems 
1. The set of solution a*x+b*y=c is
    x = x0 + k*(b/g), y = x0 - k*(a/g).
2. smallest possible val
 x' + y' = x + y + k(b-a)g, minimize k*(b-a) 
if a<b pick smallest k, a>b otherwise.
*/
const int maxn = 200005;
int A[maxn], B[maxn], C[maxn];
int n;
int test_all(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    int lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    int rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    int lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    int rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if (lx > rx){
        return 0;
	}
	int res = 0;
	for(int k = 0; x <= rx; k++){
		x = lx + k * (b/g);
		y = (c - a * x)/b;
		for(int i = 0; i < n; i++){
			if(A[i] * x + B[i] * y != C[i]){
				break;
			}
			if(i == n-1)
				res++;
		}
	}

    return res;
}


void solve(){
	cin >> n;
//	vec<pair<int, int>> nums(n);
	int mi = 0;
	int mcnt = INT_MAX;
	for(int i = 0; i < n; i++){
		cin >> A[i] >> B[i] >> C[i];
		int cnt = find_all_solutions(A[i], B[i], C[i], 0, C[i] / A[i] + 1, 0, C[i] / B[i] + 1);
		if(cnt < mcnt){
			mcnt = cnt;
			mi = i;
		}
	}
	
	if(mcnt == 0){
		cout << 0 << endl;
		return;
	}	
	cout << test_all(A[mi], B[mi], C[mi], 0, C[mi] / A[mi] + 1, 0, C[mi] / B[mi] + 1) << endl;

}

int main(){
	yccc;		
	int t;
	cin >> t;
	while(t--){
		solve();
	}

	return 0;
}

