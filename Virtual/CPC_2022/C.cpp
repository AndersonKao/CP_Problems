#include <bits/stdc++.h>
using namespace std;

int main(){

	int T;
	cin >> T;
	while(T--){
		vector<int> V;
		int N;
		cin >> N;
		for(int i = 0; i < N; i++){
			int u;
			cin >> u;
			V.push_back(u);
		}
		bool sol = true;
		for(int i = 1; i < N; i++){
			if(V[i-1] >= V[i]){
				sol = false;
			}
		}
		cout << (sol ? "Yes" : "No") << endl;

	}
}
