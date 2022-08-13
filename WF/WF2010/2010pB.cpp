// first narrow range should be
// L = V[0] / 1.05 * 0.95, R = V[0] / 0.95 * 1.05
// range case can be 0. (>= 0 will causes error
#include <bits/stdc++.h>
using namespace std;
#define al(x) x.begin(), x.end()
#define eb emplace_back
#define F first
#define S second
#define LC(x) (x * 2 + 1)
#define RC(x) (x * 2 + 2)
#define debug(x) cout << #x << ": " << x << endl;
using ll = long long;
const double eps = 1e-6;
int fcmp(double a, double b){
	if(abs(a-b) < eps){
		return 0;
	}
	return (a>b) * 2 - 1;
}
char decode(vector<int>& code, int pos){
	int res = 4;	
	int ans = 0;
#ifdef Ddecode
cout << "decoding: ";	
#endif
	for(int i = pos; i < code.size() && i < pos + 5; i++){
#ifdef Ddecode
		cout << code[i];
#endif
		if(code[i]){
			ans += (1 << res);
		}
		res--;
	}
#ifdef Ddecode
	cout << endl;
	debug(ans);
#endif

	if(ans == 1){
		return '0';
	}
	else if(ans == 17){
		return '1';
	}
	else if(ans == 9){
		return '2';
	}
	else if(ans == 24){
		return '3';
	}
	else if(ans == 5){
		return '4';
	}
	else if(ans == 20){
		return '5';
	}
	else if(ans == 12){
		return '6';
	}
	else if(ans == 3){
		return '7';
	}
	else if(ans == 18){
		return '8';
	}
	else if(ans == 16){
		return '9';
	}
	else if(ans == 4){
		return '-';
	}
	else if(ans == 6){
		return 'S';
	}
	else 
		return ' ';
}
int main(){
	int m;
	int caseN = 1;
	while(cin >> m){
		if(m == 0)
			break;
		vector<double> Vs(m);
		vector<int> type(m, 0);
		for(int i = 0; i < m; i++){
			cin >> Vs[i];
		}
		double thin_base = Vs[0];
#ifdef Debug
		debug(thin_base);
		debug(thin_base / 1.05 * 0.95);
		debug(thin_base / 0.95 * 1.05);
#endif
		bool badcode = false;
		for(int i = 0; i < m; i++){
			if(fcmp(thin_base / 1.05 * 0.95, Vs[i]) <= 0 && fcmp(Vs[i], thin_base /0.95 * 1.05  + eps) <= 0){
				type[i] = 0;
			}
			else if(fcmp(Vs[i], thin_base /1.05 * 0.95 ) <= 0){
#ifdef Debug
		cout << "too small\n";
#endif
				badcode = true;
				break;
			}
			else{
				type[i] = 1;
			}
		}
#ifdef Debug
		for(int i = 0; i < m; i++){
			cout << type[i] ;
		}
		cout << endl;
#endif
		double nmin, nmax, wmin, wmax;
		nmin = wmin = numeric_limits<double>::max();
		nmax = wmax = 0.0;
		for(int i = 0; i < m; i++){
			if(type[i] == 0){
				nmin = min(nmin, Vs[i]);
				nmax = max(nmax, Vs[i]);
			}
			else{
				wmin = min(wmin, Vs[i]);
				wmax = max(wmax, Vs[i]);
			}
		}
#ifdef Debug
		debug(nmin);
		debug(nmax);
		debug(wmin);
		debug(wmax);
#endif
		double nL, nR, wL, wR;
		nR = (nmin / 0.95) * 2.0 + eps;
		nL = (nmax / 1.05) * 2.0 - eps;
		if(fcmp(nL, nR) > 0){
			badcode = true;
#ifdef Debug
		cout << "narrow range\n";
#endif
		}
		wR = (wmin / 0.95) + eps;
		wL = (wmax / 1.05) - eps;
		if(fcmp(wL, wR) > 0){
			badcode = true;
#ifdef Debug
		cout << "wide range\n";
#endif
		}
		double bL = max(nL, wL), bR = min(nR, wR);
		if(fcmp(bL, bR) > 0){
			badcode = true;
#ifdef Debug
		cout << "no range\n";
#endif
		}
		if(badcode){
			cout << "Case " << caseN++ << ": bad code\n";
			continue;
		}
		if(decode(type, 0) != 'S'){
			reverse(al(type));
#ifdef Debug
			cout << "have to reverse\n";
#endif
		}
		if(decode(type, 0) != 'S')
			badcode = true;
		if(badcode){
			cout << "Case " << caseN++ << ": bad code\n";
#ifdef Debug
		cout << "reversing no \n";
#endif
			continue;
		}
		vector<char> destr;	
		vector<int> deval;
		int idx = 5;
#ifdef Debug
		for(int i = 0; i < m; i++){
			cout << type[i] ;
		}
		cout << endl;
#endif
		bool goodend = false;
		while(idx < type.size()){
			if(type[idx] != 0){
				badcode = true;
				break;
			}
			idx++;
			char ch = decode(type, idx);
			if(ch == ' '){
				badcode = true;
				break;
			}
//			debug(ch);
			if(ch == 'S' && idx + 5 == type.size()){
				goodend = true;
				break;
			}
			destr.eb(ch);
			deval.eb(ch == '-' ? 10 : ((int)ch - '0'));
			idx += 5;
		}
		if(badcode || goodend == false){
			cout << "Case " << caseN++ << ": bad code\n";
#ifdef Debug
		cout << "decoding error \n";
#endif
			continue;
		}
#ifdef Debug
			for(int i = 0; i < destr.size(); i++)
				cout << destr[i];
			cout << endl;
#endif
		ll Csum, Ksum;
		Csum = Ksum = 0;
		int Cn = deval.size() - 2;
		for(int i = 0; i < Cn; i++){
			Csum += (((Cn-(i+1)) % 10) + 1)*deval[i];
			Ksum += (((Cn-(i+1)+1) % 9) + 1)*deval[i];
		}	
		Ksum += (((0 % 9) + 1 ) * deval[Cn]);
		Csum %= 11;
		Ksum %= 11;
		cout << "Case " << caseN++ << ": ";
		if(Csum != deval[Cn]){
			cout << "bad C";
		}
		else if(Ksum != deval[Cn+1]){
			cout << "bad K";
		}
		else{
			for(int i = 0; i < Cn; i++)
				cout << destr[i];
		}
		cout << endl;

	}
	return 0;
}
