#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define al(a) a.begin(), a.end()
#define F frist
#define S second
#define eb emplace_back
#define REP(i,n) for(int i = 0; i < (int)n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define debug(x) cout << " > " << #x << ": " << x << endl;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;


void solve(int bitn){
//	cout << "ouo: " << data << endl;
	for(int i = 0; i < bitn; i++)
		cout << "1";
	for(int i = bitn; i < 8; i++)
		cout << "0";
	cout << endl;
	return;
	int cnt = 0;
	for(int i = 0; i < 8; i++){
		if((8 - i) == (bitn - cnt)){
			cout << "1";
			cnt++;
			continue;
		}
		int data = rand();
		if(cnt < bitn && (data & 1)){
			cout << "1";	
			cnt++;
		}
		else
			cout << "0";	
	}
	cout << endl;
}


int main(){
	int T;
	cin >> T;	
	while(T--){
		int bitn;
		while(cin >> bitn){
			if(bitn == 0)
				break;
			if(bitn == -1){
				cout << "WA\n";
				return 0;
			}
			solve(bitn);
		}
	}
}
