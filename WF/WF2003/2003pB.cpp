#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0 ; (i) < (int)(n); (i)++)
#define REP1(i, n) for(int (i) = 1 ; (i) <= (int)(n); (i)++)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define PR(x) cout << #x << " = " << (x) << endl
#define endl "\n"
using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;
//bitset<350> sa, sb;



int main(){
//	yccc;
	int cnt = 1;
	string a, b;
	while(cin >> a >> b){
		if(a == "0" && b == "0")
			break;
		//PR(a), PR(b);
		bitset<350> sa(a), sb(b);
		
		//ull pa = a;
		// case 1
		bitset<350> ans;	
		ans.reset();
		ans.flip();
		int limit = 349;
		while(sa[limit] == 0 && sb[limit] == 0)
			limit--;	
		bitset<350> tmp;	
		for(int i = limit-1; i >= 0; i--){
			if(sa[i+1] != sb[i+1]){
				tmp.flip(i);
				sa.flip(i+1), sa.flip(i);
				if(i > 0)
					sa.flip(i-1);
			}
		}
		if(sa[0] == sb[0])
			ans = bitset<350>(min(ans.to_string(), tmp.to_string()));
		// case 2
		sa = bitset<350>(a);
		tmp.reset();
		tmp.flip(limit);
		sa.flip(limit);
		if(limit > 0)
			sa.flip(limit-1);
		for(int i = limit-1; i >= 0; i--){
			if(sa[i+1] != sb[i+1]){
				tmp.flip(i);
				sa.flip(i+1), sa.flip(i);
				if(i > 0)
					sa.flip(i-1);
			}
		}
		if(sa[0] == sb[0])
			ans = bitset<350>(min(ans.to_string(), tmp.to_string()));
// print out ans;
		if(cnt != 1)
			cout << endl;
		cout << "Case Number " << cnt++ << ": ";	
		if(ans == numeric_limits<ll>::max())
			cout << "impossible\n";
		else 
			cout << ans.to_string() << endl;
	}

}
