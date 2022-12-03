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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
int cnt[26] = {0};
int main(){
	yccc;		
	string str;
	cin >> str;
	int n = str.length();
	
	for(int i = 0; i < n; i++){
		cnt[str[i] - 'A']++;
	}
	int oddcnt = 0;
	int oddone = -1;
	for(int i = 0; i < 26; i++){
		if(cnt[i] & 1){
			oddone = i;
			oddcnt++;
		}
	}
	if(str.length() & 1){
		if(oddcnt != 1){
			cout << "NO SOLUTION\n";
			return 0;
		}
	}
	else{
		if(oddcnt){
			cout << "NO SOLUTION\n";
			return 0;
		}
	}

	for(int i = 0; i < 26; i++){
		int res = cnt[i] >> 1;
		if(oddone == i) res += 1;
		while(cnt[i] > res){
			cout << (char)('A' + i);
			cnt[i]--;
		}
	}
	if(oddone != -1){
		cout << (char)('A' + oddone);
		cnt[oddone]--;
	}
	for(int i = 25; i >= 0; i--){
		while(cnt[i]){
			cout << (char)('A' + i);
			cnt[i]--;
		}
	}
	cout << "\n";
	return 0;
}

