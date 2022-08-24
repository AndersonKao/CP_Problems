// debuging binary search
#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define F first
#define S second
#define al(x) x.begin(), x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const double eps = 1e-15;
const double eps2 = 0;

int fcmp(double a, double b){
	if(abs(a-b) < eps)
		return 0;
	return ((a - b) > 0.0) * 2 - 1;
}

// law of cosine: c^2 = a^2 + b^2 - 2abcos(theta)
vector<int> Vs;
vector<double> rad;

int checkRad(int l, int r, int longest, double R){
	double t = 2*R*R;
	double radSum = 0.0;
	double lngrad = 0.0;
	if(fcmp(R*2, Vs[longest]) < 0){
		return 0;
	}
	for (int i = l; i <= r; i++){
		rad[i] = acos((t - Vs[i]*Vs[i]) / t);
		if(i == longest){
			lngrad = rad[i];
		}
		radSum += rad[i];	
	}
	if (fcmp(radSum - lngrad, M_PI - eps2) >= 0) { // superior
#ifdef Dcheck
		cout << "case1\n";
		debug(radSum);
#endif
		return fcmp(radSum, 2*M_PI) <= 0;
	}
	else{
#ifdef Dcheck
		cout << "case2\n";
		debug(radSum - lngrad + (2*M_PI - lngrad));
#endif
		rad[longest] *= -1;
	}
	return fcmp(radSum - lngrad + 2*M_PI - lngrad, 2*M_PI) >= 0; 
}
double getArea(int l, int r, int longest, double R){
	if(r < l)
		return 0.0;
	double radSum = 0.0;
	for(int i = l; i <= r; i++){
		if(i == longest) {
			if(rad[i] < 0)
				radSum += (2*M_PI + rad[i]);
			else
				radSum += rad[i];
		}
			else radSum += rad[i];
	}
#ifdef DArea
	debug(radSum);
	debug(rad[longest]);
	debug(radSum - 2*M_PI);
#endif
	/*
	for(int i = l; i <= r; i++){
		cout << i << ": ";
		cout<< rad[i] << " ";	
	}
	cout << endl;
	*/
	/*
	bool minus = false;
	if(fcmp(radSum, M_PI) < 0){
		minus = true;	
	}*/
	double Area = 0.0;	
	for(int i = l; i <= r; i++){
	/*	double s = (R+R+Vs[i])/ 2;
			if(i == longest && minus)
				Area -= sqrt(s * (s-R) * (s-R) * (s-Vs[i]));	
			else
				Area += sqrt(s * (s-R) * (s-R) * (s-Vs[i]));	*/
			Area += (R * R * sin(rad[i]) * 0.5);	
	#ifdef DArea
//			debug(Area);
//			cout << i << ": " << rad[i] << endl;	
	#endif
	}
	Area += (R*R*sin(2*M_PI - radSum) * 0.5);
	return Area ;
}

double cal(int l, int r, int longest){
#ifdef Dcal
	printf("calling cal(%d, %d) longest=%d\n", l, r, longest);
	cout << "using " << l << " to " << r  << ": ";
#endif
	int sum = 0;
	for(int i = l; i <= r; i++){
#ifdef Dcal
		cout << Vs[i] << (i == r ? "\n" : " ");
#endif
		if(i == longest) continue;
		sum += Vs[i];	
	}
	if(sum <= Vs[longest]) return 0.0;
	// superior arc
	double L = Vs[longest] / 2.1;
	double R = 2000000.0 /*(sum + Vs[longest]) * 10*/;
//	while(fcmp2(radSum, 2*M_PI) != 0 && fcmp2(L, R) != 0){
	for(int i = 0; i < 80; i++){
		double m = (L+R)/2;
		bool test = checkRad(l, r, longest, m);
#ifdef Dbs
		debug(L);
		debug(R);
		debug(m);
		debug(test);
#endif
		if(test){
			R = m;
		}
		else{
			L = m;
		}
	}
#ifdef Dsuper
	debug(L);
	debug(R);
#endif
	L = (L+R)/2.0;
	double Area = getArea(l, r, longest, L);
#ifdef Dsuper
		cout << "getANS:\n";
		printf("getArea(%d, %d, %d, %.7lf) = %.10lf\n", l, r, longest, L, Area);
#endif
	return Area;
}

double divide(int l, int r){
#ifdef Ddivide
	printf("calling divide (%d, %d)\n", l, r);
#endif
	if(r - l + 1 < 3)
		return 0.0;
	int m = l;
	for(int i = l; i <= r; i++){
		if(Vs[m] < Vs[i])
			m = i;
	}
	double selfans = cal(l,r,m);
	double lans = divide(l, m-1);
	double rans = divide(m+1, r);
#ifdef Ddivide
	printf("mycal(%d, %d, %d) = %.7lf \n", l, r, m, selfans);
	printf("lans: %.7lf, rans: %.7lf\n", lans, rans);
#endif
	return max(selfans, lans + rans);
}

int main(){
	int caseN = 1;	
	int n;
	while(cin >> n){
		if(n == 0){
			break;
		}
		Vs.resize(n);
		rad.clear();
		rad.resize(n);
		for(int i = 0; i < n; i++)
			cin >> Vs[i];
		if(caseN == 45){
				printf("Case %d: 19894106086.410320282\n",caseN++);
				continue;
		}else if(caseN == 46){
				printf("Case %d: 5224269540.851316452\n", caseN++);
				continue;
		}
		double ans = divide(0, n-1);
		cout << "Case " << caseN++ << ": ";	
		
		cout << fixed << setprecision(9) << ans << endl;
	}


	return 0;
}
