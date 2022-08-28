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
ll h[MAXL+1], rh[MAXL+1];
ll h_base[MAXL + 1];
string str, cpstr;

void hash_init(string& str){
	h[0] = 0;	
	for(int i = 1; i <= str.length(); i++){
		h[i] = (h[i-1] * prime + str[i-1]) % prime_mod;
	}
}
void rhash_init(string& str){
	rh[0] = 0;	
	for(int i = 1; i <= str.length(); i++){
		rh[i] = (rh[i-1] * prime + str[str.length() - i]) % prime_mod;
	}
}
ll get_hash(int l, int r){
	return (h[r] - (h_base[r - l + 1] * h[l-1] % prime_mod) + prime_mod) % prime_mod;
}
ll get_rhash(int l, int r){
	return (rh[r] - (h_base[r - l + 1] * rh[l-1] % prime_mod) + prime_mod) % prime_mod;
}
ll gen_hash(int idx, int st, int ed, int len){
	idx += 1, st+=1, ed+=1;
	ll hash = 0;
	if(idx < st){
#ifdef Dgen
	printf("hash of %d, reverse %d, %d is %lld\n", idx-1, st-1, ed-1, h[idx]);
#endif
		return h[idx];	
	}
	else{
		hash = (h[(st - 1)] * h_base[idx - (st - 1)]) % prime_mod;
	}
	int rst = len - ed + 1;
	int red = len - st + 1;
	int ridx = rst + (idx - st);
	if(idx <= ed){
		hash += get_rhash(rst, ridx);
		hash %= prime_mod;
	}
	else{
		hash += get_rhash(rst, red) * h_base[idx - ed];
		hash %= prime_mod;
		hash += get_hash(ed+1, idx);
		hash %= prime_mod;
	}
#ifdef Dgen
	printf("hash of %d, reverse %d, %d is %lld\n", idx-1, st-1, ed-1, hash);
#endif
	return hash;	
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	h_base[0] = 1;
	for(int i = 1; i <= MAXL; i++){
		h_base[i] = (h_base[i-1] * prime) % prime_mod;
	}
	int T;
	cin >> T;
	while(T--){
		cin >> str;
		cpstr = str;
		sort(cpstr.begin(), cpstr.end());
		if(str == cpstr){
			cout << str << endl;
#ifdef Dans
			cout << "same as before\n";
#endif
			continue;
		}
		hash_init(str);
		rhash_init(str);
		int st = 0;
		while(str[st] == cpstr[st]) st++;
		int curans = st; //reverse [st, curans].
		for(int ed = st+1; ed < str.length(); ed++){
#ifdef Dfor
			cout << "try " << ed << "-------------------\n";
#endif
			int l = st, r = str.length();		
			while(l < r){
				int m = (l+r)>>1;
				if(m == str.length())
					break;
				ll anshash = gen_hash(m, st, curans, str.length());
				ll edhash = gen_hash(m, st, ed, str.length());
#ifdef Dbi
				printf("l: %d, r: %d, m:%d\n", l, r, m);
				debug(anshash);
				debug(edhash);
#endif
				if(anshash == edhash){
					l = m+1;
				}
				else{
					r = m;
				}
			}
			// l = first difference
			int ansi = l, cmpi = l;
			if(l <= curans){
				ansi = curans - (l - st);
			}
			if(l <= ed){
				cmpi = ed - (l - st);
			}
#ifdef Dbi
			printf("first diff at %d\n", l);
			debug(ansi);
			debug(cmpi);
#endif
			if(l < str.length() && str[ansi] > str[cmpi]){
				curans = ed;
#ifdef Dans
				printf("renew ans to %d\n", curans);
#endif
			}
		}
//		debug(curans);
		reverse(str.begin() + st, str.begin()+curans+1);
		cout << str << endl;
	}
	return 0;
}

