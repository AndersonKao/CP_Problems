#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
using ll = long long;
template<typename T>
using vec = vector<T>;
using pii = pair<int, int>;

#define debug(x) cout << #x << ": " << x << endl;

int gcd(int A, int B){
	if( B == 0)
		return A;
	if(A < B)
		return gcd(B,A);
	return gcd(B, A % B);
}

int main(){
	ll N, A, B;
	cin >> N >> A >> B;	
	ll L = A * (B / gcd(A, B));
	ll sum = (1 + N) * N / 2;
	ll LA = N / A;
	sum -= A * ((1 + LA) * LA / 2);		
	ll LB = N / B;
	sum -= B * ((1 + LB) * LB / 2);		
	ll LL = N / L;
	sum += L * ((1 + LL)*LL/2); 
	cout << sum << endl;
	
	return 0;

}
