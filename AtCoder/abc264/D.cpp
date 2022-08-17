
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
	string str;
	cin >> str;

	vector<int> Vs(7);

	for(int i = 0; i < 7; i++){
		if(str[i] == 'a')
			Vs[i] = 0;
		else if(str[i] == 't')
			Vs[i] = 1;
		else if(str[i] == 'c')
			Vs[i] = 2;
		else if(str[i] == 'o')
			Vs[i] = 3;
		else if(str[i] == 'd')
			Vs[i] = 4;
		else if(str[i] == 'e')
			Vs[i] = 5;
		else if(str[i] == 'r')
			Vs[i] = 6;
	}
	int cnt = 0;
	for(int i = 0; i < 7; i++){
		for(int j = i+1; j < 7; j++){
			if(Vs[i] > Vs[j])
				cnt++;
		}
	}
	cout << cnt << endl;

	return 0;
}
