#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define al(x) x.begin(), x.end()
#define F first
#define S second
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << x.first << ", " << x.second << endl;
using ll = long long;
using pii = pair<int, int>;
int main(){
	string str = "atcoder";
	int L ,R;
	cin >> L >> R;
	L--, R--;
	for(int i = L; i <= R; i++){
		cout << str[i];
	}
	return 0;
}
