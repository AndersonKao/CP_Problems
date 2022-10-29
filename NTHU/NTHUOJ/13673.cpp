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
int pwr[10];
string str;
int idx = 0;
bool sol = true;
int ans = 0;
void gen(int k){
	if(k < 0 || idx == str.length()){
		sol = false;
		return;	
	}
	if(str[idx] == '1'){
		idx++;
		ans += pwr[k] * pwr[k];
	}
	else if(str[idx] == '2'){
		idx++;
		for(int i = 0; i < 4; i++){
			gen(k-1);
		}
	}
	else{
		idx++;
	}
}

int main(){
	int S;
	cin >> S;
	cin >> str;	
	pwr[0] = 1;
	for(int i = 1; i < 10; i++){
		pwr[i] = pwr[i-1] * 2;
	}
	gen(S);
	if(sol && idx == str.length()){
		cout << ans;
	}
	else{
		cout << "Domo";
	}
	return 0;
}

