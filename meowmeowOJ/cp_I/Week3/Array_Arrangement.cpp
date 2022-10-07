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
const int maxn = 200000;
list<int> mlist;
list<int>::iterator mit[maxn+1];
int main(){
	int T;
	cin >> T;
	while(T--){
		int n, q;
		cin >> n >> q;
		mlist.clear();
		REP1(i, n){
			mlist.emplace_back(i);
			mit[i] = (--mlist.end());
		}
		REP(i, q){
			char op; int num;
			cin >> op >> num;
			mlist.erase(mit[num]);
			if(op == 'H'){
				mlist.emplace_front(num);
				mit[num] = mlist.begin();
			}
			else{
				mlist.emplace_back(num);
				mit[num] = (--mlist.end());
			}
		}
		for(auto it = mlist.begin(); it != mlist.end(); it++){
			cout << *it << " ";
		}
		cout << endl;
	}
	return 0;
}

