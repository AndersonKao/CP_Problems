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
	priority_queue<int, vec<int>, greater<int>> v1;
	deque<int> v2;	
	int Q;
	cin >> Q;
	while(Q--){
		int op, val;
		cin >> op;
		if(op == 1){
			cin >> val;
			v2.emplace_back(val);
		}
		else if( op == 2){
			if(v1.size()){
				cout << v1.top() << endl;
				v1.pop();
			}
			else{
				cout << v2.front() << endl;
				v2.pop_front();
			}
		}
		else {
			for_each(v2.begin(), v2.end(), [&](int v){
				v1.emplace(v);
			});
			v2.clear();
		}
	}
	return 0;
}

