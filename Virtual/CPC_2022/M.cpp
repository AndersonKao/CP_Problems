#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

// #define dbg

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

#ifndef dbg
#define endl '\n'
#define debug(x) ;
#define devec(v) ;
#define devec2(v) ;
#else
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
#endif

const int INF = 1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

ll Ans[100005] = {0};
void build() {
	for(ll n=1; n<=100000; n++) {
		ll ans = 0;
        ll i;
		for(i=n;i*i>n;) {
			ll R;
			ll num = n/i;
			R = n/(num+1);
			int l = R, r = i;
			while(l < r) {
				int m = (l+r)/2;
				if(n/m == num) r = m;
				else l = m+1;
			}; 
			R = r;
			ans+=(i-R+1) * n*(n-1)/2 * (num-1);
			ans%=MOD;
			i = R-1;
		}
		
		for(ll j=1;j<=i;j++) {
			ll num = n / j - 1;
            ans += (n * (n-1) / 2 * num);
            ans %= MOD; 
		}
		Ans[n] = ans;
		//printf("%lld\n",Ans[n]);
	}
}

int main()
{
	yccc;
	int c;
	cin >> c;
	build();
	int n;
	while (c--) {
			cin >> n;
			cout << Ans[n-1] << endl;
	}
}
