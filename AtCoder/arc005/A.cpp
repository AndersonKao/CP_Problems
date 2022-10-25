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
	string str;
	cin >> str;
	stack<char> st;
	for(int i = 0; i < str.length(); i++){
		if(str[i] == 'T' && st.size() && st.top() == 'S'){
				st.pop();
		}
		else
			st.emplace(str[i]);
	}
	cout << st.size() << endl;
	return 0;
}

