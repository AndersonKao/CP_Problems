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
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;

int main(){
	int n;
	cin >> n;
	double c;
	cin >> c;	
	vec<p<double>> pts(n);
	double sx = 0.0;
	for(p<double>&e: pts){
		cin >> e.F >> e.S;
		sx += e.F;
	}
	sx /= n;
	double cost = 0.0;
	for(p<double>&e: pts){
		double xd = e.F - sx, yd = e.S - c;
		cost += xd*xd + yd*yd;
	}
	cout << fixed << setprecision(10) << cost << endl;


	return 0;
}

