// AC 2022-03-18 09:15:36
// PE
// WA
// 10^6 forget to check
#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second

#define DMAX 1e12
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
template<typename T> using vec =vector<T>;
using pii = pair<int, int>;
using ll = long long;
const double eps = 1e-9;
const int eq= 0;
const int gt = 1;
const int lt = -1;
int fcmp(double a, double b){
	if(abs(a - b) < eps)
		return 0;
	return a - b > 0.0 ? gt : lt;
}

vec<pii> island;
vec<vec<double>> dis;
vec<vec<double>> dp;
int main(){
	int n, cap;
	int Case = 1;
	while(cin >> n >> cap){
		if(!n && !cap)
			break;
		island.resize(n);
		dis.clear();
		dis.resize(n, vec<double>(n, 0.0));
		dp.clear();
		dp.resize(n, vec<double>(n, DMAX));
		REP(i, n){
			cin >> island[i].X >> island[i].Y;
		}
		REP(i, n){
			REP(j, n){
				if(i == j){
					continue;
				}
				else{
					ll xLen = island[i].X - island[j].X * 1LL;
					ll yLen = island[i].Y - island[j].Y * 1LL;
					dis[i][j] = dis[j][i] = sqrt((double)(xLen * xLen + yLen * yLen));
				}
			}
		}
		double C = (double)cap;
		double availC = cap / 3.0;
		double halfC = cap / 2.0;
		int end = n - 1, st = 0;
/*
		REP(i, n)
			REP(j, n)
			if (i != j){
				if(fcmp(halfC, dis[i][j]) > 0)				
					cout << i << " to " << j << " is possible with dis = " << dis[i][j] << endl;
				else
					cout << i << " to " << j << " is impossible with dis = " << dis[i][j] << endl;
			}	
*/
		REP(i, end){
			if (fcmp(halfC, dis[i][end]) > 0)				
				dp[i][0] = dis[i][end];
			// debug
//			cout << i << ": " << dp[i][0] << (i == n - 2 ? '\n' : ' ');
		}
		
		REP1(j, n-1){
			REP(i, end) {
				REP1(k, end-1){
					if (i == k)
						continue;
					if (fcmp(halfC , dis[k][i]) <= 0)
						continue;
					double remainC = C - 2*dis[k][i];
/*
					cout << "j, i, k = " << j << ", " <<i << ", " << k << endl;
					cout << "reamin C: " << remainC << endl;
					cout << "dp[k][j-1] : " << dp[k][j-1] << endl;
*/
					if (fcmp(remainC, dp[k][j-1]) >= 0) {
//						cout << "case : one round\n";
						dp[i][j] = min(dp[i][j], dis[k][i] + dp[k][j-1]);	
					}
					else if (fcmp(availC, dis[k][i]) >= 0){
						double times = ceil((dp[k][j-1] - remainC) / (C - 3 * dis[k][i]));
						//double cost =  C- dis[k][i]; // only food
						double cost =  2* dis[k][i]; // only food
						//double lastround = dis[k][i] + (dp[k][j-1] - times * (cap - 3*dis[k][i]));
						double lastround = dis[k][i];
/*
						cout << "case : multi round\n";
						cout << "it takes " << times << endl;
						cout << "each time with cost : " << cost << endl;
*/
						//dp[i][j] = min(dp[i][j], times * cost + lastround);
						dp[i][j] = min(dp[i][j], dp[k][j-1] + times * cost + lastround);
					}
		//			cout << dp[i][j] << endl;	
				}
			}
		}
		
		double ans = DMAX;		

		REP(i, n){
			ans = min(ans, dp[0][i]);
		}
		cout << "Trial " << Case++ << ": ";
		if(fcmp(ans, DMAX) == 0 || fcmp(ans, 1e6) > 0){
			cout << "Impossible\n" << endl;
		}else
			cout << (ll)(ceil(ans)) << " units of food"<< endl << endl;
	}

	return 0;
}
