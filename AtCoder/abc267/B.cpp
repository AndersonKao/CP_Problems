#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;


int main(){
	string s;
	cin >> s;		
	vector<int> V(7, 0);
	V[0] += (s[7 - 1] == '1');
	V[1] += (s[4 - 1] == '1');
	V[2] += (s[2 - 1] == '1');
	V[2] += (s[8 - 1] == '1');
	V[3] += (s[1 - 1] == '1');
	V[3] += (s[5 - 1] == '1');
	V[4] += (s[3 - 1] == '1');
	V[4] += (s[9 - 1] == '1');
	V[5] += (s[6 - 1] == '1');
	V[6] += (s[10 - 1] == '1');
	bool sol = true;
	if(s[0] == '1')
		sol = false;
	bool found = false;
	for(int i = 0; i < 7; i++){
		if(V[i] == 0) continue;
		for(int j = i + 1; j < 7 ; j++){
			if(V[j] == 0) continue;
//			cout << i << ", " << j << endl;
			for(int k = i+1; k < j; k++){
				if(V[k] == 0){
					found = true;
//					cout << "found " << k << endl;
				}
			}
		}
	}
	if(sol && found)	
	cout << "Yes\n";
	else
	cout << "No\n"; return 0;
}

