#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll solve(int* arr, int p, int r){
	if(p == r){
		return arr[p];
	}
	int q = (p + r)/2;	
	ll ans = max(solve(arr, p, q), solve(arr, q+1, r));
	ll lmax = numeric_limits<ll>::min(), lsum = 0;
	for(int i = q; i >= p; i--){
		lsum += arr[i];
		lmax = max(lmax, lsum);
	}
	ll rmax =  numeric_limits<ll>::min(), rsum = 0;
	for(int i = q+1; i <= r; i++){
		rsum += arr[i];
		rmax = max(rmax, rsum);
	}
	return max(ans, lmax + rmax);
}

int main(){
	int N;
	cin >> N;
	int * arr = new int[N];
	for(int i = 0; i < N; i++)
		cin >> arr[i];
	 cout << solve(arr, 0, N-1);
	 delete [] arr;
}
