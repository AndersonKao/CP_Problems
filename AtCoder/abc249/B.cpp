
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define al(a) a.begin(), a.end()
#define F first
#define S second
#define eb emplace_back

using ll = long long;
using pii = pair<int, int>;
template<typename T>
using vec = vector<T>;
auto cmp = [](int& a, int& b){
	return a < b;
};


bool seq[500];
int main(){
	string str;
	cin >> str;
	bool a, b, c;
	a = b = false;
	c = true;
	REP(i, str.length()){
		if(str[i] >= 'A' && str[i] <= 'Z')
			a = true;
		if(str[i] >= 'a' && str[i] <= 'z')
			b = true;
		if(seq[str[i]]){
			c = false;
			break;
		}
		seq[str[i]] = true;
	}	
	if(a && b && c)
		cout << "Yes\n";
	else
		cout << "No\n";
	return 0;
}
