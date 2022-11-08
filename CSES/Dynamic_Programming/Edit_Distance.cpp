#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxn = 5000;
int dp[maxn+1][maxn+1];
const int inf = 0x3f3f3f3f;
int main(){
	yccc;		
	string A, B;
	cin >> A >> B;
	int alen = A.length();
	int blen = B.length();
	for(int i = 0; i <= maxn; i++)
		fill(dp[i], dp[i] + maxn, inf);
	dp[0][0] = 0;
	for(int i = 1; i <= alen; i++)
		dp[i][0] = i;
	for(int i = 1; i <= blen; i++)
		dp[0][i] = i;
	for(int i = 1; i <= alen; i++){
		for(int j = 1; j <= blen; j++){
			if(A[i-1] == B[j-1]){ // Replace
				dp[i][j] = dp[i-1][j-1]; 
			}
			else{
				dp[i][j] = dp[i-1][j-1]+1;
			}
			dp[i][j] = min(dp[i][j], dp[i-1][j] + 1); // remove
			dp[i][j] = min(dp[i][j], dp[i][j-1] + 1); // insert
		}
	}
	cout << dp[alen][blen]<< endl;

	return 0;
}

