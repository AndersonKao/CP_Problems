// AC 2022-07-19 20:39:38
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
#define eb emplace_back
#define F first
#define S second
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")\n";
bool solve(vector<pii>& poly, int x, ll D){
	int pw = 0;		
	ll res = 1;
	ll  ans = 0;
	for(pii&e: poly){
		while(pw < e.S){
			res *= x;	
			res %= D;
			pw++;
		}
		ans += ((e.F * res) % D +D) %D;	
		ans = (ans % D + D)%D;
	}
	return ans == 0;
}
int main(){
	string str;
	int caseN = 1;
	while(cin >> str){
		if(str == ".")
			break;
		vector<pair<int, int>> poly;
		int E = 0;
		ll C = 0, D = 0;
		bool meetn = false, meetend = false;
		int neg = 1;
		int i = 1;
		int maxE = 0;
		while(meetend == false){
			if(isdigit(str[i])){
				if(meetn){
					E*=10;
					E+=(str[i] - '0');
				}
				else{
					C*= 10;
					C+= (str[i] - '0');
				}
			}
			else if(str[i] == 'n'){
				meetn = true;
				if(C == 0)
					C=1;
			}
			else if(str[i] == '-'){
				if(i != 1){
					if(meetn && E== 0)
						E = 1;
					poly.eb(C * neg,E);
					maxE = max(E, maxE);
					C = E = 0;	
					meetn = false;
					neg = 1;
				}
				neg = -1;
			}
			else if(str[i] == '+' || str[i] == ')'){
				if(meetn && E== 0)
					E = 1;
				poly.eb(C * neg,E);
				maxE = max(E, maxE);
				C = E = 0;	
				meetn = false;
				neg = 1;
				if(str[i] == ')')
					meetend = true;
			}
			i++;
		}	
		i++;
		while(i < (int) str.length()){
			D *= 10;
			D += (str[i++] - '0');	
		}
		#ifdef Dpoly
		cout << str << endl;
		for(pii&e: poly){
			depii(e);	
		}
		debug(D);
		#endif
		reverse(poly.begin(), poly.end());
		bool ans = true;
		for(int i = 1; i <= maxE+1; i++){
			if(solve(poly, i, D) == false){
				ans = false;
				break;
			}
		}
		cout << "Case " << caseN++ << ": " << (ans ? "Always an integer" : "Not always an integer") << endl;	
	}
	return 0;
}
