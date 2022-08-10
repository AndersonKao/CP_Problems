#include <bits/stdc++.h>
#define eb emplace_back
#define al(x) x.begin(), x.end()
#define F first
#define S second
#define mp make_pair
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << #x << ": " << x.F << ", " << x.S << endl;
using namespace std;
using pii = pair<int ,int>;
const double disINF = 1e20;
int n, b1, b2;
vector<pii> pos;
vector<vector<double>> dp;
vector<vector<pii>> tdp;
const double eps = 1e-6;
int fcmp(double a, double b){
	if(fabs(a-b) < eps)
		return 0;
	return (a > b) * 2 -1;
}
double getdis(int i, int j){
	int xoff = pos[i].F - pos[j].F, yoff = pos[i].S - pos[j].S;
	return sqrt(xoff * xoff + yoff * yoff);
}
int main(){
	int caseN = 1;
	while(cin >> n >> b1 >> b2){
		if(n == 0 && b1 == 0 && b2 == 0)
			break;
//		b1--, b2--;
		pos.clear();
		dp.clear();
		dp.resize(n, vector<double>(n, disINF));
		tdp.clear();
		tdp.resize(n, vector<pii>(n, pii(-1, -1)));
		for(int i = 0; i < n; i++){
			int x, y;
			cin >> x >> y;
			pos.eb(x, y);
		}
#ifdef Ddis
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				debug(i);
				debug(j);
				debug(getdis(i, j));
			}
		}
#endif
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
//				cout << "dping " << i << ", " << j << endl;
				if(i == 0 && j == 0){
					dp[i][j] = 0.0;
					continue;
				}
				if(i == j)
					continue;
				if(j < i){
					if(i == b2){
//						cout << "invalid i == b2\n";
						continue;
					}
					if(j == i-1){
						//cout << "case j = i-1\n";
						for(int k = 0; k < max(j, 1); k++){
							if(fcmp(dp[i][j], dp[k][j] + getdis(k, i)) > 0){
								dp[i][j] = dp[k][j] + getdis(k, i);
								tdp[i][j] = mp(k, j);
							}
						}
						//debug(dp[i][j]);
					}	
					else{
						dp[i][j] = dp[i-1][j] + getdis(i-1, i);
						//debug(dp[i][j]);
						tdp[i][j] = mp(i-1, j);
					}
				}
				else if(j > i){
					if(j == b1){
//						cout << "invalid j == b1\n";
						continue;
					}
					if(i == j-1){
						//cout << "case i = j-1\n";
						for(int k = 0; k < max(i, 1); k++){
//							dp[i][j] = min(dp[i][j], dp[k][j-1] + getdis(k, j);
							if(fcmp(dp[i][j], dp[i][k] + getdis(k, j)) > 0){
								dp[i][j] = dp[i][k] + getdis(k, j);
								tdp[i][j] = mp(i, k);
							}
						}
//						debug(dp[i][j]);
					}	
					else{
						dp[i][j] = dp[i][j-1] + getdis(j-1, j);
//						debug(dp[i][j]);
						tdp[i][j] = mp(i, j-1);
					}
				}
			}
		}
#ifdef Ddp
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cout << i << ", " << j << ":\n";
				debug(dp[i][j]);
				depii(tdp[i][j]);
			}
		}
#endif
		double ans = disINF;
		pii apii;
		for(int k = 0; k < n-1; k++){
			if(fcmp(ans, dp[n-1][k] + getdis(k, n-1)) > 0){
				ans = dp[n-1][k] + getdis(k, n-1);
				apii = mp(n-1, k);
			}
			if(fcmp(ans, dp[k][n-1] + getdis(k, n-1)) > 0){
				ans = dp[k][n-1] + getdis(k, n-1);
				apii = mp(k, n-1);
			}
		}
		cout << "Case " << caseN++ << ": ";
		cout << fixed << setprecision(2) << ans << endl;
		vector<int> arr[2];
		while(apii.F != -1 && apii.S != -1){
			//depii(apii);
			pii& prv = tdp[apii.F][apii.S];
			if(prv.F == apii.F){
				arr[0].eb(apii.S);
			}
			else if(prv.S == apii.S){
				arr[1].eb(apii.F);
			}
			else{
//				cout << "Error\n";
			}
			apii = prv;
		}
		int to = 0;	
		for(int i = 0; i < arr[0].size(); i++){
			if(arr[0][i] == 1){
				reverse(al(arr[0]));
				to = 0;
				break;
			}
		}
		for(int i = 0; i < arr[1].size(); i++){
//			cout << arr[1][i] << " ";
			if(arr[1][i] == 1){
				reverse(al(arr[1]));
				to = 1;
				break;
			}
		}
		cout << 0;
		for(int i = 0; i < arr[to].size(); i++){
			cout << " " << arr[to][i];
		}
		for(int i = 0; i < arr[to^1].size(); i++){
			cout << " " << arr[to^1][i];
		}
		cout << " 0\n";
//		cout << endl;
	}
	return 0;
}
