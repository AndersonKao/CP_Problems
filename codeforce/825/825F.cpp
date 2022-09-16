#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int inf = 2000000000;

int prefix[8000] = {0};
int dp[8001];
void gen_prefix(char* str, int len){
	prefix[0] = 0;
	for(int i = 1; i < len; i++){
		int len = prefix[i-1];
		while(len > 0 && str[len] != str[i]){
			len = prefix[len-1];
		}
		if(str[len] == str[i])
			len++;
		prefix[i] = len;
	}
}
int tostrlen(int val){
	if(val == 0)
		return 1;
	int ans = 0;
	while(val > 0)
		val /= 10, ans++;
	return ans;
}
int main(){
	char str[8000];
	scanf("%s", str);
	int len = strlen(str);
	fill(dp, dp+len+1, inf);
	dp[0] = 0;
	for (int i = 0; i < len; i++){
		gen_prefix(str + i, len - i);
		for (int j = i + 1; j <= len; j++){
			int curlen = j - i;
			int circulen = curlen - prefix[curlen-1];
			int circutime = curlen / circulen;
			if(curlen % circulen == 0 && circutime > 1){
				dp[j] = min(dp[j], dp[i] + circulen + tostrlen(circutime));	
			}
			else{
				dp[j] = min(dp[j], dp[i] + curlen + 1);	
			}
		}
	}
	cout << dp[len] << endl;
		
	return 0;
}

