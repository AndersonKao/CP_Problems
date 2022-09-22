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
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
vec<bool> in;
void getout(int k);
void getin(int k){
	if(in[k])
		return;
	if(k == 1){
		printf("Move ring %d in\n", k);
	}
	else{
		getin(k-1);
		for(int j = k-2; j >= 1; j--){
			getout(j);
		}
		printf("Move ring %d in\n", k);
	}
	in[k] = true;
}
void getout(int k){
	if(in[k] == false)
		return;
	if(k == 1){
		printf("Move ring %d out\n", k);
	}
	else{
		getin(k-1);
		for(int j = k-2; j >= 1; j--){
			getout(j);
		}
		printf("Move ring %d out\n", k);
	}
	in[k] = false;
}
int main(){
	int n;
	cin >> n;
	in.resize(n+1, true);	
	for(int i = n; i >= 1; i--)
		getout(i);
	return 0;
}

