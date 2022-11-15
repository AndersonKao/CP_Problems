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
const int maxn = 100000;
int N, C, D;
struct machine{
	int	Day, Price, Revenue, Gain;
};
int main(){
//	yccc;
	while(cin >> N >> C >> D){
		if(N == 0 && C == 0 && D == 0){
			break;
		}
		vec<machine> macs(n);
		REP(i, N){
			cin >> macs[i].Day >> macs[i].Price >> macs[i].Revenue >> macs[i].Gain;
		}
		sort(al(macs), [](machine& a, machine& b){
				return a.Day < b.Day;
			});
		

		


	}	

	return 0;
}

