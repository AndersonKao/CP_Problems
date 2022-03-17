#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i =0 ; i < n; i++)
#define endl '\n'
#define debug(x) cout << " > " << #x << " " << x << endl;
template<typename T> using vec = vector<T>;

vec<int> BIT;
vec<int> data;

void modify(int i, int val){
	while(i < BIT.size()){
		BIT[i] += val;
		i += i & (-i);
	}
}
int query(int i){
	int ans = 0;	
	while(i > 0){
		ans += BIT[i];
		i -= i & (-i);
	}
	return ans;
}


int main(){
	int n;
	cin >> n;
	BIT.resize(n+1, 0);
	data.resize(n);
	REP(i, n){
		cin >> data[i];
		modify(i + 1, 1);
	}	
	REP(i, n){
		int k;
		cin >> k;
		int l = 1, r = n;
		while(l < r){
			int m = (l + r) >> 1;
			int t = query(m);
			if(t < k)
				l = m + 1;
			else if(t > k){
				r = m - 1;
			}else
				r = m;
		}
		
		cout << data[l -1 ] << (i == n-1 ? '\n' : ' ');
		modify(l, -1);
	}
	
		
	


	return 0;
}
