#include <bits/stdc++.h>
using namespace std;
vector<int> V;
using ll = long long;
int main(){
	int N;
	cin >> N;
	V.resize(N);
	ll self = 0;
	for(int i = 0; i < N; i++){
		cin >>V[i];
		V[i]--;
		if(V[i] == i)
			self++;
	}
	ll ans = 0;
	for(int i = 0; i < N; i++){
		if(V[i] != i && i == V[V[i]]){
			ans++;
		}
	}
	ans/=2;
	cout << ans  + self * (self-1) / 2<< endl;
	return 0;
}
