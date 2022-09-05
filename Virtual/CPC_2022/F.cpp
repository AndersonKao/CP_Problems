#include <bits/stdc++.h>
using namespace std;

int main(){

	int T;
	cin >> T;
	while(T--){
		int sum = 0;
		for(int i = 0; i < 7; i++){
			int u;
			cin >> u;
			sum += u;
		}
		cout << sum << endl;

	}
}
