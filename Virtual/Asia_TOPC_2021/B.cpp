#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--){
		ll x;
		cin >> x;
		ll sum = 0;
		for(ll i = 1; i*i <= x; i++){
			if(x % i == 0){
				sum += i;
				if(i != x/i && i != 1)
					sum += (x/i);
			}
		}
		if(sum < x){
			cout << "deficient\n";
		}
		if(sum > x){
			cout << "abundant\n";
		}
		if(sum == x){
			cout << "perfect\n";
		}
	}

	return 0;
}
