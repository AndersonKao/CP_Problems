#include <bits/stdc++.h>
using namespace std;
#define F frist
#define S second
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;


int main(){
	yccc;	
	int T;
	cin >> T;
	int cnt = 1;
	while(T--){
		cout << "Case #" << cnt++ << ":\n";
		int R, C;
		cin >> R >> C;
		for(int i = 0; i < R; i++){
		
			for(int j = 0; j < C; j++){
				if(i == 0 && j == 0){
					cout << "..";
				}else{
					cout << "+-";
				}
			}
			cout << "+\n";
			for(int j = 0; j < C; j++){
				if(i == 0 && j == 0){
					cout << "..";
				}else{
					cout << "|.";
				}
			}
			cout << "|\n";
		}
		for(int j = 0; j < C; j++)
			cout << "+-";
		cout << "+\n";
	}

}
