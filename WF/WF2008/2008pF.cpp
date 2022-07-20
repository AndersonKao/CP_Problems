// AC 2022-07-19 21:04:43
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
#define eb emplace_back
#define F first
#define S second
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")\n";
ll nCrT[1001][1001];

ll nCr(int n, int r){
	if(r < 0)
		return 0;
//	cout << n << ", " << r <<endl;
	if(nCrT[n][r])
		return nCrT[n][r];
	if(r == 1){
		return nCrT[n][r] = n;	
	}
	else if(n == r)
		return nCrT[n][r] = 1;
	return nCrT[n][r] = nCr(n-1, r) + nCr(n-1, r-1);	
}

int main(){
	int L;
	int caseN=1;
	for(int i = 0; i <= 1000; i++){
		nCrT[i][0] = 1;
		for(int j = 1; j <= 1000; j++)
			nCrT[i][j] = 0;
	}
	
	while(cin >> L){
		if(L == 0)
			break;
		cout << "Case " << caseN++ << ": ";
		if(L&1){
			cout << "0";
		}else{
			int K = (L-4)/2;
			cout << nCr((L-K+1)-2, K-1)*2 + nCr(L-K+1-2, K);
		}
		cout << endl;
	}
	return 0;
}
