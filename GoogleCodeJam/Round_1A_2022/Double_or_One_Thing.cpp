
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define al(a) a.begin(), a.end()
#define F frist
#define S second
#define eb emplace_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define debug(x) cout << " > " << #x << ": " << x << endl;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;


int main(){
	yccc;	
	int T;
	cin >> T;
	string str;
	string ans;
	int cnt = 1;
	int nxt = 0;
	while(T--){
		cout << "Case #" << cnt++ << ": ";
		cin >> str;
		nxt = 0;
//		ans.clear();	
		REP(i, (int)str.length()){
			while(str[nxt] == str[i])
				nxt++;
			cout << str[i];
			if(i < (int)str.length() && nxt < (int)str.length() && str[i] < str[nxt])
				cout << str[i];			
		}
		cout << endl;
	}
}
