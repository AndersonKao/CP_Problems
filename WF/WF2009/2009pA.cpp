#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define F first
#define S second
vector<pii> range;
const double eps = 0.00001;
int fcmp(double a, double b){
	if(abs(a-b) < eps)
		return true;
	return (a > b) * 2 - 1;
}
bool valid(double t){	
	vector<int> it(range.size());	
	iota(it.begin(), it.end(), 0);

	bool sol = false;
	do{
		double T = range[it[0]].F + t;
		for(int i = 1; i < it.size(); i++){
			double L = range[it[i]].F, R = range[it[i]].S;
			if(fcmp(T, R) > 0){
				break;
			} 		
			else if(fcmp(T, L) < 0){
				T = L + t;	
			}
			else{
				T = T + t;
			}
			if(i == it.size() -1)
				sol = true;
		}
	}while(next_permutation(it.begin(), it.end()) && sol == false);
	return sol;
}

int main(){
	int n;
	int caseN=1;
	while(cin >> n){
		if(n == 0)
			break;
		range.resize(n);	
		for(int i = 0; i < n; i++){
			cin >> range[i].first >> range[i].second;
		}
		double L = 0.0, R = 1440.0;
		while(abs(R-L) > eps){
			double M = (L+R)/2;
			if(valid(M)){
				L = M;	
			}
			else
				R = M;
		}	
		double m, s;
		s = modf(R + eps, &m);
		cout << "Case " << caseN++ << ": " << (int)(m) << ":" << setw(2) << setfill('0') << (int)(round(s * 60)) << endl;
	}
	return 0;
}
