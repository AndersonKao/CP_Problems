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
const ll MAXL = 500000;
const ll prime = 0xdefaced;
const ll prime_mod = 1073676287;
vector<ll> h, rh;
vector<ll> h_base(MAXL + 1);

void hash_init(string& str){
	h.resize(str.length()+1);
	h[0] = 0;	
	for(int i = 1; i <= str.length(); i++){
		h[i] = (h[i-1] * prime + str[i-1]) % prime_mod;
	}
}
void rhash_init(string str){
	reverse(al(str));
	rh.resize(str.length()+1);
	rh[0] = 0;	
	for(int i = 1; i <= str.length(); i++){
		rh[i] = (rh[i-1] * prime + str[i-1]) % prime_mod;
	}
}
bool check(int idx){
		
}

int main(){
	h_base[0] = 1;
	for(int i = 1; i <= MAXL; i++){
		h_base[i] = (h_base[i-1] * prime) % prime_mod;
	}
	int T;
	cin >> T;
	while(T--){
		string str;
		cin >> str;
		string cpstr(str);
		sort(cpstr.begin(), cpstr.end());
		if(str == cpstr){
			str << endl;
			continue;
		}
		hash_init(str);
		rhash_init(str);
		int st = 0;
		while(str[st] == cpstr[st]) st++;
		int curans = st;
		int ed = st + 1;
		while(ed < str.length()){
			int l = 0, r = str.length()-1;		
			while(l < r){
				int m = (l+r)>>1;
				if(check(m, st, ed)){
					l = m+1;
				}
				else{
					r = m;
				}
			}
			// l = first difference


		}
		
	}

	return 0;
}

