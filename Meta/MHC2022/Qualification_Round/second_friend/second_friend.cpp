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
char table[100][100];

int main(){
	int T;
	cin >> T;
	int casen = 1;
	while(T--){
		int R, C;
		cin >> R >> C;
		bool hastree= false;
		REP(i, R){
			REP(j, C){
				cin >> table[i][j];
				if(table[i][j] == '^')
					hastree = true;
			}
		}
		cout << "Case #" << casen++ << ": ";
		if((R == 1 || C == 1) && hastree){
			cout << "Impossible\n";
		}
		else{
			cout << "Possible\n";
			REP(i, R){
				REP(j, C){
					cout << (hastree ? "^" : ".");
				}
				cout << endl;
			}
		}
	}
		
	return 0;
}

