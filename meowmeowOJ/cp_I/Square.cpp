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
int n;
int sti[20];
int stack[4];
bool sol;
bool selected[20];
int target;
bool dfs(int cur, int l, int tid){
	if(tid == 3){
		return true;
	}

	for(int i = l; i < n; i++){
		if(selected[i])
			continue;
		selected[i] = true;
		if(cur + sti[i] == target){
			if(dfs(0, 0, tid+1)){
				return true;
			}
		}
		else if(cur + sti[i] < target){
			if(dfs(cur+sti[i], i+1, tid)){
				return true;
			}
		}
		selected[i] = false;
	}
	return false;
}
int main(){
	int T;
	cin >> T;
	while(T--){
		cin >> n;
		int sum = 0;
		REP(i, n){
			cin >> sti[i];
			sum += sti[i];
			selected[i] = false;
		}
		target = sum /4;
		sort(sti, sti+n, greater<int>());
		if(sum % 4 || sti[0] > target){
			cout << "no\n";
			continue;
		}
		
		if(dfs(0, 0, 0)){
			cout << "yes\n";
		}
		else
			cout << "no\n";
	}
	return 0;
}

