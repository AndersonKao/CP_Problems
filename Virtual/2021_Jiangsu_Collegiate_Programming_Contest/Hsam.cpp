// by poll
#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll M = 1073676287;
ll h_base[100005];
ll h[100005];
ll rh[100005];
string s, rs, sorted_s;
void hash_init(int len, ll prime = 0xdefaced) {
	h_base[0] = 1;
	for(int i=1;i<=len;i++) {
		h[i] = (h[i-1]*prime + s[i-1]) % M;
		h_base[i] = (h_base[i-1]*prime) % M;
	}
}

void rhash_init(int len, ll prime = 0xdefaced) {
	h_base[0] = 1;
	for(int i=1;i<=len;i++) {
		rh[i] = (rh[i-1]*prime + rs[i-1]) % M;
		h_base[i] = (h_base[i-1]*prime) % M;
	}
}

ll get_hash(int l, int r) {
	return (h[r+1] - (h[l]*h_base[r-l+1])%M+M)%M;
}

ll get_rhash(int l, int r) {
	return (rh[r+1] - (rh[l]*h_base[r-l+1])%M+M)%M;
}

ll getHash(int st, int ed, int len, bool print) {
	if(print) printf("st=%d, ed=%d, len=%d\n",st,ed,len);
	int n = (int)s.size();
	if(len < st) {
		if(print) printf("case 1, ans = %lld\n", h[len+1]);
		return h[len+1];
	}
	else if(len <= ed) {
		int rst = n-ed-1;
		int red = rst+len-1;
		if(print) {
			printf("case 2, ans = %lld\n", ((h[st] * h_base[len-st] % M) + get_rhash(rst, red)) % M);
			printf("rst = %lld, red = %lld\n",rst, red);
			printf("seg1 = %lld\n", (h[st] * h_base[len-st] % M));
			printf("seg2 = %lld\n", get_rhash(rst, red)%M);
			//printf("seg2 = %lld\n", get_rhash(rst, red)) % M);
		}
		return ((h[st] * h_base[len-st] % M) + get_rhash(rst, red)) % M;
	} else {
		int rst = n-ed-1;
		int red = n-st-1;
		if(print) {
			printf("rst = %d, red = %d\n",rst, red);
			printf("seg 1 = %lld\n",(h[st] * h_base[len-st] % M));
			printf("seg 2 = %lld\n",(get_rhash(rst, red) * h_base[len-ed] % M));
			printf("seg 3 = %lld\n",get_hash(ed+1, len)%M);
		}
		if(print) printf("case 3, ans = %lld\n", ((h[st+1] * h_base[len-st] % M) + (get_rhash(rst, red) * h_base[len-ed] % M) + get_hash(ed+1, len))%M);
		return ((h[st] * h_base[len-st] % M) + (get_rhash(rst, red) * h_base[len-ed] % M) + get_hash(ed+1, len))%M;
	}
}

bool same(int start, int ed1, int ed2, int len) {
	//get s1 hash
//	printf("s1 = %lld\n",getHash(start, ed1, len, true));
//	printf("s2 = %lld\n",getHash(start, ed2, len, true));
	return getHash(start, ed1, len, false) == getHash(start, ed2, len,false);
}

char getChar(int st, int ed, int len, bool print) {
	int n = (int)s.size();
	if(print) printf("st = %d, ed = %d, len = %d\n",st,ed,len);
	if(len < st) return s[len];
	else if(len <= ed) {
		int rst = n-ed-1;
		int red = rst+len-st;
		if(print) printf("rst = %d, red = %d\n",rst,red);
		return rs[red];
	} else {
		return s[len];
	}
}

bool checkSame(int start, int ed1, int ed2, int len) {
	return getChar(start, ed1, len,false) == getChar(start, ed2, len,false);
}
bool check(int start, int ed1, int ed2, int len) {
	//printf("char1 = %c, char2 = %c\n",getChar(start, ed1, len,true),getChar(start, ed2, len,true));
	return getChar(start, ed1, len,false) > getChar(start, ed2, len,false);
}
int main(){
	int t;
	cin>>t;
	while(t--) {
		cin>>s;
		int n = (int)s.size();
		rs = s;
		reverse(rs.begin(), rs.end());
		hash_init(n);
		rhash_init(n);
		sorted_s = s;
		sort(sorted_s.begin(), sorted_s.end());
		int start = 0;
		while(start < n) {
			if(s[start] == sorted_s[start])
				start++; 
			else break;
		}
//		cout<<s<<"\n";
//		cout<<rs<<"\n";
		if(start == n) cout<<s<<"\n";
		else {
			int ans = start;
			for(int ed = start+1; ed<n; ed++) {
//				printf("----------------- ed = %d ------------------\n",ed);
//				printf("s1:"); cout<<s.substr(0,start)<<rs.substr(n-ans-1, ans-start+1)<<s.substr(ans+1)<<"\n";
//				printf("s2:"); cout<<s.substr(0,start)<<rs.substr(n-ed-1, ed-start+1)<<s.substr(ed+1)<<"\n";
				int L, R, now;
				L = 0, R = n-1;
				while(L<R) {
//					printf("----------------- L=%d, R=%d ------------------\n",L,R);
					int M = (L+R)/2;
					if(same(start, ans, ed, M)) {
						L = M;
						if(L == R-1) break;
					}
					else R = M-1;
				}
				
				//printf("lcp = %d\n",L);
				while(L>=0) {
					if(!checkSame(start, ans, ed, L)) L--;
					else break;
				}
				while(L<n-1) {
					if(checkSame(start, ans, ed, L+1)) L++;
					else break;
				}
				if(L == n-1) continue;
//				printf("L = %d\n",L);
				if(check(start, ans, ed, L+1)) ans = ed;
				
				//printf("ans = %d\n",ans);
			}
			//printf("ans:"); cout<<s.substr(0,start)<<rs.substr(n-ans-1, ans-start+1)<<s.substr(ans+1)<<"\n";
			cout<<s.substr(0,start)<<rs.substr(n-ans-1, ans-start+1)<<s.substr(ans+1)<<"\n";
		}
	}
	

}
