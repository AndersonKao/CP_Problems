#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template <typename T> using vec = vector<T>;
template <typename T> using p = pair<T, T>;
template <typename T> using deq = deque<T>;

#define F first
#define S second
#define eb emplace_back
#define al(x) x.begin(),x.end()
#define debug(x) cout << #x << ": " << x << endl;
double fcmp(double a, double b, double eps=1e-9) {
	if (abs(a-b) < eps) return 0;
	return a-b;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	vec<string> onlys;
	int n;
	cin >> n;
	vec<double> rate(n);
	vec<p<string>> pi(n);
	vec<p<int>> trans(n);
	for(int i = 0; i < n; i++){
		cin >> pi[i].F >> pi[i].S >> rate[i];
		onlys.eb(pi[i].F);
		onlys.eb(pi[i].S);
	}
	onlys.eb("pink");
	onlys.eb("blue");
	sort(al(onlys));
	onlys.resize(unique(al(onlys)) - onlys.begin());

	for(int i = 0; i < n; i++){
		trans[i].F = lower_bound(al(onlys), pi[i].F) - onlys.begin();
		trans[i].S = lower_bound(al(onlys), pi[i].S) - onlys.begin();
	}
	vec<double> best(onlys.size(), 0.0);
	int x = lower_bound(al(onlys), "pink") - onlys.begin();
	int y = lower_bound(al(onlys), "blue") - onlys.begin();
//	cout << onlys.size() << endl;
	vec<bool> seq(onlys.size(), false);
	best[x] = numeric_limits<double>::min(); 
	seq[x] = true;
	for(int i = 0; i < n; i++){
		int f, t;
		tie(t, f) = trans[i];
		/*
		cout << pi[i].F << " " << pi[i].S << " " << rate[i] << endl;
		cout << trans[i].F << " " << trans[i].S << " " << rate[i] << endl;
		debug(f);
		debug(t);
		cout << best[f] << ", " << best[t] <<endl;
		cout << log(rate[i]) << endl;
		*/
		if(seq[f]){
			if(seq[t]){
				best[t] = max(best[t], best[f] + log(rate[i]));
			}
			else{
				seq[t] = true;
				best[t] = best[f] + log(rate[i]);
			}
		}
		/*
		for(int j = 0; j < n; j++){
			cout << best[j] << " ";
		}
		cout << endl;
		*/
	}
	double ans = 0.0;
	cout << fixed << setprecision(10);
	if(best[y])
		ans = exp(best[y]);
	if(ans >= 10.0)
		cout << 10.000000000000 << endl;
	else
		cout << ans << endl;
	
	return 0;
	
}
