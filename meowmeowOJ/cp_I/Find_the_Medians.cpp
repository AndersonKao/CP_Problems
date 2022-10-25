// UVa 10107
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
int main(){
	int n;
	cin >> n;
	priority_queue<int> pqL;
	priority_queue<int, vector<int>, greater<int>> pqR;
	for(int i = 0 ;i < n; i++){
		int val;
		cin >> val;
		if(pqL.size() == pqR.size()){
			if(pqL.empty()){
				pqL.emplace(val);	
			}
			else if(val <= pqL.top()){
				pqL.emplace(val);
			}
			else{
				pqR.emplace(val);
				pqL.emplace(pqR.top());
				pqR.pop();
			}
		}
		else{
			if(val <= pqL.top()){
				pqL.emplace(val);
				pqR.emplace(pqL.top());
				pqL.pop();
			}
			else{
				pqR.emplace(val);
			}
		}

		cout << pqL.top() << (i == n-1 ? "\n" : " ");
	}
	return 0;
}

